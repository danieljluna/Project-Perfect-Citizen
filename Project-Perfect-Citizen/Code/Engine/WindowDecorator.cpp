#include "WindowDecorator.h"

using namespace ppc;


///////////////////////////////////////////////////////////////////////
// Constructors / Destructor
///////////////////////////////////////////////////////////////////////

WindowDecorator::WindowDecorator(WindowInterface& win): 
    windowHandle_(&win) {}

WindowDecorator::~WindowDecorator() {
    if (windowHandle_ != nullptr) {
        delete windowHandle_;
    }
}

///////////////////////////////////////////////////////////////////////
// Space Setters
///////////////////////////////////////////////////////////////////////


void WindowDecorator::setSize(unsigned int width, unsigned int height){
    windowHandle_->setSize(width, height);
}


///////////////////////////////////////////////////////////////////////
// Transformation Setters
///////////////////////////////////////////////////////////////////////

void WindowDecorator::setPosition(float x, float y) {
    windowHandle_->setPosition(x, y);
}

void WindowDecorator::move(float dx, float dy) {
    windowHandle_->move(dx, dy);
}

void WindowDecorator::setScale(float xscale, float yscale) {
    windowHandle_->setScale(xscale, yscale);
}

void WindowDecorator::scale(float xscale, float yscale) {
    windowHandle_->scale(xscale, yscale);
}


///////////////////////////////////////////////////////////////////////
// Transformation Getters
///////////////////////////////////////////////////////////////////////

sf::Vector2f WindowDecorator::getPosition() const {
    return windowHandle_->getPosition();
}

sf::Vector2f WindowDecorator::getScale() const {
    return windowHandle_->getScale();
}


///////////////////////////////////////////////////////////////////////
// Component Manipulation
///////////////////////////////////////////////////////////////////////

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
