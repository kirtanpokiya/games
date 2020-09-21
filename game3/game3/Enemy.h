#pragma once
#include<SFML/Graphics.hpp>
class Enemy
{
private:
	sf::CircleShape shape;
	int pointCount;
	int type;
	float speed;
	int hp;
	int hpMax;
	int damage;
	int	points;

	void initVariables();
	void initshape();

public:
	Enemy(float posX, float posY);
	~Enemy();	

	sf::FloatRect getBounds() const;

	const int getDamage() const;

	const int& getPoints() const;

	void update();
	void render(sf::RenderTarget* target);
};
