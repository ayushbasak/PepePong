#pragma once
#include <SFML/Graphics.hpp>
class Ball
{
private:
	sf::Vector2f position;
	sf::Vector2f speed;
	sf::CircleShape ball;

public:
	Ball(sf::Vector2f pos);
	sf::CircleShape shape();
};

