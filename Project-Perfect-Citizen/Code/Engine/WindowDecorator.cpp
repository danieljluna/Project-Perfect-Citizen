#include "debug.h"
#include "WindowDecorator.h"

using namespace ppc;


///////////////////////////////////////////////////////////////////////
// Constructors / Destructor
///////////////////////////////////////////////////////////////////////

WindowDecorator::WindowDecorator(WindowInterface& win): 
        windowHandle_(&win) {
    univHandle_ = this;

    //Updates 
    WindowDecorator* decorates;
    decorates = dynamic_cast<WindowDecorator*>(windowHandle_);
    while (decorates != nullptr) {
        decorates->univHandle_ = this;
        //Set decorates to next decorated Window if it is a Dec
        decorates = 
            dynamic_cast<WindowDecorator*>(decorates->windowHandle_);
    }
}

WindowDecorator::~WindowDecorator() {
    if (windowHandle_ != nullptr) {
        delete windowHandle_;
    }
}

///////////////////////////////////////////////////////////////////////
// Space Getters
///////////////////////////////////////////////////////////////////////

sf::Vector2u WindowDecorator::getSize() const {
    return windowHandle_->getSize();
}

sf::FloatRect WindowDecorator::getBounds() const {
    return windowHandle_->getBounds();
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
// View Manipulation
///////////////////////////////////////////////////////////////////////

const sf::View& WindowDecorator::getView() const {
    return windowHandle_->getView();
}

void WindowDecorator::setView(const sf::View& view) {
    windowHandle_->setView(view);
}

const sf::View& WindowDecorator::getDefaultView() {
    return windowHandle_->getDefaultView();
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


///////////////////////////////////////////////////////////////////////
// Other Getters
///////////////////////////////////////////////////////////////////////

InputHandler& WindowDecorator::getInputHandler() {
    return windowHandle_->getInputHandler();
}

///////////////////////////////////////////////////////////////////////
// Game Loop Functionality
///////////////////////////////////////////////////////////////////////

void WindowDecorator::update(sf::Time& deltaTime) {
	windowHandle_->update(deltaTime);
}

void WindowDecorator::registerInput(sf::Event& ev) {
	windowHandle_->registerInput(ev);
}

void WindowDecorator::refresh(sf::RenderStates states) {
	windowHandle_->refresh(states);
}

///////////////////////////////////////////////////////////////////////
// Close State
///////////////////////////////////////////////////////////////////////

void WindowDecorator::close() {
    windowHandle_->close();
}

bool WindowDecorator::isOpen() const {
    return windowHandle_->isOpen();
}

///////////////////////////////////////////////////////////////////////
// Draw Function
///////////////////////////////////////////////////////////////////////

void WindowDecorator::draw(sf::RenderTarget& target,
	sf::RenderStates states) const  {
	target.draw(*windowHandle_, states);
}
