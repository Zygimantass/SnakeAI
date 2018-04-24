#pragma once
#include "Screen.h"
#include <SFML/Graphics.hpp>
#include "../ui/UIButton.h"

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
private:
	void reset();

	sf::Font font;
	sf::Text pauseText;

	UIButton resetButton;
};

