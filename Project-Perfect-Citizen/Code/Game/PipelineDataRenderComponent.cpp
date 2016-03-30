#include "../Engine/debug.h"
#include "PipelineDataRenderComponent.h"

using namespace ppc;

PipelineDataRenderComponent::PipelineDataRenderComponent(sf::Font& f,
	int x, int y, int size, int backgroundWidth, int backgroundHeight) : font_(f) {

	/* The output text */
	this->text_ = new sf::Text();
	text_->setFont(font_);
	text_->setColor(sf::Color::White);
	text_->setPosition(float(x), float(y));
	text_->setCharacterSize(size);
	//text_->setString("");

	/* The background */
	dataBoxBackground_.setPosition(sf::Vector2f(float(x), float(y)));
	dataBoxBackground_.setSize(sf::Vector2f(float(backgroundWidth), float(backgroundHeight)));
	dataBoxBackground_.setFillColor(sf::Color::Blue);
}


PipelineDataRenderComponent::~PipelineDataRenderComponent() {

}

void PipelineDataRenderComponent::appendString(const std::string& output) {
	/* Set the string now to be rendered in the draw() call.*/
	text_->setString(text_->getString() + output);
}

void PipelineDataRenderComponent::clearString() {
	text_->setString("");
}


void PipelineDataRenderComponent::draw(sf::RenderTarget& target,
	sf::RenderStates states) const {
	target.draw(dataBoxBackground_, states);
	target.draw(*(this->text_), states);
}

void PipelineDataRenderComponent::recieveMessage(msgType code) {
}