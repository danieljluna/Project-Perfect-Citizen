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
    for (unsigned int i = 0; i < 4; ++i) {
        delete buttonRenders_[i];
        delete obsvrs_[i];
    }

    delete obsvrs_[4];
    delete obsvrs_[5];

}




///////////////////////////////////////////////////////////////////////
// Window Overrides
///////////////////////////////////////////////////////////////////////

sf::Vector2u ScrollBarDecorator::getSize() const {
    sf::Vector2u size = WindowDecorator::getSize();

    size.x += int(barSize_);
    size.y += int(barSize_);

    return size;
}



void ScrollBarDecorator::setSize(unsigned int x, unsigned int y) {
    WindowDecorator::setSize(x, y);
    updateSliders();
}



sf::FloatRect ScrollBarDecorator::getBounds() const {
    sf::FloatRect bounds = WindowDecorator::getBounds();

    bounds.width += barSize_;
    bounds.height += barSize_;

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



void ScrollBarDecorator::setBarSprite(const sf::Sprite& barSpr) {

}



void ScrollBarDecorator::setBarBkgrndSprite(const sf::Sprite& bkgrndSpr) {

}



void ScrollBarDecorator::setButtonSprite(const sf::Sprite& buttonSpr) {

}


///////////////////////////////////////////////////////////////////////
// Draw Functionality
///////////////////////////////////////////////////////////////////////

void ScrollBarDecorator::draw(sf::RenderTarget& target,
                              sf::RenderStates states) const {

    WindowDecorator::draw(target, states);
    
    for (unsigned int i = 0; i < 4; ++i) {
        if (i < 2) {
            target.draw(scrollBackgrounds_[i]);
            target.draw(scrollBars_[i]);
        }
        target.draw(*buttonRenders_[i]);
    }

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
    scrollBackgrounds_[0].setPosition(winRight, 
                                      winBounds.top + barSize_);
    sf::Vector2f vertBkgrnd(barSize_, 
                            winBounds.height - 2.0f * barSize_);
    scrollBackgrounds_[0].setSize(vertBkgrnd);

    //Set up ScrollBar
    scrollBars_[0].setPosition(winRight + 1.0f, scrollBars_[0].getPosition().y);
    float vertBarLen = viewRatio.y * scrollBackgrounds_[0].getSize().y;
    scrollBars_[0].setSize({ barSize_ - 2.0f, vertBarLen });

    //Set up Buttons
    buttonRenders_[0]->renderPosition({ winRight, winBounds.top });
    buttonRenders_[1]->renderPosition({ winRight, winBottom - barSize_ });


  //HORIZONTAL-BAR---------------------------------------------------//

    //Set up background
    scrollBackgrounds_[1].setPosition(winBounds.left + barSize_, winBottom);
    sf::Vector2f horBkgrnd(winBounds.width - 2.0f * barSize_,
                            barSize_);
    scrollBackgrounds_[1].setSize(horBkgrnd);

    //Set up ScrollBar
    scrollBars_[1].setPosition(scrollBars_[1].getPosition().x, winBottom + 1.0f);
    float horBarLen = viewRatio.x * scrollBackgrounds_[1].getSize().x;
    scrollBars_[1].setSize({ horBarLen, barSize_ - 2.0f });

    //Set up Buttons
    buttonRenders_[2]->renderPosition({ winRight - barSize_, winBottom });
    buttonRenders_[3]->renderPosition({ winBounds.left, winBottom });


  //-----------------------------------------------------------------//

    updateButtons();
    updateDraggable();
    updateSliders();

}



void ScrollBarDecorator::updateButtons() {
    sf::FloatRect tempBounds;

    //Update Inputs
    for (unsigned int i = 0; i < 4; ++i) {
        //ButtonInputs
        tempBounds = buttonRenders_[i]->getSprite()->getGlobalBounds();
        tempBounds.left += WindowDecorator::getPosition().x;
        tempBounds.top += WindowDecorator::getPosition().y;
        buttonInputs_[i]->setFloatRect(tempBounds);
    }
}



void ScrollBarDecorator::updateDraggable() {
    sf::FloatRect tempBounds;

    //Draggables
    for (unsigned int i = 0; i < 2; ++i) {
        //Update Draggable
        tempBounds.left = scrollBars_[i].getPosition().x -
                    WindowDecorator::getPosition().x;
        tempBounds.top = scrollBars_[i].getPosition().y -
                    WindowDecorator::getPosition().y;
        tempBounds.width = scrollBars_[i].getSize().x;
        tempBounds.height = scrollBars_[i].getSize().y;
        draggableInputs_[i]->setBounds(tempBounds);

        tempBounds.left = scrollBackgrounds_[i].getPosition().x;
        tempBounds.top = scrollBackgrounds_[i].getPosition().y;
        if (i == 0) {
            tempBounds.left += 1;
            tempBounds.width = 0;
            tempBounds.height = scrollBackgrounds_[i].getSize().y - 
                                    scrollBars_[i].getSize().y;
        } else if (i == 1) {
            tempBounds.top += 1;
            tempBounds.height = 0;
            tempBounds.width = scrollBackgrounds_[i].getSize().x - 
                                    scrollBars_[i].getSize().x;
        }
        draggableInputs_[i]->setClampBounds(tempBounds);
    }
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
                    scrollBackgrounds_[0].getSize().y + pos.y;
    scrollBars_[0].setPosition(scrollBars_[0].getPosition().x, bary);
    float barx = currView.left / defaultView.width * 
                    scrollBackgrounds_[1].getSize().x + pos.x;
    scrollBars_[1].setPosition(barx, scrollBars_[1].getPosition().y);

}




void ScrollBarDecorator::updateView() {
    sf::View v = WindowDecorator::getView();

    float centerX = scrollBars_[1].getPosition().x -
        scrollBackgrounds_[1].getPosition().x;
    centerX += scrollBars_[1].getSize().x / 2.0f;
    centerX *= float(WindowDecorator::getSize().x) / (v.getSize().x - 
                                                    2.0f * barSize_);

    float centerY = scrollBars_[0].getPosition().y -
        scrollBackgrounds_[0].getPosition().y;
    centerY += scrollBars_[0].getSize().y / 2.0f;
    centerY *= float(WindowDecorator::getSize().y) / (v.getSize().y - 
                                                    2.0f * barSize_);

    v.setCenter(centerX, centerY);

    WindowDecorator::setView(v);
}




void ScrollBarDecorator::initialize(sf::Image img) {

    //Set up Observers
    obsvrs_[2] = new FreeFunctionObserver<ScrollBarDecorator>(
        onButtonUp, this);
    obsvrs_[3] = new FreeFunctionObserver<ScrollBarDecorator>(
        onButtonDown, this);
    obsvrs_[4] = new FreeFunctionObserver<ScrollBarDecorator>(
        onButtonRight, this);
    obsvrs_[5] = new FreeFunctionObserver<ScrollBarDecorator>(
        onButtonLeft, this);


    for (unsigned int i = 0; i < 4; ++i) {
        if (i < 2) {
            //Set ScrollBar Color
            scrollBars_[i].setFillColor({ 110, 110, 110 });

            //Set Draggables Up For Bars
            draggableInputs_[i] = new DraggableInput(scrollBars_[i]);
            draggableInputs_[i]->watch(WindowDecorator::getInputHandler(),
                                       sf::Event::MouseButtonPressed);
            draggableInputs_[i]->watch(WindowDecorator::getInputHandler(),
                                       sf::Event::MouseButtonReleased);
            draggableInputs_[i]->watch(WindowDecorator::getInputHandler(),
                                       sf::Event::MouseMoved);

            //Add Draggables to Window
            WindowDecorator::addInputComponent(draggableInputs_[i]);

            //Add Observer to Draggable
            obsvrs_[i] = new FreeFunctionObserver<ScrollBarDecorator>(
                                onSliderDrag, this);
            draggableInputs_[i]->onDrag().addObserver(obsvrs_[i]);

        } else {
            //Define Background Bar Color
            scrollBackgrounds_[i - 2].setFillColor({ 200, 200, 200 });
        }

        //Define Button Shape / Image
        buttonRenders_[i] = new buttonRenderComponent(img, 2 * i, 4, 1, 1);
        float buttonScale = float(buttonRenders_[i]->getSprite()->
                                getTextureRect().width);
        buttonScale = barSize_ / buttonScale;
        buttonRenders_[i]->setImageScale(buttonScale, buttonScale);

        //Define Button Input
        buttonInputs_[i] = new mousePressButton(
                    WindowDecorator::getInputHandler(), 
                    sf::FloatRect(), 
                    "");
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

bool ppc::onButtonLeft(ScrollBarDecorator* sb, Event ev) {
    sf::View v = sb->getView();
    v.move({ -10.0f, 0.0f });
    sb->setView(v);
    sb->updateSliders();

    return true;
}

bool ppc::onButtonRight(ScrollBarDecorator* sb, Event ev) {
    sf::View v = sb->getView();
    v.move({ 10.0f, 0.0f });
    sb->setView(v);
    sb->updateSliders();

    return true;
}

