#pragma once
#include<SFML/Graphics.hpp>

class Bullet
{
private:
	sf::Sprite bullet;
	sf::Texture* texture;

	sf::Vector2f direction;
	float movementSpeed;


public:
	Bullet();
	Bullet(sf::Texture* texture,float posX,float posY,float dirX, float dirY, float movement_speed);
	~Bullet();

	//accessors
	const sf::FloatRect getglobalBound() const;

	void update();
	void render(sf::RenderTarget* target);
};

