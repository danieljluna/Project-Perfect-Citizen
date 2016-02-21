#include "BorderDecorator.h"

#include <SFML/Window/Event.hpp>

using namespace ppc;

///////////////////////////////////////////////////////////////////////
// Constructors & Destructor
///////////////////////////////////////////////////////////////////////

BorderDecorator::BorderDecorator(
    WindowInterface& win,
    unsigned int majorBorder,
    unsigned int minorBorder) :
            WindowDecorator(win),
            draggableInput_(*this) {
    //Store Input

	majorBorder_ = majorBorder;
	minorBorder_ = minorBorder_;

    borderTopLeft_.y = majorBorder;
    borderTopLeft_.x = borderBottomRight_.x = 
            borderBottomRight_.y = minorBorder;


	sf::Image spriteSheet;
	spriteSheet.loadFromFile(resourcePath() + "Windows_UI.png");

	/*minRC_ = new buttonRenderComponent(spriteSheet, 4, 3, 1, 1);
	maxRC_ = new buttonRenderComponent(spriteSheet, 2, 3, 1, 1);
	closeRC_ = new buttonRenderComponent(spriteSheet, 0, 3, 1, 1);

	minRC_->setImageScale(0.2f, 0.2f);
	maxRC_->setImageScale(0.2f, 0.2f);
	closeRC_->setImageScale(0.2f, 0.2f);*/


	buttonRenderComponent* debugRC_ = new buttonRenderComponent(spriteSheet, 0, 3, 1, 1);
	debugRC_->setImageScale(0.2f, 0.2f);
	debugRC_->renderPosition(sf::Vector2f(0.0, 0.0));
	bIC_ = new mousePressButton(this->getInputHandler(), *debugRC_->getSprite(), "localCloseButton");

	closeButton_ = new Entity();
	closeButton_->addComponent(debugRC_);
	closeButton_->addComponent(bIC_);

	win.addEntity(*closeButton_);



	//closeButton_->addComponent(closeRC_);
	//this->addEntity(*closeButton_);

	
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
	/*minRC_->draw(target, states);
	maxRC_->draw(target, states);
	closeRC_->draw(target, states);*/
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
    bounds.height = borderTopLeft_.y;
    bounds.top = WindowDecorator::getBounds().top - borderTopLeft_.y;
    bounds.left = WindowDecorator::getBounds().left - borderTopLeft_.x;
    draggableInput_.setBounds(bounds);


	/*minRC_->renderPosition(sf::Vector2f(WindowDecorator::getBounds().left + WindowDecorator::getBounds().width - (3 * closeRC_->getSprite()->getGlobalBounds().width),
		WindowDecorator::getBounds().top - borderTopLeft_.y + ((majorBorder_ - closeRC_->getSprite()->getGlobalBounds().height) / 2)));

	maxRC_->renderPosition(sf::Vector2f(WindowDecorator::getBounds().left + WindowDecorator::getBounds().width - (2*closeRC_->getSprite()->getGlobalBounds().width),
		WindowDecorator::getBounds().top - borderTopLeft_.y + ((majorBorder_ - closeRC_->getSprite()->getGlobalBounds().height) / 2)));

	closeRC_->renderPosition(sf::Vector2f(WindowDecorator::getBounds().left + WindowDecorator::getBounds().width - closeRC_->getSprite()->getGlobalBounds().width,
		WindowDecorator::getBounds().top - borderTopLeft_.y + ( (majorBorder_ - closeRC_->getSprite()->getGlobalBounds().height) / 2)));*/
}
