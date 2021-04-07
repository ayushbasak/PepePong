#include "Player.h"
#include <iostream>
Player::Player(sf::Vector2f pos)
{
	position = pos;
	rect.setSize(sf::Vector2f(width, height));
	rect.setPosition(position);
}

sf::Vector2f Player::getPosition()
{
	return rect.getPosition();;
}

void Player::setColor(int r, int g, int b)
{
	rect.setFillColor(sf::Color(r,g,b));
}

void Player::move(float right, float down)
{
	rect.move(sf::Vector2f(right, down));
}

void Player::move(int direction, bool boost)
{
	if (boost)
		speed = 2 * baseSpeed;
	else
		speed = baseSpeed;
	// direction = -1 (UP) ; +1 (DOWN)
	rect.move(sf::Vector2f(0.0, direction * speed));
	std::cout << "MOVE" << std::endl;;
}

sf::RectangleShape Player::shape()
{
	return rect;
}
