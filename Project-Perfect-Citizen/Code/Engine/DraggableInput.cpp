#include "../Engine/debug.h"
#include "DraggableInput.h"
#include "WindowInterface.h"
#include <iostream>
#include <SFML/Graphics/Transformable.hpp>

using namespace ppc;

///////////////////////////////////////////////////////////////////////
// Constructors & Destructor
///////////////////////////////////////////////////////////////////////

DraggableInput::DraggableInput(WindowInterface& win) : 
                               InputComponent(3) {
    //Set Private Variables
    isDragging_ = false;
    isWindow_ = true;
    isClamped_ = false;
    win_ = &win;
    startX_ = 0;
    startY_ = 0;
}




DraggableInput::DraggableInput(sf::Transformable& trans) :
                               InputComponent(3) {
    //Set Private Variables
    isDragging_ = false;
    isWindow_ = false;
    isClamped_ = false;
    trans_ = &trans;
}




DraggableInput::~DraggableInput() {

}




///////////////////////////////////////////////////////////////////////
// Setters
///////////////////////////////////////////////////////////////////////

void DraggableInput::setBounds(const sf::FloatRect& bounds) {
    bounds_ = bounds;
}




void DraggableInput::setClampBounds(const sf::FloatRect& clamp) {
    clamp_ = clamp;
    isClamped_ = true;
}




///////////////////////////////////////////////////////////////////////
// Input Function
///////////////////////////////////////////////////////////////////////

bool DraggableInput::registerInput(Event ppcEv) {
    sf::Event ev(ppcEv);
    //If we have a mousePress
    if (ev.type == ev.MouseButtonPressed) {

        sf::Vector2f mousePos(float(ev.mouseButton.x), 
                              float(ev.mouseButton.y));
		
        //See if it was a left click in bounds
        if ((ev.mouseButton.button == sf::Mouse::Left) &&
            (bounds_.contains(mousePos))) {
            //Set the flag to true

			startX_ = ev.mouseButton.x;
			startY_ = ev.mouseButton.y;
            isDragging_ = true;
        }

    //If we have a mouseRelease
    } else if (ev.type == ev.MouseButtonReleased) {
        if (ev.mouseButton.button == sf::Mouse::Left){
            isDragging_ = false;
        }


    } else if (ev.type == ev.MouseMoved) {
		int endX_ = ev.mouseMove.x;
		int endY_ = ev.mouseMove.y;

        //See if we're dragging
        if (isDragging_) {
		
            sf::Vector2f shift(float(endX_ - startX_),
                               float(endY_ - startY_));
            
            drag(shift);
            clamp();
            
            onDrag_.sendEvent(ev);

			return true;
        }
    }

    return true;
}





///////////////////////////////////////////////////////////////////////
// Subject Functionality
///////////////////////////////////////////////////////////////////////

Subject& DraggableInput::onDrag() {
    return onDrag_;
}





///////////////////////////////////////////////////////////////////////
// Private Helpers
///////////////////////////////////////////////////////////////////////

void DraggableInput::clamp() {
    if (isClamped_) {
        sf::Vector2f pos;
        if (isWindow_) {
            pos = win_->getPosition();
        } else {
            pos = trans_->getPosition();
        }

        if (pos.x < clamp_.left) {
            drag({ clamp_.left - pos.x, 0.0f });
        } else if (pos.x > clamp_.left + clamp_.width) {
            drag({ clamp_.left + clamp_.width - pos.x, 0.0f});
        }

        if (pos.y < clamp_.top) {
            drag({ 0.0f, clamp_.top - pos.y });
        } else if (pos.y > clamp_.top + clamp_.height) {
            drag({ 0.0f, clamp_.top + clamp_.height - pos.y });
        }
    }
}




void DraggableInput::removeClamp() {
    isClamped_ = false;
}




void DraggableInput::drag(const sf::Vector2f& delta) {
    //If we're pointing to a Window:
    if (isWindow_) {
        win_->move(delta);
    //Else if we're pointing to a Transformable
    } else {
        trans_->move(delta);
        bounds_.left += delta.x;
        bounds_.top += delta.y;
        startX_ += int(delta.x);
        startY_ += int(delta.y);
    }
}
