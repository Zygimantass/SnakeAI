#include <SFML/Graphics.hpp>
#include "Game.h";

int main()
{
	Game game;

	if (!game.init()) return EXIT_FAILURE;

	game.start();
	return 0;
}
