#pragma once
#include "../Screen.h"
#include <SFML/Graphics.hpp>
#include "../../ui/UIButton.h"

class AboutScreen : public Screen
{
public:
	AboutScreen(sf::RenderWindow *sf) : Screen(sf) {
		this->screen = sf;
		this->setup();
	}
	~AboutScreen();

	void loop() override;
	void processEvents();
	void setup();
private:
	sf::RenderWindow *screen;
	sf::Text aboutText;
	sf::Font font;
	UIButton backButton;

	void back();
};

