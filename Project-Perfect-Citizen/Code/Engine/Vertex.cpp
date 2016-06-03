#include "../ResourceDef.h"

#include "Vertex.h"
#include "debug.h"

#include <iostream>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include "InputHandler.h"
#include "DraggableInput.h"

#include "../Game/characterRender.hpp"



const int ppc::Vertex::fontSize_ = 20;
const float ppc::Vertex::radius_ = 30.f;

ppc::Vertex::Vertex(){

	color_ = sf::Color::Yellow;
    
    sf::Image face_sheet;
    face_sheet.loadFromFile(resourcePath() + "Face_Sheet.png");
	rend_.setImage(face_sheet);
    
    bgrect_.setSize(sf::Vector2f(100,125));
    bgrect_.setFillColor(sf::Color(181,179,165));
    bgrect_.setOutlineThickness(1.f);
    bgrect_.setOutlineColor(sf::Color::Black);
    
    rect_.setSize(sf::Vector2f(100,100));
    rect_.setFillColor(sf::Color(180,180,180));
    rect_.setOutlineColor(sf::Color::Black);
    rend_.setOrigin(rect_.getOrigin().x, rect_.getOrigin().y);


	circ_.setRadius(radius_);
	circ_.setFillColor(color_);
	circ_.setPosition(0, 0);
	circ_.setOutlineColor(sf::Color::White);
	//text_.setPosition(radius_ / 2.f, radius_ / 2.f);
    text_.setPosition(40, rect_.getSize().y+1);
	setTextFontLoad(resourcePath() + "consola.ttf");
	isSelected_ = false;
}

ppc::Vertex::Vertex(const Vertex & other){
	color_ = other.color_;
	char_ = other.char_;
	circ_ = other.circ_;
    rect_ = other.rect_;
    bgrect_ = other.bgrect_;
    rend_ = other.rend_;
	text_ = other.text_;
	font_ = other.font_;
	isSelected_ = other.isSelected_;

}

ppc::Vertex& ppc::Vertex::operator=(const Vertex& other){
	if (this != &other) {
		color_ = other.color_;
		char_ = other.char_;
		circ_ = other.circ_;
        rect_ = other.rect_;
        bgrect_ = other.bgrect_;
        rend_ = other.rend_;
		text_ = other.text_;
		font_ = other.font_;
		isSelected_ = other.isSelected_;
		bounds_ = other.bounds_;
	}
	return *this;
}

ppc::Vertex::~Vertex() {
	//delete rend_;
}

sf::Color ppc::Vertex::getColor() const {
	return color_;
}

void ppc::Vertex::setColor(sf::Color col) {
	color_ = col;
	circ_.setFillColor(color_);
    rect_.setFillColor(color_);
    bgrect_.setFillColor(sf::Color(181, 179, 165));
}

sf::Vector2f ppc::Vertex::getPosCenter() const {
	sf::Vector2f p = getPosition();
	//sf::FloatRect f = circ_.getGlobalBounds();
    sf::FloatRect f = bgrect_.getGlobalBounds();
	p.x += (f.width / 2.f);
	p.y += (f.height / 2.f);
	return p;
}

sf::FloatRect ppc::Vertex::getLocalBounds() const {
//	sf::FloatRect fRect = circ_.getLocalBounds();
    sf::FloatRect fRect = bgrect_.getLocalBounds();
    fRect.width = fRect.width*scale;
    fRect.height = fRect.height*scale;
	fRect.left = getPosition().x;
	fRect.top = getPosition().y;
	return fRect;
}

sf::FloatRect ppc::Vertex::getGlobalBounds() const {
//	sf::FloatRect fRect = circ_.getGlobalBounds();
	sf::FloatRect fRect = bgrect_.getGlobalBounds();
    fRect.left = getPosition().x;
	fRect.top = getPosition().y;
	return fRect;
}

ppc::PipelineCharacter ppc::Vertex::getCharacter() const {
	return char_;
}

void ppc::Vertex::setCharacter(ppc::PipelineCharacter ch) {
	char_ = ch;
    rend_.applyCharacterValues(char_);
    rend_.setShouldDraw(true);

	text_.setString(char_.getSSN().substr(0, 2));
}

void ppc::Vertex::setTextFont(sf::Font f) {
	font_ = f;
	text_.setFont(font_);
	text_.setString(char_.getSSN().substr(0, 2));
	text_.setCharacterSize(fontSize_);
	text_.setColor(sf::Color::Black);
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

void ppc::Vertex::selectVert() {
	isSelected_ = true;
	circ_.setOutlineThickness(3.f);
    rect_.setOutlineThickness(3.f);
    bgrect_.setOutlineThickness(3.f);
    rend_.setOrigin(rect_.getOrigin().x, rect_.getOrigin().y);

}

void ppc::Vertex::deselectVert() {
	isSelected_ = false;
	circ_.setOutlineThickness(0.f);
	rect_.setOutlineThickness(0.f);
    bgrect_.setOutlineThickness(1.f);
}

bool ppc::Vertex::isSelected() {
	return isSelected_;
}

void ppc::Vertex::draw(sf::RenderTarget& target,
	sf::RenderStates states) const {

    //The line below draws Vertices at double size (Uncomment it to see)
    states.transform.scale(sf::Vector2f{scale, scale});

	states.transform *= getTransform();

    target.draw(bgrect_, states);
	target.draw(rect_, states);
	target.draw(text_, states);
    target.draw(rend_, states);

}
