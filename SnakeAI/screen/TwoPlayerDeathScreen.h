#pragma once
#include "Screen.h"
#include <SFML/Graphics.hpp>
#include "../ui/UIButton.h"

// DeathScreen for two players, inherits Screen
class TwoPlayerDeathScreen : public Screen
{
public:
	// ctor, takes window
	TwoPlayerDeathScreen(sf::RenderWindow *sf) : Screen(sf) {
		this->screen = sf;
		this->setup();
	}
	~TwoPlayerDeathScreen();

	// score mgmt
	void setScore(int scoreOne, int scoreTwo, int victoriousPlayerIndex);

	// loop, events, setup
	void loop() override;
	void processEvents();
	void setup();
private:
	// screen
	sf::RenderWindow *screen;
	
	// score, victory texts and font
	sf::Text scoreOneText;
	sf::Text scoreTwoText;
	sf::Text victoryText;

	sf::Font font;

	// resetting game
	void reset();

	UIButton resetButton;

	// scores and player

	int scoreOne;
	int scoreTwo;
	int victoriousPlayerIndex;
};

