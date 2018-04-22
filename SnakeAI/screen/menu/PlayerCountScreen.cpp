#include "PlayerCountScreen.h"
#include "../../Game.h"

void PlayerCountScreen::setup() {
	if (!font.loadFromFile("./resources/arial.ttf")) return;

	playerCountText.setString("Pasirinkite žaidėjų kiekį:");
	playerCountText.setCharacterSize(50);
	playerCountText.setFillColor(sf::Color::White);
	playerCountText.setFont(font);

	sf::FloatRect textRect = playerCountText.getLocalBounds();
	playerCountText.setOrigin((textRect.left + textRect.width) / 2.0f, 0.0);
	playerCountText.setPosition((float) (Game::getInstance()->SCREEN_WIDTH / 2), (float) 150);

	this->onePlayerButton = UIButton(this->sf, (Game::getInstance()->SCREEN_WIDTH / 2) - 225, 250, 200, 50, L"Vienas žaidėjas", 20, "./resources/arial.ttf");
	this->onePlayerButton.bind(std::bind(&PlayerCountScreen::onePlayer, this));

	this->twoPlayerButton = UIButton(this->sf, (Game::getInstance()->SCREEN_WIDTH / 2) + 25, 250, 200, 50, L"Du žaidėjai", 20, "./resources/arial.ttf");
	this->twoPlayerButton.bind(std::bind(&PlayerCountScreen::twoPlayer, this));
}

void PlayerCountScreen::processEvents() {
	sf::Event currEvent;

	while (sf->pollEvent(currEvent)) {
		if (currEvent.type == sf::Event::Closed) {
			Game::getInstance()->exit();
		}

		if (currEvent.type == sf::Event::MouseButtonReleased) {
			this->onePlayerButton.click(currEvent);
			this->twoPlayerButton.click(currEvent);
		}
	}
}

void PlayerCountScreen::onePlayer() {
	Game::getInstance()->setPlayerCount(1);
	Game::getInstance()->reset();
	Game::getInstance()->switchGameState(Game::Playing);
}

void PlayerCountScreen::twoPlayer() {
	Game::getInstance()->setPlayerCount(2);
	Game::getInstance()->reset();
	Game::getInstance()->switchGameState(Game::Playing);
}

void PlayerCountScreen::loop() {
	processEvents();

	sf->clear(sf::Color::Black);
	sf->draw(playerCountText);
	onePlayerButton.display();
	twoPlayerButton.display();

	sf->display();
}