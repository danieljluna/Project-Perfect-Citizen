#include "WindowDecorator.h"

using namespace ppc;


WindowDecorator::WindowDecorator(WindowInterface& win): 
    windowHandle_(&win) {}

WindowDecorator::~WindowDecorator() {
    if (windowHandle_ != nullptr) {
        delete windowHandle_;
    }
}

void WindowDecorator::setSize(sf::Vector2u& size) {
    windowHandle_->setSize(size);
}

void WindowDecorator::setSize(unsigned int width, unsigned int height) {
    windowHandle_->setSize(width, height);
}

void WindowDecorator::addInputComponent(InputComponent* inputcmpnt) {
	windowHandle_->addInputComponent(inputcmpnt);
}


void WindowDecorator::addRenderComponent(
	RenderComponent* rendercmpnt) {

	windowHandle_->addRenderComponent(rendercmpnt);
}

void WindowDecorator::addUpdateComponent(
	UpdateComponent* updatecmpnt) {

	windowHandle_->addUpdateComponent(updatecmpnt);
}

void WindowDecorator::addEntity(Entity& entity) {
	windowHandle_->addEntity(entity);
}

void WindowDecorator::update(sf::Time& deltaTime) {
	windowHandle_->update(deltaTime);
}

void WindowDecorator::registerInput(sf::Event& ev) {
	windowHandle_->registerInput(ev);
}

void WindowDecorator::refresh(sf::RenderStates states) {
	windowHandle_->refresh(states);
}

void WindowDecorator::draw(sf::RenderTarget& target,
	sf::RenderStates states) const  {
	target.draw(*windowHandle_, states);
}
