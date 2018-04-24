#pragma once
#include "../Screen.h"
#include "../../ui/UIButton.h"
#include <SFML/Graphics.hpp>

// MainMenu Screen inherits Screen
class MainScreen : public Screen
{
public:
	//ctor takes renderwindow
	MainScreen(sf::RenderWindow *sf) : Screen(sf) {
		this->sf = sf;
		this->setup();
	}
	~MainScreen();

	// setup, loop, events
	void setup();
	void loop() override;
	void processEvents();
private:
	sf::RenderWindow *sf;

	// choice buttons and functions

	void exit();
	void play();
	void about();

	UIButton playButton;
	UIButton exitButton;
	UIButton aboutButton;

	// title text and font
	
	sf::Font font;
	sf::Text titleText;
};

