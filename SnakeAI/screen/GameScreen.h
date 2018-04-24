#pragma once
#include "Screen.h"
#include <SFML/Graphics.hpp>

// GameScreen, inherits Screen
class GameScreen : public Screen
{
public:
	// ctor, takes renderwindow
	GameScreen(sf::RenderWindow *sf) : Screen(sf) {
		this->sf = sf;
		this->setup();
	};
	~GameScreen();

	// loop, events and setup
	void loop() override;
	void processEvents();
	void setup();
private:
	// display and update
	void display();
	void update(float dt);
	void displayScore();
	
	// render clock
	sf::Clock renderClock;

	// texts and fonts
	sf::Font font;

	sf::Text scoreOneText;
	sf::Text scoreTwoText;
};

