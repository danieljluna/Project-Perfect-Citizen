#include "Window.h"


using namespace ppc;


///////////////////////////////////////////////////////////////////////
// Constructors and Destructor
///////////////////////////////////////////////////////////////////////

Window::Window(unsigned int width, unsigned int height) : 
        windowSpace_() {
    windowSpace_.create(width, height);
}




Window::Window(const Window& other) :
        windowSpace_() {
    sf::Vector2u windowSize = other.windowSpace_.getSize();
    windowSpace_.create(windowSize.x, windowSize.y);
}




Window::~Window() {}

