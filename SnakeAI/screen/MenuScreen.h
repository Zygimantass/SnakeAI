#pragma once
#include "Screen.h"
#include <SFML/Graphics.hpp>
#include "menu/MainScreen.h"
#include "menu/PlayerCountScreen.h"
#include "menu/AboutScreen.h"

// screen for menu, inherited screen
class MenuScreen : public Screen
{
public:
	// ctor, takes renderwindow
	MenuScreen(sf::RenderWindow *sf) : Screen(sf) {
		this->sf = sf;
		this->setup();

		// creating other menu screens
		this->mainScreen = new MainScreen(this->sf);
		this->playerCountScreen = new PlayerCountScreen(this->sf);
		this->aboutScreen = new AboutScreen(this->sf);
	}
	~MenuScreen();

	// setup and loop
	void setup();
	void loop() override;
	
	// menu states

	enum MenuState {
		Main, PlayerCount, About
	};

	void switchMenuState(MenuState state);
private:
	sf::RenderWindow *sf;

	MenuState currentState;

	// other menu screens
	MainScreen *mainScreen;
	PlayerCountScreen *playerCountScreen;
	AboutScreen *aboutScreen;
};

