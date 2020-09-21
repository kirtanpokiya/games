#pragma once
#include<SFML/Graphics.hpp>
#include<vector>

class Game
{
private:
	sf::RenderWindow* window;
	sf::Event ev;
	sf::VideoMode videomode;

	sf::Font font;
	sf::Text uiText;

	sf::Vector2i mousePos;
	sf::Vector2f mousePosViews;

	void initVariables();
	void initWindow();
	void initenemy();
	void initFont();
	void inituiText();

public:
	//construcors / destructors
	 Game();
	 virtual ~Game();

	 //game logic
	 bool endGame;
	 float enemySpawnTimer;
	 float enemySpawnTimerMax;
	 unsigned int maxEnemies;
	 int points;
	 int health;
	 bool mouseHeld;

	 //game objects
	 std::vector<sf::RectangleShape> enemies;
	 sf::RectangleShape enemy;

	 //accessors
	 const bool running() const;
	 const bool getEndGame() const;

	 void printScore();
	 void spawnEnemies();

	 void pollEvent();
	 void mousePosWindow();

	 void updateEnemies();
	 void updateuiText();
	 void update();

	 void renderEnemies(sf::RenderTarget& target);
	 void renderuiText(sf::RenderTarget& target);
	 void render();
};