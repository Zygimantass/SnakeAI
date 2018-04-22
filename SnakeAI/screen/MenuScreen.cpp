#include "MenuScreen.h"

void MenuScreen::setup() {
	this->currentState = Main;
}

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

void MenuScreen::switchMenuState(MenuScreen::MenuState state) {
	this->currentState = state;
}