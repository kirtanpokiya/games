#include "Game.h"
#include<SFML/Graphics.hpp>
#include <iostream>
#include<ctime>
#include<sstream>

void Game::initVariables()
{
	this->window = nullptr;
	this->videomode.width = 512;
	this->videomode.height = 512;

	this->endGame = false;
	this->enemySpawnTimerMax = 10.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 10;
	this->health = 100;
	this->mouseHeld = false;
}

void Game::initWindow()
{
	this->window = new sf::RenderWindow(this->videomode, "my first game", sf::Style::Default);

	this->window->setFramerateLimit(60);
}

void Game::initenemy() 
{
	this->enemy.setPosition(100.f,100.f);
	this->enemy.setSize(sf::Vector2f(50.f, 50.f));
	this->enemy.setFillColor(sf::Color::Green);
	this->enemy.setOutlineColor(sf::Color::Black);
	this->enemy.setOutlineThickness(1.0f);
}

void Game::initFont()
{
	if (!this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
		std::cout << "ERROR::Fonts are not loded";
}

void Game::inituiText()
{
	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(24);
	this->uiText.setFillColor(sf::Color::White);
	this->uiText.setString("NONE");
}

Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initenemy();
	this->initFont();
	this->inituiText();
}

Game::~Game()
{
	delete this->window;
}

const bool Game::running() const
{
	return this->window->isOpen();
}

const bool Game::getEndGame() const
{
	return this->endGame;
}

void Game::printScore()
{
	std::cout << "-----GAME OVER----- \n";
	std::cout << "total points earned  :" << this->points;
}

void Game::spawnEnemies()
{
	int type = (rand() % 5) + 1;
	this->enemy.setPosition(
	static_cast<float>(rand()% static_cast<int>(this->window->getSize().x) - this->enemy.getSize().x),
	0.f);
	switch (type)
	{
	case 1:
		this->enemy.setFillColor(sf::Color::Magenta);
		this->enemy.setSize(sf::Vector2f(20.f,20.f));
		break;
	case 2:
		this->enemy.setFillColor(sf::Color::Blue);
		this->enemy.setSize(sf::Vector2f(25.f,25.f));
		break;
	case 3:
		this->enemy.setFillColor(sf::Color::Red);
		this->enemy.setSize(sf::Vector2f(50.f,50.f));
		break;
	case 4:
		this->enemy.setFillColor(sf::Color::Yellow);
		this->enemy.setSize(sf::Vector2f(70.f,70.f));
		break;
	case 5:
		this->enemy.setFillColor(sf::Color::Green);
		this->enemy.setSize(sf::Vector2f(100.f,100.f));
		break;
	default:
		this->enemy.setFillColor(sf::Color::Cyan);
		this->enemy.setSize(sf::Vector2f(100.f,100.f));
		break;
	}
	
	this->enemies.push_back(this->enemy);
}

void Game::pollEvent()
{
	while (this->window->pollEvent(this->ev))
	{
		if (this->ev.type == sf::Event::Closed)
			this->window->close();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			this->window->close();
	}
}

void Game::mousePosWindow()
{
	this->mousePos = sf::Mouse::getPosition(*this->window);
	this->mousePosViews = this->window->mapPixelToCoords(this->mousePos);
}

void Game::updateEnemies()
{
	if (this->enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			this->spawnEnemies();
			this->enemySpawnTimer = 0.f;
		}
		else
			this->enemySpawnTimer += 1.f;
	}


	for (int i = 0; i < this->enemies.size(); i++)
	{
		bool deleted = false;
		this->enemies[i].move(0.0f, 2.5f);

		if (this->enemies[i].getPosition().y > this->window->getSize().y)
		{
			this->enemies.erase(this->enemies.begin() + i);
			this->health -= 5;
			std::cout << "health  :" << this->health<<"\n";
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->mouseHeld == false)
		{
			this->mouseHeld = true;
			bool deleted = false;
			for (int i = 0; i < this->enemies.size() && deleted == false; i++)
			{
				if (this->enemies[i].getGlobalBounds().contains(this->mousePosViews))
				{	
					if(this->enemies[i].getFillColor()==sf::Color::Magenta)
						this->points += 50.f;
					if (this->enemies[i].getFillColor() == sf::Color::Blue)
						this->points += 30.f;
					if (this->enemies[i].getFillColor() == sf::Color::Red)
						this->points += 20.f;
					if (this->enemies[i].getFillColor() == sf::Color::Yellow)
						this->points += 10.f;
					if (this->enemies[i].getFillColor() == sf::Color::Green)
						this->points += 5.f;

					this->enemies.erase(this->enemies.begin() + i);
					std::cout << "points  :" << this->points<<"\n";
				}
			}
		}
	}
	else
		this->mouseHeld = false;
}

void Game::updateuiText()
{
	std::stringstream ss;
	ss << "Points  : " << this->points<<"\n"<<"Health  : "<<this->health;

	this->uiText.setString(ss.str());
}


void Game::update()
{
	this->pollEvent();

	if (!this->endGame)
	{
		this->mousePosWindow();
		this->updateEnemies();
		this->updateuiText();
	}

	if (this->health <= 0)
		this->endGame = true;

	if(this->endGame)
		this->printScore();
}


void Game::renderEnemies(sf::RenderTarget& target)
{
	for (auto& e : this->enemies)
		target.draw(e);
}

void Game::renderuiText(sf::RenderTarget& target)
{
	target.draw(this->uiText);
}

void Game::render()
{
	this->window->clear();
	this->renderEnemies(*this->window);
	this->renderuiText(*this->window);
	this->window->display();
}