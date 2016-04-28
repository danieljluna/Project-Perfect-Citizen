#include "ScrollBarDeco.h"
#include "../Game/mousePressButton.h"
#include "../Game/buttonRenderComponent.h"
#include "DraggableInput.h"

using namespace ppc;

///////////////////////////////////////////////////////////////////////
// Constructors & Destructors
///////////////////////////////////////////////////////////////////////

ScrollBarDecorator::ScrollBarDecorator(WindowInterface& win,
                                       sf::Image& img) :
        WindowDecorator(win) {
    initialize(img);

    //TODO: Find out why this needs to be called twice on init / drag before scroll
    repositionSliders();
    move(0, 0);
}




ScrollBarDecorator::ScrollBarDecorator(WindowInterface& win, 
                                       sf::Image& img,
                                       const sf::View& view) :
        WindowDecorator(win) {
    
    initialize(img);
    WindowDecorator::setView(view);

    repositionSliders();
    move(0, 0);
}




ScrollBarDecorator::~ScrollBarDecorator() {
    for (unsigned int i = 0; i < 2; ++i) {
        delete buttonRenders_[i];
        delete obsvrs_[i];
    }

    delete obsvrs_[2];

}




///////////////////////////////////////////////////////////////////////
// Window Overrides
///////////////////////////////////////////////////////////////////////

sf::Vector2u ScrollBarDecorator::getSize() const {
    sf::Vector2u size = WindowDecorator::getSize();

    size.x += int(barSize_);

    return size;
}



void ScrollBarDecorator::setSize(unsigned int x, unsigned int y) {
    WindowDecorator::setSize(x, y);
    updateSliders();
}



sf::FloatRect ScrollBarDecorator::getBounds() const {
    sf::FloatRect bounds = WindowDecorator::getBounds();

    bounds.width += barSize_;

    return bounds;
}




void ScrollBarDecorator::setPosition(float x, float y) {
    WindowDecorator::setPosition(x, y);
    repositionSliders();
}



void ScrollBarDecorator::move(float dx, float dy) {
    WindowDecorator::move(dx, dy);
    repositionSliders();
}



void ScrollBarDecorator::setView(const sf::View& view) {
    WindowDecorator::setView(view);

    updateSliders();
}



///////////////////////////////////////////////////////////////////////
// View Manipulation
///////////////////////////////////////////////////////////////////////

void ScrollBarDecorator::setBarSize(float barSize) {
    barSize_ = barSize;

    repositionSliders();
}


sf::RectangleShape ScrollBarDecorator::drawBorder(int b) const{
   
    sf::View currView = WindowDecorator::getView();
    sf::Vector2u winSize = WindowDecorator::getSize();
    sf::Vector2f viewRatio{
        currView.getSize().x / float(winSize.x),
        currView.getSize().y / float(winSize.y) };
    sf::FloatRect winBounds = WindowDecorator::getBounds();
    
    float winRight = winBounds.left + winBounds.width;
    float winBottom = winBounds.top + winBounds.height;
    float vertBarLen = viewRatio.y * scrollBackgrounds_.getSize().y;
    
    sf::RectangleShape borderShadow;
    
    switch (b) {
        case 0:
            borderShadow.setSize({ barSize_ - 2.0f, vertBarLen });
            borderShadow.setFillColor(sf::Color::Black);
            borderShadow.setPosition(winRight + 2.0f, scrollBars_.getPosition().y+1.0f);
            break;
        case 1:
            borderShadow.setFillColor(sf::Color::White);
            borderShadow.setSize({ barSize_ -1.0f, vertBarLen });
            borderShadow.setPosition(winRight, scrollBars_.getPosition().y-1.0f);
        default:
            break;
    }
    return borderShadow;
}
    

///////////////////////////////////////////////////////////////////////
// Draw Functionality
///////////////////////////////////////////////////////////////////////

