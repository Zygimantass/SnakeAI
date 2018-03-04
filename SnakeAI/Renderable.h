#pragma once
#include <SFML/Graphics.hpp>

class Renderable {
public:
	Renderable() {};
	Renderable(sf::RenderWindow *sf);
	~Renderable();

	virtual void display();
	virtual void update();
protected:
	sf::RenderWindow *sf;
	int width, height = 0;
	int x, y = 0;
};