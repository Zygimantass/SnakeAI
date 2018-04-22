#pragma once
#include "../Screen.h"
#include "../../ui/UIButton.h"
#include <SFML/Graphics.hpp>

class MainScreen : public Screen
{
public:
	MainScreen(sf::RenderWindow *sf) : Screen(sf) {
		this->sf = sf;
		this->setup();
	}
	~MainScreen();

	void setup();
	void loop() override;
	void processEvents();
private:
	sf::RenderWindow *sf;

	void exit();
	void play();

	UIButton playButton;
	UIButton exitButton;

	sf::Font font;
	sf::Text titleText;
};

