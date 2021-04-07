#pragma once
#pragma warning(push, 0)
#include <SFML/Graphics.hpp>
#pragma warning(pop)
#define PLAYER_WIDTH 20.0f
#define PLAYER_HEIGHT 100.0f
class Player
{
private:
	const float baseSpeed = 10.0f; //reference speed 
	float speed = 0.0f;
	float width = PLAYER_WIDTH;
	float height = PLAYER_HEIGHT;
	sf::Vector2f position;
	sf::RectangleShape rect;

public:

	Player(sf::Vector2f pos);
	sf::Vector2f getPosition();
	void setColor(int r,int g, int b);
	void move(float right, float down);
	void move(int direction,  bool boost);
	void setPosition(sf::Vector2f pos);
	sf::RectangleShape shape();
};
