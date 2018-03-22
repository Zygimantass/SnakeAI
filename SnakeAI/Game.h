#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <vector>
#include <random>

#include "renderable/Renderable.h"
#include "renderable/Food.h"
#include "renderable/Snake.h"

#include "screen/SplashScreen.h"
#include "screen/PauseScreen.h"
#include "screen/DeathScreen.h"
#include "screen/GameScreen.h"

class Game
{
public:
	// consts

	static const int FRAMES_PER_SECOND = 60;
	static const int SCREEN_WIDTH = 1024;
	static const int SCREEN_HEIGHT = 768;

	// singleton

	static Game* getInstance();

	// functions

	bool init();
	void start();

	// food

	std::vector<Food*> foods;

	void addFood(int cnt);

	// rng

	std::random_device rd;
	std::mt19937 gen;

	int getRandomInt(int min, int max);

	// misc

	sf::Font getFont();

	enum GameState {
		Uninitialized, ShowingSplash, Paused,
		ShowingMenu, Playing, GameOver, Exiting
	};

	void switchGameState(GameState state);
	
	void exit();

	// snake

	Snake* getSnake();

	// clock

	sf::Clock getRenderClock();

private:
	// singleton

	Game() {};
	Game(Game const &) {};
	Game& operator=(Game const &) {};
	static Game* m_pInstance;

	// screens

	SplashScreen *splashScreen;
	PauseScreen *pauseScreen;
	DeathScreen *deathScreen;
	GameScreen *gameScreen;

	// loops

	void gameLoop();

	// exit

	bool isExiting();
	
	void setup();
	
	// vars

	sf::Clock renderClock;

	sf::RenderWindow _window;
	GameState _gameState = Uninitialized;

	sf::Font font;

	Snake* snake;
};