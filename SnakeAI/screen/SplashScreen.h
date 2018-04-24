#pragma once
#include "Screen.h"
#include <SFML/Graphics.hpp>

// SplashScreen, inherits Screen
class SplashScreen: public Screen
{
public:
	// ctor, takes renderwindow
	SplashScreen(sf::RenderWindow *sf) : Screen(sf) {
		this->sf = sf;
		this->setup();
	};
	~SplashScreen();

	// loop, events, setup
	void loop() override;
	void processEvents();
	void setup();
private:
	// splash text and font
	sf::Text splashText;
	sf::Font font;
};

