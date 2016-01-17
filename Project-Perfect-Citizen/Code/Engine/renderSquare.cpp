#include <SFML/Graphics.hpp>
#include "renderSquare.h"


RenderSquare::RenderSquare() {
	sf::Vector2f tempVec;
	tempVec.x = 10.f;
	tempVec.y = 10.f;
	this->rect = new sf::RectangleShape(tempVec);
	rect->setFillColor(sf::Color::Red);
}

void RenderSquare::render(sf::RenderWindow* wnd) {
	wnd->draw(*(this->rect));
}

