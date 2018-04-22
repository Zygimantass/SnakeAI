#pragma once
#include "Screen.h"
#include <SFML/Graphics.hpp>
#include "menu/MainScreen.h"
#include "menu/PlayerCountScreen.h"
#include "menu/AboutScreen.h"

class MenuScreen : public Screen
{
public:
	MenuScreen(sf::RenderWindow *sf) : Screen(sf) {
		this->sf = sf;
		this->setup();

		this->mainScreen = new MainScreen(this->sf);
		this->playerCountScreen = new PlayerCountScreen(this->sf);
		this->aboutScreen = new AboutScreen(this->sf);
	}
	~MenuScreen();

	void setup();
	void loop() override;
	
	enum MenuState {
		Main, PlayerCount, About
	};

	void switchMenuState(MenuState state);
private:
	sf::RenderWindow *sf;

	MenuState currentState;

	MainScreen *mainScreen;
	PlayerCountScreen *playerCountScreen;
	AboutScreen *aboutScreen;
};

