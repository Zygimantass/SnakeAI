#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <vector>
#include <random>

#include "util/Constants.h"

#include "renderable/Renderable.h"
#include "renderable/Food.h"
#include "renderable/Snake.h"

#include "models/Point.cpp"

#include "screen/SplashScreen.h"
#include "screen/PauseScreen.h"
#include "screen/DeathScreen.h"
#include "screen/GameScreen.h"
#include "screen/MenuScreen.h"
#include "screen/TwoPlayerDeathScreen.h"

class Game
{
public:
	// consts

	static const int FRAMES_PER_SECOND = 3000;
	static const int SCREEN_WIDTH = Constants::SCREEN_WIDTH;
	static const int SCREEN_HEIGHT = Constants::SCREEN_HEIGHT;

	// singleton

	static Game* getInstance();

	// functions

	bool init();
	void reset();
	void start();

	// ai and normal player counts

	void setPlayerCount(int cnt) {
		this->playerCount = cnt;
	}

	int getPlayerCount() {
		return this->playerCount;
	}
	void setAIPlayerCount(int cnt) {
		this->aiPlayerCount = cnt;
	}

	int getAIPlayerCount() {
		return this->aiPlayerCount;
	}

	// food

	std::vector<Food*> foods;
	void addFood(int cnt);

	// rng

	std::random_device rd;
	std::mt19937 gen;

	int getRandomInt(int min, int max);

	// misc

	sf::Font getFont();

	// state managament

	enum GameState {
		Uninitialized, ShowingSplash, Paused,
		ShowingMenu, Playing, GameOver, TwoPlayerGameOver, Exiting
	};

	void switchGameState(GameState state);
	
	void exit();

	// snake

	Snake* getSnake();
	Snake* getSecondSnake();

	// safe path

	bool isSafe(Point point);

	// clock

	sf::Clock getRenderClock();

	MenuScreen *menuScreen;
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
	TwoPlayerDeathScreen *twoPlayerDeathScreen;
	GameScreen *gameScreen;

	// exit
	bool isExiting();
	void setup();
	
	// playercount

	int playerCount = 0;
	int aiPlayerCount = 0;

	// vars

	sf::RenderWindow _window;
	GameState _gameState = Uninitialized;

	sf::Font font;

	// snakes

	Snake* snake;
	Snake* secondSnake;
};