#include "MenuScreen.h"

// setup for screen
void MenuScreen::setup() {
	this->currentState = Main;
}

// main loop
void MenuScreen::loop() {
	switch (this->currentState) {
	case Main:
		mainScreen->loop();
		break;
	case PlayerCount:
		playerCountScreen->loop();
		break;
	case About:
		aboutScreen->loop();
	}
}

// switching menu state
void MenuScreen::switchMenuState(MenuScreen::MenuState state) {
	this->currentState = state;
}