#include "PlayerCountScreen.h"
#include "../../Game.h"

void PlayerCountScreen::setup() {
	if (!font.loadFromFile("./resources/arial.ttf")) return;

	// setting up and centering text

	playerCountText.setString(L"Pasirinkite žaidėjų kiekį:");
	playerCountText.setCharacterSize(50);
	playerCountText.setFillColor(sf::Color::White);
	playerCountText.setFont(font);

	sf::FloatRect textRect = playerCountText.getLocalBounds();
	playerCountText.setOrigin((textRect.left + textRect.width) / 2.0f, 0.0);
	playerCountText.setPosition((float) (Game::getInstance()->SCREEN_WIDTH / 2), (float) 150);

	// creating buttons and binding them to their functions

	this->onePlayerButton = UIButton(this->sf, (Game::getInstance()->SCREEN_WIDTH / 2) - 225, 250, 200, 50, L"Vienas žaidėjas", 20, "./resources/arial.ttf");
	this->onePlayerButton.bind(std::bind(&PlayerCountScreen::onePlayer, this));

	this->twoPlayerButton = UIButton(this->sf, (Game::getInstance()->SCREEN_WIDTH / 2) + 25, 250, 200, 50, L"1v1 žaidėjai", 20, "./resources/arial.ttf");
	this->twoPlayerButton.bind(std::bind(&PlayerCountScreen::twoPlayer, this));

	this->playerVsAIButton = UIButton(this->sf, (Game::getInstance()->SCREEN_WIDTH / 2) - 225, 325, 200, 50, L"Žaidėjas vs AI", 20, "./resources/arial.ttf");
	this->playerVsAIButton.bind(std::bind(&PlayerCountScreen::playerVsAI, this));

	this->AIVsAIButton = UIButton(this->sf, (Game::getInstance()->SCREEN_WIDTH / 2) + 25, 325, 200, 50, L"AI vs AI", 20, "./resources/arial.ttf");
	this->AIVsAIButton.bind(std::bind(&PlayerCountScreen::AIVsAI, this));
}

void PlayerCountScreen::processEvents() {
	sf::Event currEvent;
	// polling for exits or button clicks

	while (sf->pollEvent(currEvent)) {
		if (currEvent.type == sf::Event::Closed) {
			Game::getInstance()->exit();
		}

		if (currEvent.type == sf::Event::MouseButtonReleased) {
			this->onePlayerButton.click(currEvent);
			this->twoPlayerButton.click(currEvent);
			this->playerVsAIButton.click(currEvent);
			this->AIVsAIButton.click(currEvent);
		}
	}
}

// setting player count functions

void PlayerCountScreen::playerVsAI() {
	Game::getInstance()->setPlayerCount(2);
	Game::getInstance()->setAIPlayerCount(1);
	Game::getInstance()->reset();
	Game::getInstance()->switchGameState(Game::Playing);
}

void PlayerCountScreen::AIVsAI() {
	Game::getInstance()->setPlayerCount(2);
	Game::getInstance()->setAIPlayerCount(2);
	Game::getInstance()->reset();
	Game::getInstance()->switchGameState(Game::Playing);
}

void PlayerCountScreen::onePlayer() {
	Game::getInstance()->setPlayerCount(1);
	Game::getInstance()->setAIPlayerCount(0);
	Game::getInstance()->reset();
	Game::getInstance()->switchGameState(Game::Playing);
}

void PlayerCountScreen::twoPlayer() {
	Game::getInstance()->setPlayerCount(2);
	Game::getInstance()->setAIPlayerCount(0);
	Game::getInstance()->reset();
	Game::getInstance()->switchGameState(Game::Playing);
}

// main loop

void PlayerCountScreen::loop() {
	processEvents();

	sf->clear(sf::Color::Black);
	sf->draw(playerCountText);
	onePlayerButton.display();
	twoPlayerButton.display();
	playerVsAIButton.display();
	AIVsAIButton.display();

	sf->display();
}