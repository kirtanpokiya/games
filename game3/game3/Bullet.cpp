#include "Bullet.h"
#include<iostream>



Bullet::Bullet()
{
}

Bullet::Bullet(sf::Texture* texture, float posX, float posY, float dirX, float dirY, float movement_speed)
{
	bullet.setTexture(*texture);
	bullet.setPosition(posX, posY);
	direction.x = dirX;
	direction.y = dirY;
	movementSpeed = movement_speed;
}

Bullet::~Bullet()
{
}

const sf::FloatRect Bullet::getglobalBound() const
{
	return bullet.getGlobalBounds();
}

void Bullet::update()
{
	bullet.move(movementSpeed * direction);
}

void Bullet::render(sf::RenderTarget* target)
{
	target->draw(this->bullet);
}