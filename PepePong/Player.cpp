#include "Player.h"

Player::Player(sf::Vector2f pos)
{
	position = pos;
	rect.setSize(sf::Vector2f(width, height));
	rect.setPosition(position);
}

sf::Vector2f Player::getPosition()
{
	return position;
}

void Player::setColor(int r, int g, int b)
{
	rect.setFillColor(sf::Color(r,g,b));
}

void Player::move(float right, float down)
{
	rect.move(sf::Vector2f(right, down));
}

sf::RectangleShape Player::shape()
{
	return rect;
}
