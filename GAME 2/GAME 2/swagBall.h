#pragma once
#include<SFML/Graphics.hpp>

enum swagBallTypes { DEFAULT = 0, damage, healing, noOfTypes };

class swagBall
{
private:
	sf::CircleShape shape;

	int type;

	void initShape(sf::RenderWindow& target);

public:
	swagBall(sf::RenderWindow& target,int type);
	~swagBall();

	//accessor
	const sf::CircleShape getShape() const;
	const int& getType() const;

	void update(sf::RenderWindow* target);
	void render(sf::RenderWindow* target);
};