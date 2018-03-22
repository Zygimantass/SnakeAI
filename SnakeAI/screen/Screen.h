#pragma once
#include <SFML/Graphics.hpp>

class Screen {
public:
	Screen() {};
	Screen(sf::RenderWindow *sf);
	~Screen();

	virtual void loop();
	virtual void processEvents();
	
	void enable();
	void disable();
	void toggle();
	bool isActive();
protected:
	sf::RenderWindow *sf;

	bool active = false;
};

