#include "WindowLogger.h"

using namespace std;
using namespace ppc;

WindowLogger::WindowLogger(WindowInterface& windowPtr, ostream& out):
	WindowDecorator(windowPtr), out_(out){}

WindowLogger::~WindowLogger() {}

void WindowLogger::addInputComponent(InputComponent* inputcmpnt) {
	out_ << "Window Logger: Adding ICmpnt: " << inputcmpnt << endl;
	this->getDecoTarget()->addInputComponent(inputcmpnt);
	out_ << "Window Logger: Finished Adding ICmpnt " << endl;
}

void WindowLogger::addRenderComponent(RenderComponent* rendercmpnt) {
	out_ << "Window Logger: Adding RCmpnt: " << rendercmpnt << endl;
	this->getDecoTarget()->addRenderComponent(rendercmpnt);
	out_ << "Window Logger: Finished Adding RCmpnt " << endl;
}

void WindowLogger::addUpdateComponent(UpdateComponent* updatecmpnt) {
	out_ << "Window Logger: Adding UCmpnt: " << updatecmpnt << endl;
	this->getDecoTarget()->addUpdateComponent(updatecmpnt);
	out_ << "Window Logger: Finished Adding RUCmpnt " << endl;
}

void WindowLogger::addEntity(Entity& entity) {
	out_ << "Window Logger: Adding Entity: " << &entity << endl;
	this->getDecoTarget()->addEntity(entity);
	out_ << "Window Logger: Finished Adding Entity " << endl;
}

void WindowLogger::update(sf::Time& deltaTime) {
	out_ << "Window Logger: Updating Window: " << 
		this->getDecoTarget() << endl;
	this->getDecoTarget()->update(deltaTime);
	out_ << "Window Logger: Finished Updating Window" << endl;
}

void WindowLogger::registerInput(sf::Event& ev) {
	out_ << "Window Logger: Registering Event: " << ev.type << endl;
	this->getDecoTarget()->registerInput(ev);
	out_ << "Window Logger: Finished Registering Event" << endl;
}

void WindowLogger::refresh(sf::RenderStates states) {
	out_ << "Window Logger: Refreshing Window: " <<
		this->getDecoTarget() << endl;
	this->getDecoTarget()->refresh(states);
	out_ << "Window Logger: Finished Refreshing Window" << endl;
}

void WindowLogger::draw(sf::RenderTarget& target,
	sf::RenderStates states) const  {

	out_ << "Window Logger: Drawing Window: "<< 
		this->getDecoTarget() << endl;
	target.draw(*(this->getDecoTarget()),states);
	out_ << "Window Logger: Finished Drawing Window" << endl;
}