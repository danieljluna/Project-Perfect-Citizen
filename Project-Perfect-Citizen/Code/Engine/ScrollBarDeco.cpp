#include "ScrollBarDeco.h"

using namespace ppc;

///////////////////////////////////////////////////////////////////////
// Constructors & Destructors
///////////////////////////////////////////////////////////////////////

ScrollBarDecorator::ScrollBarDecorator(WindowInterface& win) : 
        WindowDecorator(win) {
    initialize();
}




ScrollBarDecorator::ScrollBarDecorator(WindowInterface& win, 
                                       const sf::View& view) :
        WindowDecorator(win) {
    
    initialize();

    setView(view);
}




ScrollBarDecorator::~ScrollBarDecorator() {
    for (unsigned int i = 0; i < 4; ++i) {
        if (i < 2) {
            delete draggableInputs_[i];
        } 
        delete buttonInputs_[i];
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
}



void ScrollBarDecorator::move(float dx, float dy) {
    WindowDecorator::move(dx, dy);
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

    /*
    for (unsigned int i = 0; i < 4; ++i) {
        if (i < 2) {
            target.draw(scrollBackgrounds_[i]);
            target.draw(scrollBars_[i]);
        }
        target.draw(*buttonRenders_[i]);
    }
    */
}



///////////////////////////////////////////////////////////////////////
// Helpers
///////////////////////////////////////////////////////////////////////



void ScrollBarDecorator::repositionSliders() {
    sf::View currView = WindowDecorator::getView();
    sf::View normalView = WindowDecorator::getDefaultView();
    sf::Vector2f viewRatio{
        currView.getSize().x / normalView.getSize().x,
        currView.getSize().y / normalView.getSize().y };
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
    scrollBars_[0].setPosition(winRight, scrollBars_[0].getPosition().y);
    float vertBarLen = viewRatio.y * scrollBackgrounds_[0].getSize().y;
    scrollBars_[0].setSize({ barSize_, vertBarLen });

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
    scrollBars_[1].setPosition(scrollBars_[1].getPosition().x, winBottom);
    float horBarLen = viewRatio.y * scrollBackgrounds_[1].getSize().x;
    scrollBars_[1].setSize({ horBarLen, barSize_ });

    //Set up Buttons
    buttonRenders_[2]->renderPosition({ winRight, winBounds.top });
    buttonRenders_[3]->renderPosition({ winRight, winBottom - barSize_ });


  //-----------------------------------------------------------------//

    //Update Input to match visuals
    updateInput();
}



void ScrollBarDecorator::updateInput() {
    float buttonScale = barSize_ / buttonRenders_[0]->getSprite()->getTextureRect().width;
    sf::FloatRect tempBounds;

    //Update Inputs
    for (unsigned int i = 0; i < 4; ++i) {
        //Draggables
        if (i < 2) {
            //Update Draggable
            tempBounds.left = scrollBars_[i].getPosition().x;
            tempBounds.top = scrollBars_[i].getPosition().y;
            tempBounds.width = scrollBars_[i].getSize().x;
            tempBounds.height = scrollBars_[i].getSize().y;
            draggableInputs_[i]->setBounds(tempBounds);
        }

        //ButtonInputs
        buttonRenders_[i]->setButtonScale(buttonScale);
        tempBounds.left = buttonRenders_[i]->getEntity()->getPosition().x;
        tempBounds.top = buttonRenders_[i]->getEntity()->getPosition().y;
        tempBounds.height = tempBounds.width = barSize_;
        buttonInputs_[i]->setFloatRect(tempBounds);
    }
}




void ScrollBarDecorator::updateSliders() {
    sf::View currView = WindowDecorator::getView();


}




void ScrollBarDecorator::updateView() {

}




void ScrollBarDecorator::initialize() {
    repositionSliders();
    updateSliders();
}

