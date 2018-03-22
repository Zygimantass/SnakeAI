#pragma once
#include "Screen.h"
#include <SFML/Graphics.hpp>

class PauseScreen : public Screen
{
public:
	PauseScreen(sf::RenderWindow *sf) : Screen(sf) {
		this->sf = sf;
		this->setup();
	};
	~PauseScreen();

	void loop() override;
	void processEvents();
	void setup();
};

