#pragma once
#include "Screen.h"
#include <SFML/Graphics.hpp>

class SplashScreen: public Screen
{
public:
	SplashScreen(sf::RenderWindow *sf) : Screen(sf) {
		this->sf = sf;
		this->setup();
	};
	~SplashScreen();

	void loop() override;
	void processEvents();
	void setup();
private:
	sf::Text splashText;
	sf::Font font;
};

