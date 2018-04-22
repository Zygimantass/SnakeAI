#include "Snake.h"
#include "../Game.h"
#include "Renderable.h"
#include "../util/Logging.h"
#include <sstream>
#include <SFML/Graphics.hpp>

Snake::~Snake()
{

}

// update, rendering

void Snake::display() {
	for (int idx = 1; idx < snake_length; ++idx) {
		this->sf->draw(body[idx]);
	}
	this->sf->draw(body[0]);
}

void Snake::update(float dt)
{
	if (sf::Keyboard::isKeyPressed(this->currentScheme[0]) && this->local) {
		this->switchDirection(sf::Vector2<int>(-1, 0));
	} else if (sf::Keyboard::isKeyPressed(this->currentScheme[1]) && this->local) {
		this->switchDirection(sf::Vector2<int>(1, 0));
	} else if (sf::Keyboard::isKeyPressed(this->currentScheme[2]) && this->local) {
		this->switchDirection(sf::Vector2<int>(0, -1));
	} else if (sf::Keyboard::isKeyPressed(this->currentScheme[3]) && this->local) {
		this->switchDirection(sf::Vector2<int>(0, 1));
	}

	if (secondsSinceLastMove > (1.0 / speed)) {
		int eatenFood = this->ateFood();
		
		if (eatenFood != -1) {
			Game::getInstance()->foods.erase(Game::getInstance()->foods.begin() + eatenFood);
			Game::getInstance()->addFood(1);
			this->addScore();
			this->speed += 1;
		}

		logger::print(this->secondsSinceLastMove);

		this->move(this->lastDir);
		this->secondsSinceLastMove = 0;
	}
	else {
		this->secondsSinceLastMove += dt;
	}
}

// movement

void Snake::move(sf::Vector2<int> direction) {
	snakeDirections.push_front(direction);
	snakeDirections.pop_back();

	std::list<sf::Vector2<int>>::iterator i = snakeDirections.begin();

	int index = 0;

	while (i != snakeDirections.end() && index < snake_length) {
		body[index].move((float) (16 * (*i).x), (float) (16 * (*i).y));
		index++;
		i++;
	}
}

void Snake::switchDirection(sf::Vector2<int> dir) {
	this->lastDir = dir;
}

// food

int Snake::ateFood() {
	if (needToUpdateLength) {
		snake_length++;
		needToUpdateLength = false;
	}

	int idx = 0;
	for (auto& fd : Game::getInstance()->foods) {
		Food food = *fd;
		sf::RectangleShape fdRect = Utils::getRectangleAt(fd->getLocation(), fd->getSize(), sf::Color::White);
		if (this->body[0].getGlobalBounds().intersects(fdRect.getGlobalBounds())) {
			sf::Vector2f newLoc = this->body[snake_length - 1].getPosition();
			body.push_back(Utils::getRectangleAt(newLoc, sf::Vector2f((float) Snake::SIZE, (float) Snake::SIZE), bodyColor));
			snakeDirections.push_back(lastDir);
			needToUpdateLength = true;
			return idx;
		}
		idx++;
	}
	return -1;
}

// death

bool Snake::died() {
	for (int i = 1; i < snake_length; i++) {
		if (this->collidesHead(body[i].getPosition())) {
			return true;
		}
	}

	if (Game::getInstance()->getPlayerCount() == 2) {
		if (playerIndex == 0) {
			if (this->collidesHead(Game::getInstance()->getSecondSnake()->body[0].getPosition())) return true;

			for (int i = 0; i < Game::getInstance()->getSecondSnake()->snake_length; i++) {
				if (this->collides(Game::getInstance()->getSecondSnake()->body[i].getPosition())) return true;
			}
		}
		else {
			if (this->collidesHead(Game::getInstance()->getSnake()->body[0].getPosition())) return true;

			for (int i = 0; i < Game::getInstance()->getSnake()->snake_length; i++) {
				if (this->collides(Game::getInstance()->getSnake()->body[i].getPosition())) return true;
			}
		}
	}

	int x = (int) body[0].getGlobalBounds().left;
	int y = (int) body[0].getGlobalBounds().top;

	int mx = sf->getSize().x;
	int my = sf->getSize().y;

	return (x >= mx || x < 0) || (y >= my || y < 0);
}

// debugging

std::ostringstream Snake::printBody() {
	std::ostringstream bodyString;

	bodyString << "[Head] loc: (" << body[0].getPosition().x << ", " << body[0].getPosition().y << ")";
	for (int i = 1; i < this->snake_length; i++) {
		bodyString << "[Body " << i << "] loc: (" << body[i].getPosition().x << ", " << body[i].getPosition().y << ")";
	}	

	return bodyString;
}

// collision

bool Snake::collidesBody(sf::Vector2f pos){
	for (int i = 1; i < snake_length; i++) {
		if (body[i].getGlobalBounds().contains(pos)) {
			return true;
		}
	}

	return false;
}

bool Snake::collidesHead(sf::Vector2f pos) {
	return body[0].getGlobalBounds().contains(pos);
}

bool Snake::collides(sf::Vector2f pos) {
	return this->collidesBody(pos) || this->collidesHead(pos);
}

// misc. snake methods

int Snake::getScore() {
	return this->score;
}

void Snake::addScore() {
	this->score++;
}

void Snake::addScore(int score) {
	this->score += score;
}