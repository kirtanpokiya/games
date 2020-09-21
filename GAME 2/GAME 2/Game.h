#pragma once
#include<iostream>
#include<ctime>
#include<vector>
#include<SFML/Graphics.hpp>
#include"Player.h"
#include"swagBall.h"

class Game
{
private:
	sf::VideoMode videoMode;
	sf::RenderWindow* window;
	bool endGame;
	sf::Event sfmlEvent;

	Player player;

	int points;
	int time;

	sf::Font font;
	sf::Text text;
	sf::Text timeText;
	sf::Text endgameText;

	std::vector<swagBall> swagBalls;
	float spawnTimerMax;
	float spawnTimer;
	int maxSwagBalls;

	void initVariables();
	void initWindow();
	void initFont();
	void initText();

public:
	//constructors and destructors
	Game();
	~Game();

	//accessors
	const bool& getEndgame() const;

	//modifiers

	//functions
	const bool running() const;
	void pollEvent();

	void spawnSwagBalls();
	const int randomisedBallType() const;
	void updatePlayer();
	void updateCollision();

	void updateTime();
	void updateText();
	void update();

	void renderText(sf::RenderWindow &target);
	void render();
};

