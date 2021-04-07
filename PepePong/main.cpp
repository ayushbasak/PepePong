#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "State.h"
#include "Ball.h"
#include "Score.h"
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
	if (!hitBuffer.loadFromFile("Assets/hit.wav"))
		return EXIT_FAILURE;
	sf::Sound hit(hitBuffer);
	sf::Music pepeSongMuffled;
	if (!pepeSongMuffled.openFromFile("Assets/pepesong-muffled.ogg"))
		return EXIT_FAILURE;
	pepeSongMuffled.setLoop(true);
	sf::Font regularFont;
	if (!regularFont.loadFromFile("Assets/Roboto-Regular.ttf"))
		return EXIT_FAILURE;
	sf::SoundBuffer winGameBuffer;
	if (!winGameBuffer.loadFromFile("Assets/end.wav"))
		return EXIT_FAILURE;
	sf::Sound winGame(winGameBuffer);

	/*TEMP Structure*/
	Player leftPlayer = Player(sf::Vector2f(10.0, WINDOW_HEIGHT / 2 - PLAYER_HEIGHT / 5));
	Player rightPlayer = Player(sf::Vector2f(WINDOW_WIDTH - PLAYER_WIDTH - 10.0, WINDOW_HEIGHT / 2 - PLAYER_HEIGHT / 5));
	Ball ball = Ball(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));
	Score score = Score();

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
			press.setString("Click To Start\n\nControls:\n\n\nW | S : Player 1\n\nUP | DOWN : Player 2");
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
			sf::Text scoreText1;
			scoreText1.setString(std::to_string(score.getScore1()));
			scoreText1.setFont(regularFont);
			scoreText1.setFillColor(sf::Color::White);
			scoreText1.setCharacterSize(30);
			scoreText1.setPosition(sf::Vector2f(30.0, 20.0));

			sf::Text scoreText2;
			scoreText2.setString(std::to_string(score.getScore2()));
			scoreText2.setFont(regularFont);
			scoreText2.setFillColor(sf::Color::White);
			scoreText2.setCharacterSize(30);
			scoreText2.setPosition(sf::Vector2f(WINDOW_WIDTH - 50.0, 20.0));

			if (!(pepeSongMuffled.getStatus() == sf::Music::Status::Playing))
				pepeSongMuffled.play();
			window.draw(pepeSprite02);
			window.draw(scoreText1);
			window.draw(scoreText2);
			window.draw(leftPlayer.shape());
			window.draw(rightPlayer.shape());
			window.draw(ball.shape());

			//Quit mid Game
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				return EXIT_SUCCESS;

			/*
			Player 1 Controls
			*/
			sf::Vector2f leftPlayerPosition = leftPlayer.getPosition();
			sf::Vector2f rightPlayerPosition = rightPlayer.getPosition();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
				if (leftPlayerPosition.y >= PLAYER_HEIGHT / 4) {
					leftPlayer.move(-1, false);
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				if (leftPlayerPosition.y <= WINDOW_HEIGHT - PLAYER_HEIGHT - PLAYER_HEIGHT / 4) {
					leftPlayer.move(1, false);
				}
			}

			/*
			Player 2 Controls
			*/

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				if (rightPlayerPosition.y <= WINDOW_HEIGHT - PLAYER_HEIGHT - PLAYER_HEIGHT / 4) {
					rightPlayer.move(1, false);
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				if (rightPlayerPosition.y >= PLAYER_HEIGHT / 4) {
					rightPlayer.move(-1, false);
				}
			}

			/*
			BALL mechanics
			*/
			sf::Vector2f ballPosition = ball.getPosition();;
			if (ballPosition.y <= 0 || ballPosition.y >= WINDOW_HEIGHT - BALL_RADIUS*2) {
				ball.hit(0);
				hit.play();
			}
			//leftPlayer hits
			
			if (ballPosition.x <= PLAYER_WIDTH){
				if (ballPosition.y + BALL_RADIUS / 2 >= leftPlayerPosition.y && ballPosition.y + BALL_RADIUS <= leftPlayerPosition.y + PLAYER_HEIGHT) {
					ball.hit(1);
					hit.play();
				}
				else {
					std::cout << "PLAYER 2 WINS" << std::endl;
					winGame.play();
					score.setScore2(score.getScore2() + 1);
					ball.setPosition(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));
					leftPlayer.setPosition(sf::Vector2f(sf::Vector2f(10.0, WINDOW_HEIGHT / 2 - PLAYER_HEIGHT / 5)));
				}
			}
			if(ballPosition.x >= WINDOW_WIDTH - PLAYER_WIDTH - BALL_RADIUS*2){
				if (ballPosition.y + BALL_RADIUS / 2 >= rightPlayerPosition.y && ballPosition.y + BALL_RADIUS <= rightPlayerPosition.y + PLAYER_HEIGHT) {
					ball.hit(1);
					hit.play();
				}
				else {
					std::cout << "PLAYER 1 WINS" << std::endl;
					winGame.play();
					score.setScore1(score.getScore1() + 1);
					ball.setPosition(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));
					rightPlayer.setPosition(sf::Vector2f(WINDOW_WIDTH - PLAYER_WIDTH - 10.0, WINDOW_HEIGHT / 2 - PLAYER_HEIGHT / 5));
				}
			}
			
			ball.move();
		}
		else if (currentState.getState() == EXIT_GAME)
			std::cout << EXIT_GAME << std::endl;
		window.display();
	}

	return 0;
}