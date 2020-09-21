#include "Player.h"

void Player::initVariables()
{
	this->moveSpeed = 10.f;
	this->hpMax = 100;
	this->hp = hpMax;
}

void Player::initShape()
{
	this->shape.setFillColor(sf::Color::Green);
	this->shape.setSize(sf::Vector2f(50.f, 50.f));
}

const sf::RectangleShape Player::getShape() const
{
	return this->shape;
}

const int& Player::getHP() const
{
	return hp;
}

const int& Player::getHPMax() const
{
	return hpMax;
}

void Player::takeDamage(const int damage)
{
	if (hp > 0)
		hp -= damage;
	else
		hp = 0;
}

void Player::gainHealth(const int health )
{
	if (hp < hpMax)
		hp += health;
	else
		hp = hpMax;
}

Player::Player(float x, float y)
{
	this->shape.setPosition(x, y);
	this->initVariables();
	this->initShape();
}

Player::~Player()
{
}

void Player::updateInput()
{
	//keyboard
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->shape.move(sf::Vector2f(-this->moveSpeed, 0.f));
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->shape.move(sf::Vector2f(this->moveSpeed, 0.f));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->shape.move(sf::Vector2f(0.f, -this->moveSpeed));
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->shape.move(sf::Vector2f(0.f, this->moveSpeed));
}

void Player::updateWindowBoundCollision(const sf::RenderWindow* target)
{
	if (this->shape.getGlobalBounds().left <= 0.f)
		this->shape.setPosition(0.f, this->shape.getGlobalBounds().top);
	else if (this->shape.getGlobalBounds().left + this->shape.getGlobalBounds().width>= target->getSize().x)
		this->shape.setPosition(target->getSize().x - this->shape.getGlobalBounds().width,this->shape.getGlobalBounds().top);
	if (this->shape.getGlobalBounds().top <= 0.f)
		this->shape.setPosition(this->shape.getGlobalBounds().left,0.f);
	else if (this->shape.getGlobalBounds().top + this->shape.getGlobalBounds().height >= target->getSize().y)
		this->shape.setPosition(this->shape.getGlobalBounds().left, target->getSize().y - this->shape.getGlobalBounds().height);
}

void Player::update(const sf::RenderWindow* target)
{
	this->updateInput();
	this->updateWindowBoundCollision(target);
}

void Player::render(sf::RenderWindow* target)
{
	target->draw(this->shape);
}
