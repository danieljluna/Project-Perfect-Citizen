#include "debug.h"
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
	
    //Set up BorderShape & Visual Details
    sf::Vector2f pos(win.getPosition().x - minorBorder,
                     win.getPosition().y - majorBorder);
 
    sf::Vector2f size(float(win.getSize().x + 2 * minorBorder),
                      float(win.getSize().y + minorBorder +
                                              majorBorder));

                
    borderShape_.setPosition(pos);
   
    borderShape_.setSize(size);
    borderShape_.setFillColor(sf::Color(170,170,170));

    //Set up space for buttons

    buttonInputs_ = new mousePressButton*[maxButtons_];
    buttonRenders_ = new buttonRenderComponent*[maxButtons_];
    buttonEntities_ = new Entity*[maxButtons_];

    for (size_t i = 0; i < maxButtons_; ++i) {
        buttonInputs_[i] = nullptr;
        buttonRenders_[i] = nullptr;
        buttonEntities_[i] = nullptr;
    }

    buttonCount_ = 0;

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




BorderDecorator::~BorderDecorator() {
    for (size_t i = 0; i < buttonCount_; ++i) {
        delete buttonEntities_[i];
        delete buttonRenders_[i];
    }

    delete[] buttonEntities_;
    delete[] buttonInputs_;
    delete[] buttonRenders_;
}



void BorderDecorator::addButton(sf::Image& buttonImage, std::string buttonFn) {
    if (buttonCount_ < maxButtons_) {
        //Push back the button render cmpnt
        buttonRenders_[buttonCount_] = new buttonRenderComponent(buttonImage, 0, 3, 1, 1);
        buttonRenders_[buttonCount_]->setImageScale(0.2f, 0.2f);
        updateButton(buttonCount_);

        //Push back the button input cmpnt
        buttonInputs_[buttonCount_] = new mousePressButton();

        //Calculate Button Click FloatRect
        sf::FloatRect clickSpace = buttonRenders_[buttonCount_]->getSprite()->getGlobalBounds();
        clickSpace.left = WindowDecorator::getSize().x;
        clickSpace.left -= float(buttonCount_ + 1) * (borderBottomRight_.x + clickSpace.width);
        clickSpace.top = float(borderBottomRight_.y) - float(borderTopLeft_.y);

        //Set button input values
        buttonInputs_[buttonCount_]->setInputHandle(getInputHandler());
        buttonInputs_[buttonCount_]->setFloatRect(clickSpace);
        buttonInputs_[buttonCount_]->setIsBeingPressed(buttonFn);

        //Push back the button entity
        buttonEntities_[buttonCount_] = new Entity();
        buttonEntities_[buttonCount_]->addComponent(buttonInputs_[buttonCount_]);
        buttonEntities_[buttonCount_]->addComponent(buttonRenders_[buttonCount_]);

        //Add the inputCmpnt to the Window
        addInputComponent(buttonInputs_[buttonCount_]);

        ++buttonCount_;

    }
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
    for (size_t i = 0; i < buttonCount_; ++i) {
        target.draw(*buttonRenders_[i], states);
    }
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

    //Re-position the buttons
    for (size_t i = 0; i < buttonCount_; ++i) {
        updateButton(i);
    }
    
}



void BorderDecorator::updateButton(size_t i) {
    float left = borderShape_.getPosition().x + borderShape_.getSize().x;
    left = left - float(i + 1) * (borderBottomRight_.y + buttonRenders_[i]->getSprite()->getGlobalBounds().width);
    float top = WindowDecorator::getPosition().y - borderTopLeft_.y + borderBottomRight_.y;

    sf::Vector2f ButtonPos(left, top);
    buttonRenders_[i]->renderPosition(ButtonPos);
}