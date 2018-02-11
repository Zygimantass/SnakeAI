#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"


class Game
{
public:
	bool init();
	void start();
private:
	void gameLoop();
	void splashLoop();

	bool isExiting();
	void exit();
	
	void setup();

	void processEvents();
	void update();
	void display();

	enum GameState {
		Uninitialized, ShowingSplash, Paused,
		ShowingMenu, Playing, Exiting
	};

	static const int FRAMES_PER_SECOND = 60;
	static const int SCREEN_WIDTH = 1600;
	static const int SCREEN_HEIGHT = 900;

	sf::Clock renderClock;

	sf::RenderWindow _window;
	GameState _gameState = Uninitialized;

	sf::Font font;
	sf::Text splashText;
};