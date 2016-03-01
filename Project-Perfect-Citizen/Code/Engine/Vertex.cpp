#ifdef WINDOWS_MARKER
#define resourcePath() string("Resources/")
#else
#include "ResourcePath.hpp"
#endif

#include "Vertex.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include "debug.h"
#include <iostream>
const int ppc::Vertex::fontSize_ = 20;
const float ppc::Vertex::radius_ = 30.f;

void ppc::Vertex::setTextPos() {

	text_.setPosition(getPosCenter());
}

ppc::Vertex::Vertex(){

	color_ = sf::Color::Yellow;

	circ_.setRadius(radius_);
	circ_.setFillColor(color_);
	circ_.setPosition(0,0);

	setTextPos();
	setTextFontLoad(resourcePath() + "consola.ttf");
}

ppc::Vertex::Vertex(sf::Vector2f pos, PipelineCharacter ch,
	sf::Color col = sf::Color::Yellow){

	color_ = col;
	char_ = ch;

	circ_.setRadius(radius_);
	circ_.setFillColor(color_);
	circ_.setPosition(pos);

	text_.setString(char_.getSSN().substr(0, 2));
	text_.setCharacterSize(fontSize_);
	text_.setColor(sf::Color::Black);

	setTextPos();
}

ppc::Vertex::Vertex(float x, float y, PipelineCharacter ch,
	sf::Color col = sf::Color::Yellow){

	color_ = col;
	char_ = ch;
	
	circ_.setRadius(radius_);
	circ_.setFillColor(color_);
	circ_.setPosition({ x,y });

	text_.setString(char_.getSSN().substr(0, 2));
	text_.setCharacterSize(fontSize_);
	text_.setColor(sf::Color::Black);

	setTextPos();
}

ppc::Vertex::Vertex(const Vertex & other){

	color_ = other.color_;
	char_ = other.char_;
	circ_ = other.circ_;
	text_ = other.text_;
	font_ = other.font_;

}

ppc::Vertex& ppc::Vertex::operator=(const Vertex& other){
	if (this != &other) {
		color_ = other.color_;
		char_ = other.char_;
		circ_ = other.circ_;
		text_ = other.text_;
		font_ = other.font_;
	}
	return *this;
}

ppc::Vertex::~Vertex() {
}

sf::CircleShape & ppc::Vertex::getCircle() {
	return circ_;
}

sf::Color ppc::Vertex::getColor() const {
	return color_;
}

void ppc::Vertex::setColor(sf::Color col) {
	color_ = col;
	circ_.setFillColor(color_);
}

sf::Vector2f ppc::Vertex::getPos() const {
	return circ_.getPosition();
}

void ppc::Vertex::setPos(sf::Vector2f pos) {
	circ_.setPosition(pos);
	setTextPos();
}

void ppc::Vertex::setPos(float x, float y) {
	circ_.setPosition({ x,y });
	setTextPos();
}

sf::Vector2f ppc::Vertex::getPosCenter() const {
	sf::Vector2f p;
	sf::FloatRect f = circ_.getGlobalBounds();
	p.x = f.left + (f.width / 2.f);
	p.y = f.top + (f.height / 2.f);
	return p;
}

ppc::PipelineCharacter ppc::Vertex::getCharacter() const {
	return char_;
}

void ppc::Vertex::setCharacter(ppc::PipelineCharacter ch) {
	char_ = ch;
	text_.setString(char_.getSSN().substr(0, 2));
}

void ppc::Vertex::setTextFont(sf::Font f) {
	font_ = f;
	text_.setFont(font_);
	text_.setString(char_.getSSN().substr(0, 2));
	text_.setCharacterSize(fontSize_);
	text_.setColor(sf::Color::Black);

	setTextPos();
}

void ppc::Vertex::setTextFontLoad(std::string fontPath) {
	font_.loadFromFile(fontPath);
	setTextFont(font_);
}

void ppc::Vertex::applyDraggable(ppc::DraggableInput &di, ppc::InputHandler &ih) {
	di.watch(ih, sf::Event::MouseButtonPressed);
	di.watch(ih, sf::Event::MouseButtonReleased);
	di.watch(ih, sf::Event::MouseMoved);
}

void ppc::Vertex::draw(sf::RenderTarget& target,
	sf::RenderStates states) const {

	states.transform *= getTransform();

	target.draw(circ_, states);
	target.draw(text_, states);
}
