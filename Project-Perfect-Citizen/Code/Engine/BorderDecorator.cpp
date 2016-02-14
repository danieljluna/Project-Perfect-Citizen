#include "BorderDecorator.h"

#include <SFML/Window/Event.hpp>

using namespace ppc;

///////////////////////////////////////////////////////////////////////
// Constructors & Destructor
///////////////////////////////////////////////////////////////////////

BorderDecorator::BorderDecorator(
        WindowInterface& win,
        unsigned int majorBorder,
        unsigned int minorBorder) : WindowDecorator(win) {
    borderTopLeft_.y = majorBorder;
    borderTopLeft_.x = borderBottomRight_.x = 
            borderBottomRight_.y = minorBorder;

    borderShape_.setPosition(win.getPosition().x - minorBorder, 
                            win.getPosition().y - majorBorder);
    sf::Vector2f size(float(win.getSize().x + 2 * minorBorder),
                      float(win.getSize().y + minorBorder + 
                                majorBorder));
    borderShape_.setSize(size);
    borderShape_.setFillColor(sf::Color::Red);

    isBeingDragged_ = false;
}




BorderDecorator::~BorderDecorator() {}



///////////////////////////////////////////////////////////////////////
// Decorated Functionality
///////////////////////////////////////////////////////////////////////

sf::Vector2u BorderDecorator::getSize() {
    sf::Vector2u size = WindowDecorator::getSize();

    size.x += borderBottomRight_.x + borderTopLeft_.x;
    size.y += borderBottomRight_.y + borderTopLeft_.y;

    return size;
}




void BorderDecorator::setSize(unsigned int x, unsigned int y) {
    unsigned int borderWidth = borderTopLeft_.x + borderBottomRight_.x;
    if (x <= borderWidth) { x = 1; } else { x -= borderWidth; }

    unsigned int borderHeight = 
            borderTopLeft_.y + borderBottomRight_.y;
    if (y <= borderHeight) { y = 1; } else { y -= borderHeight; }
    
    WindowDecorator::setSize(x, y);
}




void BorderDecorator::setPosition(float x, float y) {
    borderShape_.setPosition(x - borderTopLeft_.x, 
                             y - borderTopLeft_.y);

    WindowDecorator::setPosition(x, y);
}




void BorderDecorator::move(float x, float y) {
    borderShape_.move(x, y);

    WindowDecorator::move(x, y);
}




void BorderDecorator::draw(sf::RenderTarget& target,
                           sf::RenderStates states) const {
    target.draw(borderShape_, states);

    WindowDecorator::draw(target, states);
}
