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
    updateBorder();

    borderShape_.setFillColor(sf::Color(170,170,170));
        
    line[0] = sf::Vertex(sf::Vector2f(10, 10));
    line[1] = sf::Vertex(sf::Vector2f(150, 150));


    

    //Set up space for buttons
    buttonInputs_ = new mousePressButton*[maxButtons_];
    buttonRenders_ = new buttonRenderComponent*[maxButtons_];
    buttonEntities_ = new Entity*[maxButtons_];

    for (size_t i = 0; i < maxButtons_; ++i) {
        buttonInputs_[i] = nullptr;
        buttonRenders_[i] = nullptr;
        buttonEntities_[i] = nullptr;
    }

    caption_.updateSize(20);
    
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



void BorderDecorator::addButton(sf::Image& buttonImage, 
                                bool(*buttonFn)(WindowInterface*, sf::Event&)) {
    if (buttonCount_ < maxButtons_) {
        //Push back the button render cmpnt
        buttonRenders_[buttonCount_] = new buttonRenderComponent(buttonImage, 0, 3, 1, 1);
        buttonRenders_[buttonCount_]->setImageScale(0.2f, 0.2f);

        //Push back the button input cmpnt
        buttonInputs_[buttonCount_] = new mousePressButton();

        updateButton(buttonCount_);

        //Set button input values
        buttonInputs_[buttonCount_]->setInputHandle(getInputHandler());
        setOnPress(buttonInputs_[buttonCount_], getUniversalTarget(), closeWindow);

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
// Draggable Manipulation
///////////////////////////////////////////////////////////////////////

void BorderDecorator::setClampBounds(const sf::FloatRect& clamp) {
    draggableInput_.setClampBounds(clamp);
}




///////////////////////////////////////////////////////////////////////
// Caption Functionality
///////////////////////////////////////////////////////////////////////

void BorderDecorator::setCaption(std::string text) {
    caption_.updateString(text);
}

void BorderDecorator::setCaptionFont(sf::Font font, unsigned int size) {
    caption_.updateFont(font);
    caption_.updateSize(size);
}

void BorderDecorator::setCaptionColor(sf::Color col) {
    caption_.updateColor(col);
}




///////////////////////////////////////////////////////////////////////
// Decorated Functionality
///////////////////////////////////////////////////////////////////////

sf::Vector2u BorderDecorator::getSize() const {
    sf::Vector2u size = WindowDecorator::getSize();

    size.x += borderBottomRight_.x + borderTopLeft_.x;
    size.y += borderBottomRight_.y + borderTopLeft_.y;

    return size;
}




void BorderDecorator::setSize(unsigned int x, unsigned int y) {
    WindowDecorator::setSize(x, y);
}




void BorderDecorator::setView(const sf::View& view) {
    WindowDecorator::setView(view);

    updateBorder();
    updateBounds();
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
        target.draw(caption_, states);
    }
}




sf::FloatRect BorderDecorator::getBounds() const {
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

    caption_.updatePosition(WindowDecorator::getPosition().x, 
                            WindowDecorator::getPosition().y - bounds.height * 0.9);

    //Re-position the buttons
    for (size_t i = 0; i < buttonCount_; ++i) {
        updateButton(i);
    }
    
}




void BorderDecorator::updateBorder() {
    sf::Vector2f pos;
    pos.x = WindowDecorator::getPosition().x - borderTopLeft_.x;
    pos.y = WindowDecorator::getPosition().y - borderTopLeft_.y;

    sf::Vector2f size;
    size.x = float(WindowDecorator::getBounds().width + 
            borderBottomRight_.x + borderTopLeft_.x);
    size.y = float(WindowDecorator::getBounds().height +
            borderBottomRight_.y + borderTopLeft_.y);


    borderShape_.setPosition(pos);

    borderShape_.setSize(size);
}



void BorderDecorator::updateButton(size_t i) {
    float left = borderShape_.getPosition().x + borderShape_.getSize().x;
    left -= float(i + 1) * (borderBottomRight_.y + buttonRenders_[i]->getSprite()->getGlobalBounds().width);
    float top = WindowDecorator::getPosition().y - borderTopLeft_.y + borderBottomRight_.y;

    sf::Vector2f ButtonPos(left, top);
    buttonRenders_[i]->renderPosition(ButtonPos);

    //Calculate Button Click FloatRect
    sf::FloatRect clickSpace = buttonRenders_[i]->getSprite()->getGlobalBounds();
    clickSpace.left -= WindowDecorator::getPosition().x;
    clickSpace.top -= WindowDecorator::getPosition().y;
    buttonInputs_[i]->setFloatRect(clickSpace);
}





bool ppc::closeWindow(WindowInterface* win, sf::Event& ev) {
    win->close();

    return true;
}


