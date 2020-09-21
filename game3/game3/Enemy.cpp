#include "Enemy.h"

void Enemy::initVariables()
{
	pointCount = rand() % 8 + 3;
	hpMax = 100;
	speed = pointCount/1.5f;
	hp = hpMax;
	type = 0;
	damage = 5*pointCount;
	points = pointCount;
}

void Enemy::initshape()
{
	shape.setRadius(rand()%20+20);
	shape.setPointCount(pointCount);
	shape.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1, 255));
}

Enemy::Enemy(float posX,float posY)
{
	initVariables();
	initshape();
	shape.setPosition(posX, posY);
}

Enemy::~Enemy()
{
}

sf::FloatRect Enemy::getBounds() const
{
	return shape.getGlobalBounds();
}

const int Enemy::getDamage() const
{
	return damage;
}

const int& Enemy::getPoints() const
{
	return points;
}

void Enemy::update()
{
	shape.move(0, speed);
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(shape);
}
