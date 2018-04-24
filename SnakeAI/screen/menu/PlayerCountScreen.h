#pragma once
#include "../Screen.h"
#include <SFML/Graphics.hpp>
#include "../../ui/UIButton.h"

// Screen for choosing players, inherits screen
class PlayerCountScreen : public Screen
{
public:
	// ctor, takes renderwindow
	PlayerCountScreen(sf::RenderWindow *sf) : Screen(sf) {
		this->sf = sf;
		this->setup();
	};
	~PlayerCountScreen();

	void loop() override;
	void processEvents();
	void setup();
private:
	// functions and their buttons
	void onePlayer();
	void twoPlayer();
	void playerVsAI();
	void AIVsAI();

	UIButton onePlayerButton;
	UIButton twoPlayerButton;
	UIButton playerVsAIButton;
	UIButton AIVsAIButton;

	// player count text and font
	sf::Font font;
	sf::Text playerCountText;
};

