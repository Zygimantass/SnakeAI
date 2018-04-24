#pragma once
#include <SFML/Graphics.hpp>

// Renderable base class
class Renderable {
public:
	// ctor and dtor
	Renderable() {};
	Renderable(sf::RenderWindow *sf);
	~Renderable();

	// size and location
	sf::Vector2f getSize();
	sf::Vector2f getLocation();

	// functions, meant to be overrode
	virtual void display();
	virtual void update(float dt);
protected:
	// renderwindow
	sf::RenderWindow *sf;

	// size and location
	int width, height = 0;
	int x, y = 0;
};