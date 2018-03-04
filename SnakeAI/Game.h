#pragma once
#include "Renderable.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Snake.h"
#include <vector>

class Game
{
public:
	static const int FRAMES_PER_SECOND = 60;
	static const int SCREEN_WIDTH = 800;
	static const int SCREEN_HEIGHT = 450;

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

	sf::Clock renderClock;

	sf::RenderWindow _window;
	GameState _gameState = Uninitialized;

	sf::Font font;
	sf::Text splashText;
	
	std::vector<Renderable*> renderables;

	Snake* snake;
};