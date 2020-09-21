#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
class Player
{
private:
	sf::Sprite sprite;
	sf::Texture texture;

	float coolTime;
	float coolTimeMax;

	int hp;
	int hpMax;

	void initVariables();
	void initTexture();
	void initSprite();

public:
	Player();
	~Player();

	void move(const float x, const float y);

	const bool canAttack();

	void setPosition(const float x, const float y);

	sf::FloatRect getBounds();

	const int& getHp() const;
	void setHp(int hp);
	void loseHp(int damage);
	const int& getHpMax() const;
	const sf::Vector2f getPos() const;

	void updateAttack();
	void update();
	void render(sf::RenderTarget& target);
};