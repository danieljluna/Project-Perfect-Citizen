#include "notifcationRenderComponent.h"
#include "../Engine/World.h"
#include "../Engine/desktop.h"
#include <string>
#include "../Engine/NotificationObserver.h"
ppc::notificationRenderComponent::notificationRenderComponent() :
	notiObserver_(*this)
{
	//Set up circle shape
	badge_.setFillColor(sf::Color::Red);
	badge_.setOutlineColor(sf::Color::White);
	badge_.setOutlineThickness(2.f);
	badge_.setRadius(5.f);

    position_ = { 0, 0 };

	//set up text
	notificationText_ = sf::Text(std::to_string(5),
		World::getFont(World::Consola),
		11);
	notificationText_.move(2.0f, -2.0f);
	notificationText_.setStyle(sf::Text::Bold);
}

void ppc::notificationRenderComponent::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform.translate(position_);
	states.transform.scale(1.3, 1.3, 0, 0);

	target.draw(badge_, states);
	target.draw(notificationText_, states);
}

ppc::NotificationObserver & ppc::notificationRenderComponent::getNotiObserver()
{
	return notiObserver_;
}

void ppc::notificationRenderComponent::updateText(unsigned int notiValue) const
{
	std::string tempString = notificationText_.getString();
	int tempInt =  std::stoi(tempString);
	tempInt -= notiValue;
	tempString = std::to_string(tempInt);
	notificationText_.setString(tempString);
}

void ppc::notificationRenderComponent::setPosition(sf::Vector2f pos)
{
    position_ = pos;
}
