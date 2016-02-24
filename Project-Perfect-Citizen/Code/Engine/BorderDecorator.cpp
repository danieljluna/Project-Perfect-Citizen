#include "BorderDecorator.h"

#include <SFML/Window/Event.hpp>

using namespace ppc;

///////////////////////////////////////////////////////////////////////
// Constructors & Destructor
///////////////////////////////////////////////////////////////////////

BorderDecorator::BorderDecorator(
    WindowInterface& win,
	sf::Image& buttonSheet,
    unsigned int majorBorder,
    unsigned int minorBorder) :
            WindowDecorator(win),
			buttonSpriteSheet(buttonSheet),
            draggableInput_(*this) {
    //Store Input

    borderTopLeft_.y = majorBorder;
    borderTopLeft_.x = borderBottomRight_.x = 
            borderBottomRight_.y = minorBorder;

	closeRC_ = new buttonRenderComponent(buttonSpriteSheet, 0, 3, 1, 1);
	closeRC_->setImageScale(0.2f, 0.2f);

	bIC_ = new mousePressButton(win.getInputHandler(), closeRC_->getSprite()->getLocalBounds(), "localCloseButton");

	closeButton_.addComponent(closeRC_);
	closeButton_.addComponent(bIC_);

	addInputComponent(bIC_);

	//Set up Bounds to align new sprite placement
	updateBounds();
	
    //Set up BorderShape
    borderShape_.setPosition(win.getPosition().x - minorBorder, 
                            win.getPosition().y - majorBorder);
    sf::Vector2f size(float(win.getSize().x + 2 * minorBorder),
                      float(win.getSize().y + minorBorder + 
                                              majorBorder));

    borderShape_.setSize(size);
    borderShape_.setFillColor(sf::Color::Red);

    //Set up Bounds
    updateBounds();

    //Set up Draggable Input Observers
    draggableInput_.watch(win.getInputHandler(), 
                          sf::Event::MouseButtonPressed);
    draggableInput_.watch(win.getInputHandler(),
                          sf::Event::MouseButtonReleased);
    draggableInput_.watch(win.getInputHandler(),
                          sf::Event::MouseMoved);
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

    updateBounds();
}




void BorderDecorator::move(float x, float y) {
    borderShape_.move(x, y);

    WindowDecorator::move(x, y);

    updateBounds();
}




void BorderDecorator::draw(sf::RenderTarget& target,
                           sf::RenderStates states) const {
    target.draw(borderShape_, states);
    WindowDecorator::draw(target, states);
	closeRC_->draw(target, states);
}




sf::FloatRect BorderDecorator::getBounds() {
    sf::FloatRect result = WindowDecorator::getBounds();

    result.left -= borderTopLeft_.x;
    result.top -= borderTopLeft_.y;
    result.width += borderTopLeft_.x + borderBottomRight_.x;
    result.height += borderTopLeft_.y + borderBottomRight_.y;

    return result;
}




///////////////////////////////////////////////////////////////////////
// Helper Functions
///////////////////////////////////////////////////////////////////////

void BorderDecorator::updateBounds() {
    //Set up Draggable Input Bounds
    sf::FloatRect bounds;
    bounds.width = borderTopLeft_.x + borderBottomRight_.x + 
                WindowDecorator::getBounds().width;
    bounds.height = float(borderTopLeft_.y);
    bounds.top = WindowDecorator::getBounds().top - borderTopLeft_.y;
    bounds.left = WindowDecorator::getBounds().left - borderTopLeft_.x;
    draggableInput_.setBounds(bounds);

    //Re-position the button
    float right = bounds.left + bounds.width;
    sf::FloatRect sprBounds = closeRC_->getSprite()->getGlobalBounds();
	bIC_->setFloatRect(sprBounds);
    sf::Vector2f ButtonPos(right - sprBounds.width - borderBottomRight_.y,
                           bounds.top + borderBottomRight_.y);
	closeRC_->renderPosition(ButtonPos);
	
}
