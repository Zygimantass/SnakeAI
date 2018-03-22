#pragma once
#include "Screen.h"
#include <SFML/Graphics.hpp>

class DeathScreen : public Screen
{
public:
	DeathScreen(sf::RenderWindow *sf) : Screen(sf) {
		this->sf = sf;
		this->setup();
	};
	~DeathScreen();

	void setScore(int score);

	void loop() override;
	void processEvents();
	void setup();
private:
	sf::Text scoreText;
	sf::Font font;

	int score;
};

