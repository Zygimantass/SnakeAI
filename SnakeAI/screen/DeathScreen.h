#pragma once
#include "Screen.h"
#include <SFML/Graphics.hpp>
#include "../ui/UIButton.h"

class DeathScreen : public Screen
{
public:
	DeathScreen(sf::RenderWindow *sf) : Screen(sf) {
		this->screen = sf;
		this->setup();
	};
	~DeathScreen();

	void setScore(int score);

	void loop() override;
	void processEvents();
	void setup();
private:
	sf::RenderWindow *screen;
	sf::Text scoreText;
	sf::Font font;

	void reset();

	UIButton resetButton;

	int score;
};

