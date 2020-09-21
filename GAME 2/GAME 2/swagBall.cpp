#include "swagBall.h"

const sf::CircleShape swagBall::getShape() const
{
	return this->shape;
}

const int& swagBall::getType() const
{
	return type;
}

void swagBall::initShape(sf::RenderWindow& target)
{
	this->shape.setRadius(rand() % 10 + 10);

	switch (type)
	{
	case swagBallTypes::DEFAULT:
		this->shape.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1));
		break;
	case swagBallTypes::damage:
		this->shape.setFillColor(sf::Color::Red);
		this->shape.setOutlineColor(sf::Color::White);
		this->shape.setOutlineThickness(2.f);
		break;
	case swagBallTypes::healing:
		this->shape.setFillColor(sf::Color::Green);
		this->shape.setOutlineColor(sf::Color::White);
		this->shape.setOutlineThickness(2.f);
		break;
	}

	this->shape.setPosition(sf::Vector2f(
		static_cast<float>(rand()%target.getSize().x - this->shape.getGlobalBounds().width),
		static_cast<float>(rand() % target.getSize().y- this->shape.getGlobalBounds().height)));
}

swagBall::swagBall(sf::RenderWindow& target, int type)
	:type(type)
{
	this->initShape(target);
}
	
swagBall::~swagBall()
{
}

void swagBall::update(sf::RenderWindow* target)
{
}

void swagBall::render(sf::RenderWindow* target)
{
	target->draw(this->shape);
}
