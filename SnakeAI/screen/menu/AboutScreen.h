#pragma once
#include "../Screen.h"
#include <SFML/Graphics.hpp>
#include "../../ui/UIButton.h"

// Screen provides info about game, inherits Screen
class AboutScreen : public Screen
{
public:
	// ctor, takes renderwindow
	AboutScreen(sf::RenderWindow *sf) : Screen(sf) {
		this->screen = sf;
		this->setup();
	}
	~AboutScreen();

	// loop, events, setup
	void loop() override;
	void processEvents();
	void setup();
private:
	// sfscreen
	sf::RenderWindow *screen;
	
	// about text, font, backButton
	sf::Text aboutText;
	sf::Font font;
	UIButton backButton;

	void back();
};

