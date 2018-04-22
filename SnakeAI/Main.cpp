#include <SFML/Graphics.hpp>
#include "Game.h";

int main()
{
	if (!Game::getInstance()->init()) return EXIT_FAILURE;

	Game::getInstance()->start();
	return 0;
}
