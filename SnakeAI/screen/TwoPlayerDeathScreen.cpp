#include "TwoPlayerDeathScreen.h"
#include "../Game.h"
#include "../util/Constants.h"

void TwoPlayerDeathScreen::setup() {
	if (!font.loadFromFile("./resources/arial.ttf")) return;

	scoreOneText.setFont(font);
	scoreOneText.setString("Player one score: ");
	scoreOneText.setFillColor(sf::Color::White);
	scoreOneText.setCharacterSize(40);

	scoreTwoText.setFont(font);
	scoreTwoText.setString("Player two score: ");
	scoreTwoText.setFillColor(sf::Color::White);
	scoreTwoText.setCharacterSize(40);

	victoryText.setFont(font);
	victoryText.setString("It's a draw!");
	victoryText.setFillColor(sf::Color::White);
	victoryText.setCharacterSize(55);

	resetButton = UIButton(this->screen, (Game::getInstance()->SCREEN_WIDTH / 2) - 150, 400, 300, 100, "Play again", 30, "./resources/arial.ttf");

	callback = std::bind(&TwoPlayerDeathScreen::reset, this);
	resetButton.bind(callback);
}

void TwoPlayerDeathScreen::setScore(int scoreOne, int scoreTwo, int victoriousPlayerIndex) {
	this->scoreOne = scoreOne;
	this->scoreTwo = scoreTwo;
	this->victoriousPlayerIndex = victoriousPlayerIndex;

	scoreOneText.setString("Player one score: " + std::to_string(scoreOne));
	scoreTwoText.setString("Player two score: " + std::to_string(scoreTwo));

	sf::FloatRect textOneRect = scoreOneText.getLocalBounds();
	scoreOneText.setOrigin((textOneRect.left + textOneRect.width) / 2.0f, 0);
	scoreOneText.setPosition((Constants::SCREEN_WIDTH / 2), 200);

	sf::FloatRect textTwoRect = scoreTwoText.getLocalBounds();
	scoreTwoText.setOrigin((textTwoRect.left + textTwoRect.width) / 2.0f, 0);
	scoreTwoText.setPosition((Constants::SCREEN_WIDTH / 2), 250);

	if (this->victoriousPlayerIndex == 0) {
		victoryText.setString("It's a draw!");
	}
	else if (this->victoriousPlayerIndex == 1) {
		victoryText.setString("Player one won!");
	}
	else if (this->victoriousPlayerIndex == 2) {
		victoryText.setString("Player two won!");
	}

	sf::FloatRect victoryTextRect = victoryText.getLocalBounds();
	victoryText.setOrigin((victoryTextRect.left + victoryTextRect.width) / 2.0f, 0);
	victoryText.setPosition((Constants::SCREEN_WIDTH / 2), 100);
}

void TwoPlayerDeathScreen::loop() {
	this->processEvents();

	screen->clear(sf::Color::Black);

	screen->draw(victoryText);
	screen->draw(scoreOneText);
	screen->draw(scoreTwoText);
	resetButton.display();

	screen->display();
}

void TwoPlayerDeathScreen::processEvents() {
	sf::Event currEvent;

	while (screen->pollEvent(currEvent)) {
		if (currEvent.type == sf::Event::Closed) {
			Game::getInstance()->exit();
		}

		if (currEvent.type == sf::Event::MouseButtonReleased) {
			resetButton.click(currEvent);
		}
	}
}

void TwoPlayerDeathScreen::reset() {
	Game::getInstance()->reset();
	Game::getInstance()->switchGameState(Game::ShowingMenu);
}