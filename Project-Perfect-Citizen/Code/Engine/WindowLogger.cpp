#include "debug.h"
#include "WindowLogger.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

using namespace ppc;

WindowLogger::WindowLogger(WindowInterface& windowPtr, std::ostream& out):
	WindowDecorator(windowPtr), out_(out){}

WindowLogger::~WindowLogger() {}

void WindowLogger::setSize(sf::Vector2u& size) {
	out_ << "Window Logger: Setting Size of Window: " <<
		this->getDecoTarget() << ": New size: " << 
		size.x << ", " << size.y << std::endl;
	this->getDecoTarget()->setSize(size);
}

void WindowLogger::setSize(unsigned int width, unsigned int height) {
	out_ << "Window Logger: Setting Size of Window: " <<
		this->getDecoTarget() << ": New size: " <<
		width << ", " << height << std::endl;
	this->getDecoTarget()->setSize(width, height);
}

void WindowLogger::addInputComponent(InputComponent* inputcmpnt) {
	out_ << "Window Logger: Adding ICmpnt: " << inputcmpnt << std::endl;
	this->getDecoTarget()->addInputComponent(inputcmpnt);
	out_ << "Window Logger: Finished Adding ICmpnt " << std::endl;
}

void WindowLogger::addRenderComponent(RenderComponent* rendercmpnt) {
	out_ << "Window Logger: Adding RCmpnt: " << rendercmpnt << std::endl;
	this->getDecoTarget()->addRenderComponent(rendercmpnt);
	out_ << "Window Logger: Finished Adding RCmpnt " << std::endl;
}

void WindowLogger::addUpdateComponent(UpdateComponent* updatecmpnt) {
	out_ << "Window Logger: Adding UCmpnt: " << updatecmpnt << std::endl;
	this->getDecoTarget()->addUpdateComponent(updatecmpnt);
	out_ << "Window Logger: Finished Adding RUCmpnt " << std::endl;
}

void WindowLogger::addEntity(Entity& entity) {
	out_ << "Window Logger: Adding Entity: " << &entity << std::endl;
	this->getDecoTarget()->addEntity(entity);
	out_ << "Window Logger: Finished Adding Entity " << std::endl;
}

void WindowLogger::update(sf::Time& deltaTime) {
	out_ << "Window Logger: Updating Window: " << 
		this->getDecoTarget() << std::endl;
	this->getDecoTarget()->update(deltaTime);
	out_ << "Window Logger: Finished Updating Window" << std::endl;
}

void WindowLogger::registerInput(sf::Event ev) {
	out_ << "Window Logger: Registering Event: " << ev.type << std::endl;
	this->getDecoTarget()->registerInput(ev);
	out_ << "Window Logger: Finished Registering Event" << std::endl;
}

void WindowLogger::refresh(sf::RenderStates states) {
	out_ << "Window Logger: Refreshing Window: " <<
		this->getDecoTarget() << std::endl;
	this->getDecoTarget()->refresh(states);
	out_ << "Window Logger: Finished Refreshing Window" << std::endl;
}

void WindowLogger::draw(sf::RenderTarget& target,
	sf::RenderStates states) const  {

	out_ << "Window Logger: Drawing Window: "<< 
		this->getDecoTarget() << std::endl;
	target.draw(*(this->getDecoTarget()),states);
	out_ << "Window Logger: Finished Drawing Window" << std::endl;
}