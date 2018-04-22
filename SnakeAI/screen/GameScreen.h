#pragma once
#include "Screen.h"
#include <SFML/Graphics.hpp>

class GameScreen : public Screen
{
public:
	GameScreen(sf::RenderWindow *sf) : Screen(sf) {
		this->sf = sf;
		this->setup();
	};
	~GameScreen();

	void loop() override;
	void processEvents();
	void setup();
private:
	void display();
	void update(float dt);
	
	sf::Clock renderClock;

};

