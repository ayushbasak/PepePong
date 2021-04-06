#pragma once
#pragma warning(push, 0)
#include <SFML/Graphics.hpp>
#pragma warning(pop)
class Player
{
private:
	float speed = 0.0f;
	float width = 20.f;
	float height = 50.f;
	sf::Vector2f position;
	sf::RectangleShape rect;

public:

	Player(sf::Vector2f pos);
	sf::Vector2f getPosition();
	void setColor(int r,int g, int b);
	void move(float right, float down);
	sf::RectangleShape shape();
};
