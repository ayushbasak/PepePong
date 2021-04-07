#pragma once
#include <SFML/Graphics.hpp>
#define BALL_RADIUS 20.0f
class Ball
{
private:
	sf::Vector2f position;
	sf::Vector2f speed = sf::Vector2f(10.0, 5.0);
	sf::CircleShape ball;

public:
	Ball(sf::Vector2f pos);
	sf::CircleShape shape();
	void hit(int WALL);
	void move();
	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f pos);
};

