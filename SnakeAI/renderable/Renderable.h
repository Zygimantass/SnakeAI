#pragma once
#include <SFML/Graphics.hpp>

class Renderable {
public:
	Renderable() {};
	Renderable(sf::RenderWindow *sf);
	~Renderable();

	sf::Vector2f getSize();
	sf::Vector2f getLocation();

	virtual void display();
	virtual void update(float dt);
protected:
	sf::RenderWindow *sf;
	int width, height = 0;
	int x, y = 0;
};