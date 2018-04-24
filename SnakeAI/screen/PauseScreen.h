#pragma once
#include "Screen.h"
#include <SFML/Graphics.hpp>
#include "../ui/UIButton.h"

// screen when you pause, inherited screen
class PauseScreen : public Screen
{
public:
	// ctor, takes renderwindow
	PauseScreen(sf::RenderWindow *sf) : Screen(sf) {
		this->sf = sf;
		this->setup();
	};
	~PauseScreen();

	// loop, events, setup
	void loop() override;
	void processEvents();
	void setup();
private:
	// resetting game
	void reset();

	// pause text n font
	sf::Font font;
	sf::Text pauseText;

	UIButton resetButton;
};

