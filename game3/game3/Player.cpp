#include "Player.h"

void Player::initVariables()
{
	coolTimeMax = 10.f;
	coolTime = coolTimeMax;
	hpMax = 100;
	hp = hpMax;
}

void Player::initTexture()
{
	this->texture.loadFromFile("textures/ship.png");
}

void Player::initSprite()
{
	sprite.setTexture(this->texture);
	sprite.setPosition(sf::Vector2f(300,500));

	//resize
	sprite.scale(0.1f, 0.1f);
}

Player::Player()
{
	initTexture();
	initSprite();
	initVariables();
}

Player::~Player()
{
}

void Player::move(const float x, const float y)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		sprite.move(-x, 0.f);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		sprite.move(x, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		sprite.move(0, -y);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		sprite.move(0, y);
}

const bool Player::canAttack()
{
	if (coolTime >= coolTimeMax)
	{
		coolTime = 0.f;
		return true;
	}
	return false;
}

void Player::setPosition(const float x, const float y)
{
	sprite.setPosition(x, y);
}

sf::FloatRect Player::getBounds()
{
	return sprite.getGlobalBounds();
}

const int& Player::getHp() const
{
	return hp;
}

void Player::setHp(int hp)
{
	this->hp = hp;
}

void Player::loseHp(int damage)
{
	hp -= damage;
}

const int& Player::getHpMax() const
{
	return hpMax;
}

const sf::Vector2f Player::getPos() const
{
	return sprite.getPosition();
}

void Player::updateAttack()
{
	if (this->coolTime < this->coolTimeMax)
		this->coolTime += .5f;
}

void Player::update()
{
	updateAttack();
	move(5.f,5.f);
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}