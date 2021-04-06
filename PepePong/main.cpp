#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "State.h"
#define	WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
int main() {
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "PepePong");
	State currentState = State(0);
	while (window.isOpen())
	{
		/*Exit Management System */
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		
		/*
		State 0 Conditons Game Menu
		*/
		if (currentState.getState() == MENU)
			std::cout << MENU << std::endl;
		else if (currentState.getState() == GAME)
			std::cout << GAME << std::endl;
		else if (currentState.getState() == EXIT_GAME)
			std::cout << EXIT_GAME << std::endl;
		window.clear();
		window.display();
	}

	return 0;
}