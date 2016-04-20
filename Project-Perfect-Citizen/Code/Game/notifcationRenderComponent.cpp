#include "notifcationRenderComponent.h"
#include "../Engine/World.h"
#include "../Engine/desktop.h"
#include <string>
ppc::notificationRenderComponent::notificationRenderComponent()
{
	//Set up circle shape
	badge_.setFillColor(sf::Color::Red);
	badge_.setOutlineColor(sf::Color::White);
	badge_.setOutlineThickness(2.f);
	badge_.setRadius(5.f);

	//set up text
	notificationText_ = sf::Text(std::to_string(5),
		World::getFont(World::Consola),
		10);
	//notificationText_.move(2.5f, -2.0f);
	//notificationText_.setStyle(sf::Text::Bold);
}

void ppc::notificationRenderComponent::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	//states.transform.translate(sprite->getPosition());
	//states.transform.scale(1.3, 1.3, 0, 0);

	target.draw(badge_, states);
	target.draw(notificationText_, states);
}
