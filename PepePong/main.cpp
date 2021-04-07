#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "State.h"
#include "Ball.h"
#define	WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
int main() {
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "PepePong");
	window.setFramerateLimit(30);
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

	sf::Texture pepeTexture02;
	if (!pepeTexture02.loadFromFile("Assets/kekistan.jpg"))
		return EXIT_FAILURE;
	sf::Sprite pepeSprite02(pepeTexture02);
	sf::SoundBuffer hitBuffer;
	sf::Sound hit(hitBuffer);

	/*TEMP Structure*/
	Player leftPlayer = Player(sf::Vector2f(10.0, WINDOW_HEIGHT / 2 - PLAYER_HEIGHT / 5));
	Player rightPlayer = Player(sf::Vector2f(WINDOW_WIDTH - PLAYER_WIDTH - 10.0, WINDOW_HEIGHT / 2 - PLAYER_HEIGHT / 5));
	Ball ball = Ball(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));

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
			press.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - 70, WINDOW_HEIGHT / 2 + 40));
			window.draw(pepeSprite01);
			window.draw(menuText);
			window.draw(press);

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				currentState.setState(1);
				pepeSong.stop();
			}
		}
		/* 
		State 1: Game Scene
		*/
		else if (currentState.getState() == GAME) {
			window.draw(pepeSprite02);
			window.draw(leftPlayer.shape());
			window.draw(rightPlayer.shape());
			window.draw(ball.shape());

			//Quit mid Game
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				return EXIT_SUCCESS;

			/*
			Player 1 Controls
			*/

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
				if (leftPlayer.getPosition().y >= PLAYER_HEIGHT / 4) {
					leftPlayer.move(-1, false);
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				if (leftPlayer.getPosition().y <= WINDOW_HEIGHT - PLAYER_HEIGHT - PLAYER_HEIGHT/4) {
					leftPlayer.move(1, false);
				}
			}

			/*
			Player 2 Controls
			*/

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				if (rightPlayer.getPosition().y >= PLAYER_HEIGHT / 4) {
					rightPlayer.move(1, false);
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				if (rightPlayer.getPosition().y <= WINDOW_HEIGHT - PLAYER_HEIGHT - PLAYER_HEIGHT / 4) {
					rightPlayer.move(-1, false);
				}
			}
		}
		else if (currentState.getState() == EXIT_GAME)
			std::cout << EXIT_GAME << std::endl;
		window.display();
	}

	return 0;
}