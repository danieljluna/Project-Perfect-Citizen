#include "BorderDecorator.h"

using namespace ppc;

///////////////////////////////////////////////////////////////////////
// Constructors & Destructor
///////////////////////////////////////////////////////////////////////

BorderDecorator::BorderDecorator(
        WindowInterface& win,
        unsigned int majorBorder,
        unsigned int minorBorder) : WindowDecorator(win) {
    borderTopLeft.y = majorBorder;
    borderTopLeft.x = borderBottomRight.x = 
            borderBottomRight.y = minorBorder;

    borderShape.setPosition(win.getPosition().x - minorBorder, 
                            win.getPosition().y - majorBorder);
    sf::Vector2f size(float(win.getSize().x + 2 * minorBorder),
                      float(win.getSize().y + minorBorder + 
                                majorBorder));
    borderShape.setSize(size);
}




BorderDecorator::~BorderDecorator() {}



///////////////////////////////////////////////////////////////////////
// Decorated Functionality
///////////////////////////////////////////////////////////////////////

sf::Vector2u BorderDecorator::getSize() {
    sf::Vector2u size = WindowDecorator::getSize();

    size.x += borderBottomRight.x + borderTopLeft.x;
    size.y += borderBottomRight.y + borderTopLeft.y;

    return size;
}




void BorderDecorator::setSize(unsigned int x, unsigned int y) {
    unsigned int borderWidth = borderTopLeft.x + borderBottomRight.x;
    if (x <= borderWidth) { x = 1; } else { x -= borderWidth; }

    unsigned int borderHeight = borderTopLeft.y + borderBottomRight.y;
    if (y <= borderHeight) { y = 1; } else { y -= borderHeight; }
    
    WindowDecorator::setSize(x, y);
}




void BorderDecorator::setPosition(float x, float y) {
    

    WindowDecorator::setPosition(x, y);
}




void BorderDecorator::move(float x, float y) {
    borderShape.move(x, y);

    WindowDecorator::move(x, y);
}




void BorderDecorator::registerInput(sf::Event& ev) {

}




void BorderDecorator::draw(sf::RenderTarget& target,
                           sf::RenderStates states) const {
    WindowDecorator::draw(target, states);
}
