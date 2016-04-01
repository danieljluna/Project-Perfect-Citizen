#include "../Engine/debug.h"
#include "PipelineGraphRenderComponent.h"

PipelineGraphRenderComponent::PipelineGraphRenderComponent(
	float x, float y, float backgroundWidth, float backgroundHeight) {

	/* The background */
	graphBoxBackground_.setPosition(sf::Vector2f(x, y));
	graphBoxBackground_.setSize(sf::Vector2f(backgroundWidth, backgroundHeight));

	//Want the color for this to be 0x80F6FF.
	graphBoxBackground_.setFillColor(sf::Color(0x80F6FF));
}


PipelineGraphRenderComponent::~PipelineGraphRenderComponent() {

}

sf::FloatRect PipelineGraphRenderComponent::getLocalBounds() {
	return graphBoxBackground_.getLocalBounds();
}

void PipelineGraphRenderComponent::draw(sf::RenderTarget& target,
	sf::RenderStates states) const {
	target.draw(graphBoxBackground_, states);
}

void PipelineGraphRenderComponent::recieveMessage(msgType code) {
}