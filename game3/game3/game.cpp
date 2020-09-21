#include "game.h"
#include<string>
#include<sstream>

void game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "game 3", sf::Style::Default);
	this->window->setFramerateLimit(144);
}

void game::initPlayer()
{
	this->player = new Player();
}

void game::initEnemies()
{
	//enemy = new Enemy(20, 20);
	spawnTimerMax = 50;
	spawnTimer = spawnTimerMax;
}

void game::initTextures()
{
	this->textures["BULLET"] = new sf::Texture();
	textures["BULLET"]->loadFromFile("textures/bullet.png");
}

void game::initGUI()
{
	font.loadFromFile("Fonts/Metropolian-Display.ttf");
	
	pointText.setFont(font);
	pointText.setCharacterSize(25);
	pointText.setFillColor(sf::Color::White);
	pointText.setString("points :   ");
	pointText.setPosition(sf::Vector2f(window->getSize().x - pointText.getGlobalBounds().width,0));

	timeText.setFont(font);
	timeText.setCharacterSize(25);
	timeText.setFillColor(sf::Color::White);
	timeText.setString("test");
	timeText.setPosition(sf::Vector2f(window->getSize().x - pointText.getGlobalBounds().width - 100, 0));

	gameOverText.setFont(font);
	gameOverText.setCharacterSize(64);
	gameOverText.setFillColor(sf::Color::Red);
	gameOverText.setString("GAME OVER!");
	gameOverText.setPosition(sf::Vector2f(
		window->getSize().x / 2.f - gameOverText.getGlobalBounds().width / 2.f,
		window->getSize().y / 2.f - gameOverText.getGlobalBounds().height / 2.f));

	playerHpBar.setSize(sf::Vector2f(200, 25));
	playerHpBar.setFillColor(sf::Color::Green);
	playerHpBar.setPosition(sf::Vector2f(20, 20));

	playerHpBarBack = playerHpBar;
	playerHpBarBack.setFillColor(sf::Color(255,0,0,100));
}

void game::initBackground()
{
	bgTexture.loadFromFile("textures/background1.jpg");
	background.setTexture(bgTexture);
}

void game::initSystem()
{
	points = 0;
}

void game::initTimer()
{
	lastTime = time(NULL);
	currentTime = time(NULL);
	gameTimer = 0;
	gameTimerMax = 30;
}

game::game()
{
	this->initWindow();
	initPlayer();
	initTextures();
	initEnemies();
	initGUI();
	initBackground();
	initSystem();
	initTimer();
}

game::~game()
{
	delete this->window;
	delete this->player;

	for (auto& i : textures)
	{
		delete i.second;
	}

	for (auto* i : bullets)
	{
		delete i;
	}
	for (auto* i : enemies)
	{
		delete i;
	}
}

void game::run()
{
	while (this->window->isOpen())
	{
		updatePollEvent();
		if (player->getHp() > 0 && gameTimer<gameTimerMax)
		{
			this->update();
			this->render();
		}
	}
}

void game::updatePollEvent()
{
	sf::Event ev;
	while (window->pollEvent(ev))
	{
		if (ev.type == sf::Event::Closed)
			window->close();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			window->close();
	}
}

void game::updateInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && player->canAttack())
	{
		bullets.push_back(new Bullet(textures["BULLET"],
			player->getPos().x+player->getBounds().width/2,
			player->getPos().y,0,-1,5));
	}
}

void game::updateBullet()
{
	unsigned counter = 0;
	for (auto* bullet : bullets)
	{
		bullet->update();
		if (bullet->getglobalBound().top + bullet->getglobalBound().height < 0.f)
		{
			delete bullets.at(counter);
			this->bullets.erase(bullets.begin() + counter);
			--counter;
		}
		++counter;
	}
}

void game::updateCollison()
{
	if (player->getBounds().left < 0.f)
		player->setPosition(0, player->getBounds().top);
	else if (player->getBounds().left +player->getBounds().width>=window->getSize().x)
		player->setPosition(window->getSize().x - player->getBounds().width, player->getBounds().top);

	if (player->getBounds().top < 0.f)
		player->setPosition(player->getBounds().left,0.f);
	else if (player->getBounds().top + player->getBounds().height >= window->getSize().y)
		player->setPosition(player->getBounds().left, window->getSize().y - player->getBounds().height);
}

void game::updateEnemiesAndCombat()
{
	spawnTimer += 0.5;
	if (spawnTimer >= spawnTimerMax)
	{
		enemies.push_back(new Enemy(rand()%780, -10));
		spawnTimer = 0;
	}
	for (int i = 0; i < enemies.size(); i++)
	{
		bool enemyRemoved = false;
		enemies[i]->update();

		for (int k = 0; k < bullets.size() && !enemyRemoved; k++)
		{
			if (bullets[k]->getglobalBound().intersects(enemies[i]->getBounds()))
			{
				points += enemies[i]->getPoints();

				enemies.erase(enemies.begin() + i);
				bullets.erase(bullets.begin() + k);

				enemyRemoved = true;
			}
		}
		if (!enemyRemoved)
		{
			if (enemies[i]->getBounds().top > window->getSize().y)
			{
				enemies.erase(enemies.begin() + i);
				enemyRemoved = true;
			}
			else if (enemies[i]->getBounds().intersects(player->getBounds()))
			{
				player->loseHp(enemies.at(i)->getDamage());
				enemies.erase(enemies.begin() + i);
				enemyRemoved = true;
			}
		}
	}
	
}

void game::updateGUI()
{
	std::stringstream ss;
	ss << "points :" << points << "\n" <<
		"time   :" << gameTimerMax - gameTimer;
	pointText.setString(ss.str());

	float  hpPercent = static_cast<float>(player->getHp())/player->getHpMax();
	playerHpBar.setSize(sf::Vector2f(200 * hpPercent, playerHpBarBack.getSize().y));

	if (player->getHp() <= 0)
	{
		playerHpBar.setSize(sf::Vector2f(0,playerHpBarBack.getSize().y));
	}
}

void game::updateTimer()
{
	currentTime = time(NULL);
	gameTimer = currentTime - lastTime;
}

void game::update()
{
	updateInput();
	this->player->update();
	updateCollison();
	updateBullet();
	updateEnemiesAndCombat();
	updateGUI();
	updateTimer();
}

void game::renderBg()
{
	window->draw(background);
}

void game::renderGUI()
{
	window->draw(pointText);
	window->draw(playerHpBarBack);
	window->draw(playerHpBar);
}

void game::render()
{
	this->window->clear();
	//---------------------//

	renderBg();

	player->render(*this->window);
	
	for (auto* i : bullets)
	{
		i->render(this->window);
	}

	renderGUI();

	for (auto* i : enemies)
	{
		i->render(this->window);
	}

	if (player->getHp() <= 0 || gameTimer >=gameTimerMax)
	{
		window->draw(gameOverText);
	}
	
	//---------------------//
	this->window->display();
}