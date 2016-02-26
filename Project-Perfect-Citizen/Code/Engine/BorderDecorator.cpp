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
            maxButtons_(3),
            draggableInput_(*this) {

    //Store Input
    borderTopLeft_.y = majorBorder;
    borderTopLeft_.x = borderBottomRight_.x = 
            borderBottomRight_.y = minorBorder;
	
    //Set up BorderShape
    borderShape_.setPosition(win.getPosition().x - minorBorder, 
                            win.getPosition().y - majorBorder);
    sf::Vector2f size(float(win.getSize().x + 2 * minorBorder),
                      float(win.getSize().y + minorBorder + 
                                              majorBorder));
    borderShape_.setSize(size);
    borderShape_.setFillColor(sf::Color::Red);

    //Set up space for buttons

    buttonInputs_ = new mousePressButton[maxButtons_];
    buttonRenders_ = new buttonRenderComponent[maxButtons_];
    buttonEntities_ = new Entity[maxButtons_];

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



void BorderDecorator::addButton(sf::Image& buttonImage) {

    //Push back the button render cmpnt
    buttonRenderVec_.push_back(buttonRenderComponent(buttonImage, 0, 3, 1, 1));
    buttonRenderVec_.back().setImageScale(0.2f, 0.2f);

    //Push back the button input cmpnt
    buttonInputVec_.push_back(new mousePressButton());

    //Calculate Button Click FloatRect
    sf::FloatRect clickSpace = buttonRenderVec_[0].getSprite()->getLocalBounds();
    clickSpace.top = 0.0f - borderTopLeft_.y - clickSpace.height;
    clickSpace.left = WindowDecorator::getSize().x - clickSpace.width - borderBottomRight_.x;

    //Set button input values
    buttonInputVec_.back()->setInputHandle(getInputHandler());
    buttonInputVec_.back()->setFloatRect(clickSpace);
    buttonInputVec_.back()->setIsBeingPressed("localCloseButton");

    //Push back the button entity
    buttonEntitiyVec_.emplace_back();
    buttonEntitiyVec_.back().addComponent(&(buttonRenderVec_.at(0)));
    buttonEntities_[buttonCount_].addComponent(buttonInputVec_.at(0));

    //Add the inputCmpnt to the Window
    addInputComponent(buttonInputVec_.back());
}




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
	target.draw(buttonRenderVec_.at(0), states);
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
    bounds.top = 0.0f - borderTopLeft_.y;
    bounds.left = 0.0f - borderTopLeft_.x;
    draggableInput_.setBounds(bounds);

    //Re-position the button
    float right = bounds.left + bounds.width;
    sf::FloatRect sprBounds = buttonRenderVec_.at(0).getSprite()->getGlobalBounds();
    sf::Vector2f ButtonPos(right - sprBounds.width - borderBottomRight_.y,
                           bounds.top + borderBottomRight_.y);
	buttonRenderVec_.at(0).renderPosition(ButtonPos);
    /*
    float right = bounds.left + bounds.width + WindowDecorator::getPosition().x;
    float top = WindowDecorator::getPosition().y + bounds.top;
    sf::FloatRect sprBounds = closeRC_->getSprite()->getGlobalBounds();
    sf::Vector2f ButtonPos(right - sprBounds.width - borderBottomRight_.y,
                           top + borderBottomRight_.y);
	closeRC_->renderPosition(ButtonPos);
    */
}
