#pragma once
#include<SFML/Graphics.hpp>

class Player
{
private:
	sf::RectangleShape shape;


	void initVariables();
	void initShape();

	

	float moveSpeed;
	int hp;
	int hpMax;

public:
	//constructors and destructors
	Player(float x = 0.f, float y = 0.f);
	~Player();


	//accessors
	const sf::RectangleShape getShape() const;
	const int& getHP() const;
	const int& getHPMax() const;

	void takeDamage(const int damage);
	void gainHealth(const int health);
	void updateInput();
	void updateWindowBoundCollision(const sf::RenderWindow* target);

	void update(const sf::RenderWindow *target);
	void render(sf::RenderWindow* target);
};

