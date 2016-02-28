#ifdef WINDOWS_MARKER
#define resourcePath() string("Resources/")
#else
#include "ResourcePath.hpp"
#endif

#include "Vertex.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include "debug.h"

const int ppc::Vertex::fontSize_ = 20;
const float ppc::Vertex::radius_ = 30.f;

void ppc::Vertex::setTextPos() {
	sf::Vector2f textPos = pos_;
	textPos.x += (circ_.getRadius() / 1.7f);
	textPos.y += (circ_.getRadius() / 1.8f);
	text_.setPosition(textPos);
}

ppc::Vertex::Vertex(){
	pos_ = { 0,0 };
	color_ = sf::Color::Yellow;

	circ_.setRadius(radius_);
	circ_.setFillColor(color_);
	circ_.setPosition(pos_);

	setTextPos();
	setTextFontLoad(resourcePath() + "consola.ttf");
}

ppc::Vertex::Vertex(sf::Vector2f pos, PipelineCharacter ch,
	sf::Color col = sf::Color::Yellow){

	color_ = col;
	char_ = ch;
	pos_ = pos;

	circ_.setRadius(radius_);
	circ_.setFillColor(color_);
	circ_.setPosition(pos_);

	text_.setString(char_.getSSN().substr(0, 2));
	text_.setCharacterSize(fontSize_);
	text_.setColor(sf::Color::Black);

	setTextPos();
}

ppc::Vertex::Vertex(float x, float y, PipelineCharacter ch,
	sf::Color col = sf::Color::Yellow){

	color_ = col;
	char_ = ch;
	pos_ = { x,y };
	
	circ_.setRadius(radius_);
	circ_.setFillColor(color_);
	circ_.setPosition(pos_);

	text_.setString(char_.getSSN().substr(0, 2));
	text_.setCharacterSize(fontSize_);
	text_.setColor(sf::Color::Black);

	setTextPos();
}

ppc::Vertex::Vertex(const Vertex & other){

	pos_ = other.pos_;
	color_ = other.color_;
	char_ = other.char_;
	circ_ = other.circ_;
	text_ = other.text_;
	font_ = other.font_;

}

ppc::Vertex& ppc::Vertex::operator=(const Vertex& other){
	if (this != &other) {
		pos_ = other.pos_;
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
	return pos_;
}

void ppc::Vertex::setPos(sf::Vector2f pos) {
	pos_ = pos;
	circ_.setPosition(pos_);
	setTextPos();
}

void ppc::Vertex::setPos(float x, float y) {
	pos_ = { x,y };
	circ_.setPosition(pos_);
	setTextPos();
}

sf::Vector2f ppc::Vertex::getPosBot() const {
	sf::FloatRect flrect = circ_.getGlobalBounds();
	flrect.left += (flrect.width / 2.f);
	flrect.top += flrect.height;
	return{ flrect.left, flrect.top };
}

sf::Vector2f ppc::Vertex::getPosTop() const {
	sf::FloatRect flrect = circ_.getGlobalBounds();
	flrect.left += (flrect.width / 2.f);

	return{ flrect.left, flrect.top };
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


	target.draw(circ_, states);
	target.draw(text_, states);
}
