#pragma once
#include "../Screen.h"
#include <SFML/Graphics.hpp>
#include "../../ui/UIButton.h"

class PlayerCountScreen : public Screen
{
public:
	PlayerCountScreen(sf::RenderWindow *sf) : Screen(sf) {
		this->sf = sf;
		this->setup();
	};
	~PlayerCountScreen();

	void loop() override;
	void processEvents();
	void setup();
private:
	void onePlayer();
	void twoPlayer();
	void playerVsAI();
	void AIVsAI();

	UIButton onePlayerButton;
	UIButton twoPlayerButton;
	UIButton playerVsAIButton;
	UIButton AIVsAIButton;

	sf::Font font;
	sf::Text playerCountText;
};

