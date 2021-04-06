#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "State.h"
#define	WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
int main() {
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "PepePong");
	State currentState = State(0);

	/*EXTRAS */
	sf::Font boldFont;
	if (!boldFont.loadFromFile("Assets/Roboto-Bold.ttf"))
		return EXIT_FAILURE;
	sf::Texture pepeTexture01;
	if (!pepeTexture01.loadFromFile("Assets/pepe-1.jpg"))
		return EXIT_FAILURE;
	sf::Sprite pepeSprite01(pepeTexture01);
	sf::Music pepeSong;
	if (!pepeSong.openFromFile("Assets/pepesong.ogg"))
		return EXIT_FAILURE;
	pepeSong.setLoop(true);
	pepeSong.play();

	while (window.isOpen())
	{
		window.clear();
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
		if (currentState.getState() == MENU) {
			sf::Text menuText;
			menuText.setString("Pepe Pong");
			menuText.setFont(boldFont);
			menuText.setFillColor(sf::Color::White);
			menuText.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - 70, WINDOW_HEIGHT / 2 - 20));
			menuText.setCharacterSize(50);
			sf::Text press;
			press.setString("Click To Start");
			press.setFont(boldFont);
			press.setCharacterSize(20);
			press.setFillColor(sf::Color::White);
			press.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - 70, WINDOW_HEIGHT / 2 +40));
			window.draw(pepeSprite01);
			window.draw(menuText);
			window.draw(press);

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				currentState.setState(1);
				pepeSong.stop();
			}
		}
		else if (currentState.getState() == GAME)
			std::cout << GAME << std::endl;
		else if (currentState.getState() == EXIT_GAME)
			std::cout << EXIT_GAME << std::endl;
		window.display();
	}

	return 0;
}