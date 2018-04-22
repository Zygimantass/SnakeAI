#pragma once
#include "Screen.h"
#include <SFML/Graphics.hpp>
#include "menu/MainScreen.h"
#include "menu/PlayerCountScreen.h"

class MenuScreen : public Screen
{
public:
	MenuScreen(sf::RenderWindow *sf) : Screen(sf) {
		this->sf = sf;
		this->setup();

		this->mainScreen = new MainScreen(this->sf);
		this->playerCountScreen = new PlayerCountScreen(this->sf);
	}
	~MenuScreen();

	void setup();
	void loop() override;
	
	enum MenuState {
		Main, PlayerCount
	};

	void switchMenuState(MenuState state);
private:
	sf::RenderWindow *sf;

	MenuState currentState;

	MainScreen *mainScreen;
	PlayerCountScreen *playerCountScreen;
};

