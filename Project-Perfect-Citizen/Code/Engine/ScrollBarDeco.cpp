#include "ScrollBarDeco.h"

using namespace ppc;

///////////////////////////////////////////////////////////////////////
// Constructors & Destructors
///////////////////////////////////////////////////////////////////////

ScrollBarDecorator::ScrollBarDecorator(WindowInterface& win,
                                       sf::Image& img) :
        WindowDecorator(win) {
    initialize(img);

    repositionSliders();
}




ScrollBarDecorator::ScrollBarDecorator(WindowInterface& win, 
                                       sf::Image& img,
                                       const sf::View& view) :
        WindowDecorator(win) {
    
    initialize(img);
    WindowDecorator::setView(view);

    repositionSliders();
}




ScrollBarDecorator::~ScrollBarDecorator() {
    for (unsigned int i = 0; i < 4; ++i) {
        delete buttonRenders_[i];
    }

}




///////////////////////////////////////////////////////////////////////
// Window Overrides
///////////////////////////////////////////////////////////////////////

sf::Vector2u ScrollBarDecorator::getSize() const {
    sf::Vector2u size = WindowDecorator::getSize();

    size.x += barSize_;
    size.y += barSize_;

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
        tempBounds.left = buttonRenders_[i]->getEntity()->getPosition().x;
        tempBounds.top = buttonRenders_[i]->getEntity()->getPosition().y;
        tempBounds.height = tempBounds.width = barSize_;
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
    }
}




void ScrollBarDecorator::updateSliders() {
    sf::FloatRect currView;
    sf::FloatRect defaultView = WindowDecorator::getBounds();
    currView.width = WindowDecorator::getView().getSize().x;
    currView.height = WindowDecorator::getView().getSize().y;
    currView.left = WindowDecorator::getView().getCenter().x - 
                        currView.width / 2.0f;
    currView.left = WindowDecorator::getView().getCenter().y -
                        currView.height / 2.0f;
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
    sf::Vector2f viewSize = { float(WindowDecorator::getSize().x),
                              float(WindowDecorator::getSize().x) };

    float viewx = scrollBars_[1].getPosition().x + 
                    scrollBars_[1].getSize().x / 2.0f;
    viewx /= scrollBackgrounds_[1].getSize().x;
    viewx *= viewSize.x;

    float viewy = scrollBars_[0].getPosition().y +
                    scrollBars_[0].getSize().y / 2.0f;
    viewy /= scrollBackgrounds_[0].getSize().y;
    viewy *= viewSize.y;

    WindowDecorator::setSize(viewx, viewy);
}




void ScrollBarDecorator::initialize(sf::Image img) {

    for (unsigned int i = 0; i < 4; ++i) {
        if (i < 2) {
            scrollBars_[i].setFillColor({ 110, 110, 110 });
            draggableInputs_[i] = new DraggableInput(scrollBars_[i]);
            //Set up Draggable Input Observers
            draggableInputs_[i]->watch(WindowDecorator::getInputHandler(),
                                       sf::Event::MouseButtonPressed);
            draggableInputs_[i]->watch(WindowDecorator::getInputHandler(),
                                       sf::Event::MouseButtonReleased);
            draggableInputs_[i]->watch(WindowDecorator::getInputHandler(),
                                       sf::Event::MouseMoved);
            WindowDecorator::addInputComponent(draggableInputs_[i]);
        } else {
            scrollBackgrounds_[i - 2].setFillColor({ 200, 200, 200 });
        }
        buttonRenders_[i] = new buttonRenderComponent(img, 2 * i, 4, 1, 1);
        float buttonScale = barSize_ / buttonRenders_[i]->getSprite()->getTextureRect().width;
        buttonRenders_[i]->setImageScale(buttonScale, buttonScale);

        buttonInputs_[i] = new mousePressButton(WindowDecorator::getInputHandler(), sf::FloatRect(), "");
        buttonInputs_[i]->setInputHandle(WindowDecorator::getInputHandler());

        buttonEntities_[i].addComponent(buttonRenders_[i]);
        buttonEntities_[i].addComponent(buttonInputs_[i]);
        WindowDecorator::addInputComponent(buttonInputs_[i]);
    }
}

