#include "Game.h"
#include<sstream>
#include <iomanip> 
#include <iostream> 
#include <stdlib.h> 
#include<cstdlib>
#include <Windows.h>

void Game::initVariables()
{
	this->endGame = false;
	this->maxSwagBalls = 10;
	this->spawnTimerMax =10.f ;
	this->spawnTimer = this->spawnTimerMax;
	this->points = 0;
	this->time = 30;
}

void Game::initWindow()
{
	this->videoMode = sf::VideoMode(800, 600);
	this->window = new sf::RenderWindow(this->videoMode,"game 2",sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
}

void Game::initFont()
{
	this->font.loadFromFile("Fonts/Metropolian-Display.ttf");
}

void Game::initText()
{
	this->text.setFont(this->font);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(32);
	this->endgameText.setFont(this->font);
	this->endgameText.setFillColor(sf::Color::Red);
	this->endgameText.setCharacterSize(64);
	this->endgameText.setPosition(sf::Vector2f(170, 200));
	this->endgameText.setString("GAME OVER");
}

Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initFont();
	this->initText();
}

Game::~Game()
{
	delete this->window;
}

const bool& Game::getEndgame() const
{
	return this->endGame;
}

const bool Game::running() const
{
	return this->window->isOpen();
}

void Game::pollEvent()
{
	while (this->window->pollEvent(this->sfmlEvent))
	{
		if (this->sfmlEvent.type == sf::Event::Closed)
			this->window->close();
			
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			this->window->close();
	}
}

void Game::spawnSwagBalls()
{
	if (this->spawnTimer < this->spawnTimerMax)
		this->spawnTimer += 1.f;
	else
		if (this->swagBalls.size() < this->maxSwagBalls)
		{
			this->swagBalls.push_back(swagBall(*this->window,randomisedBallType()));
			this->spawnTimer = 0.f;
		}
}

const int Game::randomisedBallType() const
{
	int  type = swagBallTypes::DEFAULT;
	int randValue = rand() % 100 + 1;
	if (randValue > 60 && randValue <= 80)
		type = swagBallTypes::damage;
	else if (randValue > 80 && randValue <= 100)
		type = swagBallTypes::healing;
	return type;
}

void Game::updatePlayer()
{
	this->player.update(this->window);
	if (player.getHP() <= 0)
		endGame = true;
}

void Game::updateCollision()
{
	for (size_t i = 0; i < this->swagBalls.size(); i++)
	{
		if (this->player.getShape().getGlobalBounds().intersects(this->swagBalls[i].getShape().getGlobalBounds()))
		{
			switch (this->swagBalls[i].getType())
			{
			case swagBallTypes::DEFAULT:
				points += 10;
				break;
			case swagBallTypes::damage:
				player.takeDamage(50);
				break;
			case swagBallTypes::healing:
				player.gainHealth(10);
				points++;
				break;
			}
			swagBalls.erase(this->swagBalls.begin() + i);
		}
	}
}

void Game::updateTime()
{
	Sleep(1);
	time--;
}

void Game::updateText()
{
	int zeroHP;
	std::stringstream ss;
	if (this->player.getHP() < 0)
	{
		zeroHP = 0;
		ss << "points  :" << this->points << "\n"
			<< "health :" << zeroHP<<"\n"
			<<"time :"<<time;
		text.setString(ss.str());

	}
	else
	{
		ss << "points  :" << this->points << "\n"
			<< "health :" << this->player.getHP() << "\n"
			<< "time :" << time;
		text.setString(ss.str());
	}
}

void Game::update()
{
	this->pollEvent();
	if (!this->endGame)
	{
		this->spawnSwagBalls();
		updateText();
		updatePlayer();
		updateCollision();
		updateText();
	}
}

void Game::renderText(sf::RenderWindow& target)
{
	target.draw(this->text);
}

void Game::render()
{
	this->window->clear();

	//----------------------------------------//
	//render stuff
	this->player.render(this->window);//render player
	
	for (auto i : this->swagBalls)//render swag balls
	{
		i.render(this->window);
	}

	this->renderText(*this->window);//render text;

	if (this->endGame)
		this->window->draw(this->endgameText);

	//----------------------------------------//
	this->window->display();
}
