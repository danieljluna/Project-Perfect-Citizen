#include "Window.h"

#include "inputComponent.h"
#include "updateComponent.h"
#include "renderComponent.h"

#include <SFML/Graphics/RenderTexture.hpp>


using namespace ppc;


///////////////////////////////////////////////////////////////////////
// Constructors and Destructor
///////////////////////////////////////////////////////////////////////

Window::Window(unsigned int width, unsigned int height) : 
        windowSpace_() {
    windowSpace_.create(width, height);
}




Window::Window(const sf::Vector2u& size) :
        windowSpace_() {
    windowSpace_.create(size.x, size.y);
}




Window::Window(const Window& other) :
    windowSpace_() {
    sf::Vector2u windowSize = other.windowSpace_.getSize();
    windowSpace_.create(windowSize.x, windowSize.y);
}




Window::~Window() {}




///////////////////////////////////////////////////////////////////////
// Step Functionality
///////////////////////////////////////////////////////////////////////

void Window::update(sf::Time& deltaTime) {
    //Loop over all updateComponents
    for (auto c : updatecmpnts_) {
        c->update(deltaTime);
    }
}




void Window::registerInput() {
    //HACK: This is not how input should be done
    for (auto c : inputcmpnts_) {
        c->registerInput();
    }
}




void Window::draw(sf::RenderTarget& target,
                  sf::RenderStates states) const {
    //Create a sprite off of the windowSpace_
    sf::Sprite spr(windowSpace_.getTexture());
    spr.setPosition(10, 10);

    //Draw the sprite
    target.draw(spr, states);
}

