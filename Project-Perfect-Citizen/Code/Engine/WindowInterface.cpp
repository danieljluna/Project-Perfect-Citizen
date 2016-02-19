#include "WindowInterface.h"
#include "debug.h"
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




void WindowInterface::move(const sf::Vector2f& pos) {
    move(pos.x, pos.y);
}




void WindowInterface::setScale(float scale) { 
    setScale(scale, scale); 
}




void WindowInterface::setScale(const sf::Vector2f& scale) {
    setScale(scale.x, scale.y);
}



void WindowInterface::scale(float scaleFactor) {
    scale(scaleFactor, scaleFactor);
}




void WindowInterface::scale(const sf::Vector2f& scaleVec) {
    scale(scaleVec.x, scaleVec.y);
}
