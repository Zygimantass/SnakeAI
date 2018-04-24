#pragma once
#include "Screen.h"
#include <SFML/Graphics.hpp>
#include "../ui/UIButton.h"

// Screen for death, inherits Screen
class DeathScreen : public Screen
{
public:
	// ctor, takes renderwindow
	DeathScreen(sf::RenderWindow *sf) : Screen(sf) {
		this->screen = sf;
		this->setup();
	};
	~DeathScreen();

	// score mgmt
	void setScore(int score);

	// main loop
	void loop() override;
	void processEvents();
	void setup();
private:
	// screen, scoreText and its font
	sf::RenderWindow *screen;
	sf::Text scoreText;
	sf::Font font;

	// game reset
	void reset();
	UIButton resetButton;

	int score;
};