void ScrollBarDecorator::draw(sf::RenderTarget& target,
                              sf::RenderStates states) const {

    WindowDecorator::draw(target, states);
    
    target.draw(scrollBackgrounds_);
   
    // black shadow
    target.draw(drawBorder(0));
    // white shadow
    target.draw(drawBorder(1));
 
    
    target.draw(scrollBars_);
    target.draw(*buttonRenders_[0]);
    target.draw(*buttonRenders_[1]);

}


///////////////////////////////////////////////////////////////////////
// Helpers
///////////////////////////////////////////////////////////////////////



void ScrollBarDecorator::repositionSliders() {
    sf::View currView = WindowDecorator::getView();
    sf::Vector2u winSize = WindowDecorator::getSize();
    sf::Vector2f viewRatio{
        currView.getSize().x / float(winSize.x),
        currView.getSize().y / float(winSize.y) };
    sf::FloatRect winBounds = WindowDecorator::getBounds();

    sf::FloatRect tempBounds;

    float winRight = winBounds.left + winBounds.width;
    float winBottom = winBounds.top + winBounds.height;

  //VERTICAL-BAR-----------------------------------------------------//

    //Set up background
    scrollBackgrounds_.setPosition(winRight, 
                                   winBounds.top + barSize_);
    sf::Vector2f vertBkgrnd(barSize_, 
                            winBounds.height - 2.0f * barSize_);
    scrollBackgrounds_.setSize(vertBkgrnd);
    
    scrollBars_.setFillColor(sf::Color(190,190,190));
    
   

    //Set up ScrollBar
    scrollBars_.setPosition(winRight + 1.0f, scrollBars_.getPosition().y);
    float vertBarLen = viewRatio.y * scrollBackgrounds_.getSize().y;
    scrollBars_.setSize({ barSize_ - 2.0f, vertBarLen });

    //Set up Buttons
    buttonRenders_[0]->renderPosition({ winRight, winBounds.top });
    buttonRenders_[1]->renderPosition({ winRight, winBottom - barSize_ });


  //-----------------------------------------------------------------//

    updateButtons();
    updateDraggable();
    updateSliders();

}



void ScrollBarDecorator::updateButtons() {
    sf::FloatRect tempBounds;

    //Update Inputs
    for (unsigned int i = 0; i < 2; ++i) {
        //ButtonInputs
        tempBounds = buttonRenders_[i]->getSprite()->getGlobalBounds();
        tempBounds.left -= WindowDecorator::getPosition().x;
        tempBounds.top -= WindowDecorator::getPosition().y;
        buttonInputs_[i]->setFloatRect(tempBounds);
    }
}



void ScrollBarDecorator::updateDraggable() {
    sf::FloatRect tempBounds;

    //Draggables
    //Update Draggable
    tempBounds.left = scrollBars_.getPosition().x -
                WindowDecorator::getPosition().x;
    tempBounds.top = scrollBars_.getPosition().y -
                WindowDecorator::getPosition().y;
    tempBounds.width = scrollBars_.getSize().x;
    tempBounds.height = scrollBars_.getSize().y;
    draggableInputs_->setBounds(tempBounds);

    tempBounds.left = scrollBackgrounds_.getPosition().x;
    tempBounds.top = scrollBackgrounds_.getPosition().y;
    tempBounds.left += 1;
    tempBounds.width = 0;
    tempBounds.height = scrollBackgrounds_.getSize().y - 
                        scrollBars_.getSize().y;

    draggableInputs_->setClampBounds(tempBounds);
}




void ScrollBarDecorator::updateSliders() {
    sf::FloatRect currView;
    sf::FloatRect defaultView;
    defaultView.width = float(WindowDecorator::getSize().x);
    defaultView.height = float(WindowDecorator::getSize().y);
    currView.width = float(WindowDecorator::getView().getSize().x);
    currView.height = float(WindowDecorator::getView().getSize().y);
    currView.left = float(WindowDecorator::getView().getCenter().x - 
                        currView.width / 2.0f);
    currView.top = float(WindowDecorator::getView().getCenter().y -
                        currView.height / 2.0f);
    sf::Vector2f pos = WindowDecorator::getPosition();
    pos.x += barSize_;
    pos.y += barSize_;

    float bary = currView.top / defaultView.height *
                    scrollBackgrounds_.getSize().y + pos.y;
    scrollBars_.setPosition(scrollBars_.getPosition().x, bary);

}




