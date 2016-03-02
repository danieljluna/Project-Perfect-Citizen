#include "../Engine/debug.h"
#include "PipelineGraphRenderComponent.h"

PipelineGraphRenderComponent::PipelineGraphRenderComponent(
	int x, int y, int backgroundWidth, int backgroundHeight) {

	/* The background */
	graphBoxBackground_.setPosition(sf::Vector2f(x, y));
	graphBoxBackground_.setSize(sf::Vector2f(backgroundWidth, backgroundHeight));
	graphBoxBackground_.setFillColor(sf::Color::Black);
}


PipelineGraphRenderComponent::~PipelineGraphRenderComponent() {

}

void PipelineGraphRenderComponent::draw(sf::RenderTarget& target,
	sf::RenderStates states) const {
	target.draw(graphBoxBackground_, states);
}

void PipelineGraphRenderComponent::recieveMessage(msgType code) {
}