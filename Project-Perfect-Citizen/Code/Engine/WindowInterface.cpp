#include "WindowInterface.h"

using namespace ppc;

///////////////////////////////////////////////////////////////////////
// Space Setters
///////////////////////////////////////////////////////////////////////

void WindowInterface::setSize(sf::Vector2u& size) {
    setSize(size.x, size.y);
}

///////////////////////////////////////////////////////////////////////
// Transformation Setters
///////////////////////////////////////////////////////////////////////

void WindowInterface::setPosition(const sf::Vector2f& pos) {
    setPosition(pos.x, pos.y);
};




void WindowInterface::setScale(float scale) { 
    setScale(scale, scale); 
}




void WindowInterface::setScale(const sf::Vector2f& scale) {
    setScale(scale.x, scale.y);
}
