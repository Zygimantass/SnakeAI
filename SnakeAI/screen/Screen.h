#pragma once
#include <SFML/Graphics.hpp>

// base class for Screen
class Screen {
public:
	Screen() {};
	Screen(sf::RenderWindow *sf);
	~Screen();

	// meant to be overridden
	virtual void loop();
	virtual void processEvents();
protected:
	sf::RenderWindow *sf;
};

