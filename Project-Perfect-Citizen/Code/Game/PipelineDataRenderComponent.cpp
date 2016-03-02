#include "PipelineDataRenderComponent.h"

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
	dataBoxBackground_.setPosition(sf::Vector2f(x, y));
	dataBoxBackground_.setSize(sf::Vector2f(backgroundWidth, backgroundHeight));
	dataBoxBackground_.setFillColor(sf::Color::Blue);
}


PipelineDataRenderComponent::~PipelineDataRenderComponent() {

}

void PipelineDataRenderComponent::updateString(std::string output) {
	/* Set the string now to be rendered in the draw() call.*/
	text_->setString(output);
}

void PipelineDataRenderComponent::clearString() {
	str_.clear();
}


void PipelineDataRenderComponent::draw(sf::RenderTarget& target,
	sf::RenderStates states) const {
	target.draw(dataBoxBackground_, states);
	target.draw(*(this->text_), states);
}

void PipelineDataRenderComponent::recieveMessage(msgType code) {
}