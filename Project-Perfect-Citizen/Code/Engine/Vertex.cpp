#include "Vertex.h"

ppc::Vertex::Vertex() {
}

ppc::Vertex::Vertex(sf::Vector2f pos, sf::Color col) {
	color_ = col;
	pos_ = pos;
}

ppc::Vertex::Vertex(float x, float y, sf::Color col) {
	color_ = col;
	pos_ = { x,y };
}

ppc::Vertex::~Vertex() {
}

sf::Color ppc::Vertex::getColor() const {
	return color_;
}

void ppc::Vertex::setColor(sf::Color col) {
	color_ = col;
}

sf::Vector2f ppc::Vertex::getPos() const {
	return pos_;
}

void ppc::Vertex::setPos(sf::Vector2f pos) {
	pos_ = pos;
}

void ppc::Vertex::setPos(float x, float y) {
	pos_ = { x,y };
}

void ppc::Vertex::draw(sf::RenderTarget& target,
	sf::RenderStates states) const {


	
}
