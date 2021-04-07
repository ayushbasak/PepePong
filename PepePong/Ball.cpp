#include "Ball.h"
Ball::Ball(sf::Vector2f pos)
{
	position = pos;
	ball.setRadius(BALL_RADIUS);
	ball.setPosition(position);
}

sf::CircleShape Ball::shape()
{
	return ball;
}

void Ball::hit(int WALL)
{
	/*
	0 for WALLS, 1, for paddles
	*/
	if (WALL == 0)
		speed.y = -1 * speed.y;
	else if (WALL == 1)
		speed.x = -1 * speed.x;
}

void Ball::move()
{
	ball.move(speed);
}

sf::Vector2f Ball::getPosition()
{
	return ball.getPosition();
}

void Ball::setPosition(sf::Vector2f pos)
{
	position = pos;
	ball.setPosition(position);
}
