#pragma once
#include "Screen.h"
#include <SFML/Graphics.hpp>
#include "../ui/UIButton.h"

class TwoPlayerDeathScreen : public Screen
{
public:
	TwoPlayerDeathScreen(sf::RenderWindow *sf) : Screen(sf) {
		this->screen = sf;
		this->setup();
	}
	~TwoPlayerDeathScreen();

	void setScore(int scoreOne, int scoreTwo, int victoriousPlayerIndex);

	void loop() override;
	void processEvents();
	void setup();
private:
	sf::RenderWindow *screen;
	
	sf::Text scoreOneText;
	sf::Text scoreTwoText;
	sf::Text victoryText;

	sf::Font font;

	void reset();

	UIButton resetButton;

	std::function<void(void)> callback;

	int scoreOne;
	int scoreTwo;
	int victoriousPlayerIndex;
};

