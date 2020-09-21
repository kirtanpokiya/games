#pragma once
#include"Player.h"
#include"Bullet.h"
#include<map>
#include"Enemy.h"
	
class game
{
private:
	sf::RenderWindow* window;

	std::map<std::string, sf::Texture*> textures;
	std::vector<Bullet*> bullets;
	std::vector<Enemy*> enemies;

	float spawnTimer;
	float spawnTimerMax;

	time_t gameTimer;
	time_t currentTime;
	time_t lastTime;
	time_t gameTimerMax;

	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;

	//gui
	sf::Font font;
	sf::Text pointText;
	sf::Text timeText;
	sf::Text gameOverText;

	sf::Sprite background;
	sf::Texture bgTexture;

	Player* player;
	Bullet* bullet;
	Enemy* enemy;

	unsigned points;

	void initWindow();
	void initPlayer();
	void initEnemies();
	void initTextures();
	void initGUI();
	void initBackground();
	void initSystem();
	void initTimer();

public:
	game();
	~game();

	void run();

	void updatePollEvent();
	void updateInput();
	void updateBullet();
	void updateCollison();
	void updateEnemiesAndCombat();
	void updateGUI();
	void updateTimer();
	void update();

	void renderBg();
	void renderGUI();
	void render();
};

