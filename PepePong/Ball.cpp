#include "Ball.h"

Ball::Ball(sf::Vector2f pos)
{
	position = pos;
	ball.setRadius(20.0f);
	ball.setPosition(position);
}

sf::CircleShape Ball::shape()
{
	return ball;
}
