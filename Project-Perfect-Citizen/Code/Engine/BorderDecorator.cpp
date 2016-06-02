#include "debug.h"
#include "BorderDecorator.h"

#include <SFML/Window/Event.hpp>
//#include "Audio/AudioQueue.h"
#include "World.h"

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
       //Set up space for buttons
    buttonInputs_ = new mousePressButton*[maxButtons_];
    buttonRenders_ = new buttonRenderComponent*[maxButtons_];
    buttonEntities_ = new Entity*[maxButtons_];

    for (size_t i = 0; i < maxButtons_; ++i) {
        buttonInputs_[i] = nullptr;
        buttonRenders_[i] = nullptr;
        buttonEntities_[i] = nullptr;
    }

    //Caption Defaults
    caption_.updateSize(18);
    caption_.updateColor({ 255, 255, 255 });
    captionBackground_.setFillColor({51, 50, 161});
    
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
                                bool(*buttonFn)(WindowInterface*, Event)) {
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
    isClamped_ = true;
}




///////////////////////////////////////////////////////////////////////
// Caption Functionality
///////////////////////////////////////////////////////////////////////

void BorderDecorator::setCaption(std::string text) {
    caption_.setRenderable(true);
    caption_.updateString(text);
}

void BorderDecorator::setCaptionFont(sf::Font font) {
    caption_.updateFont(font);
}

void BorderDecorator::setCaptionSize(unsigned int size) {
	caption_.updateSize(size);
}

void BorderDecorator::setCaptionColor(sf::Color col) {
    caption_.updateColor(col);
}

void BorderDecorator::setCaptionBackground(sf::Color col) {
    captionBackground_.setFillColor(col);
}

void BorderDecorator::setCaptionIcon(sf::Sprite spr) {
    captionIcon_ = spr;
    captionHasIcon_ = true;

    sf::FloatRect iconBounds = captionIcon_.getLocalBounds();
    captionIcon_.scale(captionBackground_.getSize().x / iconBounds.width,
                       captionBackground_.getSize().y / iconBounds.height);
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
    //Used to give the Border an outline
    sf::RectangleShape borderShadow;
    sf::RectangleShape borderWhite;
    
    sf::FloatRect bounds = getBounds();
  
    
    
    borderShadow.setFillColor(sf::Color::Black);
    borderShadow.setSize(sf::Vector2f(bounds.width, bounds.height));
    borderShadow.setPosition(sf::Vector2f(bounds.left+2,bounds.top+2));
    
    borderWhite.setFillColor(sf::Color::White);
    borderWhite.setSize(sf::Vector2f(bounds.width+1, bounds.height+1));
    borderWhite.setPosition(sf::Vector2f(bounds.left-1,bounds.top-1));
    

    sf::FloatRect inner = WindowDecorator::getBounds();
    sf::RectangleShape innerShadow;
    sf::RectangleShape innerWhite;

    innerShadow.setFillColor(sf::Color(200,200,200));
    innerShadow.setSize(sf::Vector2f(inner.width+1, inner.height+1));
    innerShadow.setPosition(inner.left, inner.top);
    
    innerWhite.setFillColor(sf::Color(90,90,90));
    innerWhite.setSize(sf::Vector2f(inner.width+1, inner.height+1));
    innerWhite.setPosition(inner.left-1, inner.top-1);
    
    target.draw(borderWhite, states);
    target.draw(borderShadow, states);
    target.draw(borderShape_, states);
    target.draw(captionBackground_, states);
    if (captionHasIcon_) {
        target.draw(captionIcon_);
        auto tempStates = states;
        tempStates.transform.translate({ captionIcon_.getLocalBounds().width, 0 });
        target.draw(caption_, tempStates);
    } else {
        target.draw(caption_, states);
    }
    target.draw(innerShadow, states);
    target.draw(innerWhite, states);
    WindowDecorator::draw(target, states);
    for (size_t i = 0; i < buttonCount_; ++i) {
        target.draw(*buttonRenders_[i], states);
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

    caption_.updatePosition(WindowDecorator::getPosition().x + bounds.height * 0.1f,
                            WindowDecorator::getPosition().y - bounds.height * 0.88f);

    bounds = getBounds();
    sf::Vector2f topLeft = sf::Vector2f(bounds.left + 2.0f, bounds.top + 2.0f);

    captionBackground_.setPosition(topLeft);
    captionIcon_.setPosition(topLeft);

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

    captionBackground_.setSize(sf::Vector2f(size.x - 4.0f, borderTopLeft_.y - 4.0f));
}



void BorderDecorator::updateButton(size_t i) {
    float left = borderShape_.getPosition().x + borderShape_.getSize().x;
    left -= float(i + 1) * (borderBottomRight_.y + buttonRenders_[i]->getSprite()->getGlobalBounds().width);
    float top = WindowDecorator::getPosition().y - borderTopLeft_.y + borderBottomRight_.y - 1;

    sf::Vector2f ButtonPos(left, top);
    buttonRenders_[i]->renderPosition(ButtonPos);

    //Calculate Button Click FloatRect
    sf::FloatRect clickSpace = buttonRenders_[i]->getSprite()->getGlobalBounds();
    clickSpace.left -= WindowDecorator::getPosition().x;
    clickSpace.top -= WindowDecorator::getPosition().y;
    buttonInputs_[i]->setFloatRect(clickSpace);
}





bool ppc::closeWindow(WindowInterface* win, Event ev) {

	int testSound = World::getAudio().addSound("Close_Window", "Close_Window.wav");
	World::getAudio().readySound(testSound);
	World::getAudio().popAndPlay();
    win->close();
    return true;
}


