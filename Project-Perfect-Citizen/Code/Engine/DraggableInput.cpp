#include "DraggableInput.h"

using namespace ppc;

///////////////////////////////////////////////////////////////////////
// Constructors & Destructor
///////////////////////////////////////////////////////////////////////

DraggableInput::DraggableInput(WindowInterface& win, 
                               sf::FloatRect& bounds) : 
                               InputComponent(3) {
    //Set Private Variables
    isDragging_ = false;
    isWindow_ = true;
    win_ = &win;
    bounds_ = bounds;
}




DraggableInput::DraggableInput(sf::Transformable& trans,
                               sf::FloatRect& bounds) :
                               InputComponent(3) {
    //Set Private Variables
    isDragging_ = false;
    isWindow_ = false;
    trans_ = &trans;
    bounds_ = bounds;
}




DraggableInput::~DraggableInput() {

}




///////////////////////////////////////////////////////////////////////
// Input Function
///////////////////////////////////////////////////////////////////////

bool DraggableInput::registerInput(sf::Event& ev) {
    //If we have a mousePress
    if (ev.type == ev.MouseButtonPressed) {

        //See if it was a left click in bounds
        if ((ev.mouseButton.button == sf::Mouse::Left) &&
            (bounds_.contains(ev.mouseButton.x, ev.mouseButton.y))) {
            //Set the flag to true
            isDragging_ = true;
        }

    //If we have a mouseRelease
    } else if (ev.type == ev.MouseButtonReleased) {

        //Unset the flag
        isDragging_ = false;

    } else if (ev.type == ev.MouseMoved) {

        //See if we're dragging
        if (isDragging_) {
            //If we're pointing to a Window:
            if (isWindow_) {
                win_->move(ev.mouseButton.x, ev.mouseButton.y);
            //Else if we're pointing to a Transformable
            } else {
                trans_->move(ev.mouseButton.x, ev.mouseButton.y);
            }
        }

    }
}
