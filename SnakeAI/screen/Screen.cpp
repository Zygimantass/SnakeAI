#include "Screen.h"

Screen::Screen(sf::RenderWindow *sf) {
}

Screen::~Screen() {
}

void Screen::loop() {
	if (!this->active) return;
}

void Screen::processEvents() {
}

void Screen::enable() {
	this->active = true;
}

void Screen::disable() {
	this->active = false;
}

void Screen::toggle() {
	this->active = !this->active;
}

bool Screen::isActive() {
	return this->active;
}