void ScrollBarDecorator::updateView() {
    sf::View v = WindowDecorator::getView();

    float centerX = 0.5f * WindowDecorator::getSize().x;

    float centerY = scrollBars_.getPosition().y -
                    scrollBackgrounds_.getPosition().y;
    centerY += scrollBars_.getSize().y / 2.0f;
    centerY *= float(WindowDecorator::getSize().y) / (v.getSize().y - 
                                                    2.0f * barSize_);

    v.setCenter(centerX, centerY);

    WindowDecorator::setView(v);
}




void ScrollBarDecorator::initialize(sf::Image img) {

    //Set up Observers
    obsvrs_[1] = new FreeFunctionObserver<ScrollBarDecorator>(
        onButtonUp, this);
    obsvrs_[2] = new FreeFunctionObserver<ScrollBarDecorator>(
        onButtonDown, this);

    //Set ScrollBar Color
    scrollBars_.setFillColor({ 110, 110, 110 });

    //Set Draggables Up For Bars
    draggableInputs_ = new DraggableInput(scrollBars_);
    draggableInputs_->watch(WindowDecorator::getInputHandler(),
        sf::Event::MouseButtonPressed);
    draggableInputs_->watch(WindowDecorator::getInputHandler(),
        sf::Event::MouseButtonReleased);
    draggableInputs_->watch(WindowDecorator::getInputHandler(),
        sf::Event::MouseMoved);

    //Add Draggables to Window
    WindowDecorator::addInputComponent(draggableInputs_);

    //Add Observer to Draggable
    obsvrs_[0] = new FreeFunctionObserver<ScrollBarDecorator>(
        onSliderDrag, this);
    draggableInputs_->onDrag().addObserver(obsvrs_[0]);

    scrollBackgrounds_.setFillColor({ 200, 200, 200 });


    for (unsigned int i = 0; i < 2; ++i) {

        //Define Button Shape / Image
        buttonRenders_[i] = new buttonRenderComponent(img, 2 * i, 4, 1, 1);
        float buttonScale = float(buttonRenders_[i]->getSprite()->
                                getTextureRect().width);
        buttonScale = barSize_ / buttonScale;
        buttonRenders_[i]->setImageScale(buttonScale, buttonScale);

        //Define Button Input
        buttonInputs_[i] = new mousePressButton(
                    WindowDecorator::getInputHandler(), 
                    sf::FloatRect());
        buttonInputs_[i]->setInputHandle(WindowDecorator::getInputHandler());

        //Create Entity and Push to Window
        buttonEntities_[i].addComponent(buttonRenders_[i]);
        buttonEntities_[i].addComponent(buttonInputs_[i]);
        WindowDecorator::addInputComponent(buttonInputs_[i]);

        //Add Observer to Buttons
        buttonInputs_[i]->onRelease().addObserver(obsvrs_[i]);

    }   //End For Loop

}







///////////////////////////////////////////////////////////////////////
// Other Functions
///////////////////////////////////////////////////////////////////////

bool ppc::onSliderDrag(ScrollBarDecorator* sb, Event ev) {
    sb->updateView();

    return true;
}

bool ppc::onButtonUp(ScrollBarDecorator* sb, Event ev) {
    sf::View v = sb->getView();
    v.move({ 0.0f, -10.0f });
    sb->setView(v);
    sb->updateSliders();

    return true;
}

bool ppc::onButtonDown(ScrollBarDecorator* sb, Event ev) {
    sf::View v = sb->getView();
    v.move({ 0.0f, 10.0f });
    sb->setView(v);
    sb->updateSliders();

    return true;
}

