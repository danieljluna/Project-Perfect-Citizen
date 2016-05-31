#include "../Engine/debug.h"
#include "mousePressButton.h"

#include <iostream>
#include <string>

#include "../Engine/Entity.h"
#include "../Engine/event.h"
#include "../Engine/InputHandler.h"
#include "../Engine/World.h"

using namespace ppc;

const float DOUBLE_CLICK_TIME = 500.0f;

mousePressButton::mousePressButton() : 
	InputComponent(3), buttonRect() {

}


mousePressButton::mousePressButton(ppc::InputHandler& ih, 
	sf::FloatRect rect) : 
	InputComponent(3), buttonRect(rect) {

	//add a new subject that is tied to the event
	ih.addHandle(sf::Event::MouseButtonPressed);
	ih.addHandle(sf::Event::MouseButtonReleased);
	ih.addHandle(sf::Event::MouseMoved);
	 
	//add an observer to the subject we just added
	watch(ih, sf::Event::MouseButtonPressed);
	watch(ih, sf::Event::MouseButtonReleased);
	watch(ih, sf::Event::MouseMoved);
	

}

void mousePressButton::clearObservers()
{
	for (size_t i = 0; i < observerCount_; ++i) {
		delete observerArray_[i];
	}
}


//void mousePressButton::addFunctionObserver(bool(*fnToAdd)(sf::Event &ev), mousePressButton* mpb, unsigned int placeToInsert)

void mousePressButton::recieveMessage(Event ev) {
    switch (ev.type) {
    case ppc::Event::EventTypes::AbleType:
        setIsClickable(ev.able.enable);
        break;
    }
}

mousePressButton::~mousePressButton() {

	//ignore(inputHandle, sf::Event::MouseButtonPressed);
	//ignore(inputHandle, sf::Event::MouseButtonReleased);
}

void mousePressButton::setInputHandle(ppc::InputHandler& ih) {

	ih.addHandle(sf::Event::MouseButtonPressed);
	ih.addHandle(sf::Event::MouseButtonReleased);
	ih.addHandle(sf::Event::MouseMoved);

	watch(ih, sf::Event::MouseButtonPressed);
	watch(ih, sf::Event::MouseButtonReleased);
	watch(ih, sf::Event::MouseMoved);

}

void mousePressButton::setFloatRect(sf::FloatRect rect) {
	buttonRect = rect;
}


sf::FloatRect mousePressButton::getFloatRect() const {
    return buttonRect;
}

void ppc::mousePressButton::setIsClickable(bool c){
	isClickable = c;
}

bool ppc::mousePressButton::getIsClickable() {
	return isClickable;
}


bool mousePressButton::isCollision(sf::Vector2i mousePos) {
	bool result = false;
    //Gets the position as a Float Vector
    sf::Vector2f mouseFloatPos(float(mousePos.x), float(mousePos.y));
	//cout << "MOUSE X, Y: " << mousePos.x << ",  " << mousePos.y << endl;
	//cout << "ButtonRect LEFT, TOP: " << buttonRect.left << ",  "<< buttonRect.top << endl;

    //Returns if point is in foatRect
	result = buttonRect.contains(mouseFloatPos);
    return result;
}


bool mousePressButton::registerInput(Event ppcEv) {
    sf::Event ev(ppcEv);
    bool result = true;
    if (isClickable) {

        ppcEv.type = Event::ButtonType;

        /* Case: Mouse Pressed Event*/
        if (ev.type == sf::Event::MouseButtonPressed) {
            if (isCollision({ ev.mouseButton.x ,ev.mouseButton.y })) {
                ppcEv.buttons.mousePos = { ev.mouseButton.x, ev.mouseButton.y };
                ppcEv.buttons.state = Event::ButtonsEv::Clicked;

                if (ev.mouseButton.button == sf::Mouse::Left) {
                    ppcEv.buttons.activation = Event::ButtonsEv::LeftMouse;

                    /* Handle Double Click Register */
                    mouseTime = mouseClock.getElapsedTime().asMilliseconds();
                    if (mouseTime > DOUBLE_CLICK_TIME) {
                        mouseClock.restart();
                    } else if (mouseTime < DOUBLE_CLICK_TIME) {

						int testSound = ppc::World::getAudio().addSound("gunshots", "Double_Click.wav");
						ppc::World::getAudio().readySound(0);
						ppc::World::getAudio().popAndPlay();


                        ppcEv.buttons.state = Event::ButtonsEv::DblClicked;
                    }

                } else if (ev.mouseButton.button == sf::Mouse::Right) {
                    ppcEv.buttons.activation = Event::ButtonsEv::RightMouse;
                } else {
                    ppcEv.buttons.activation = Event::ButtonsEv::Enter;
                }
                wasPressed_ = true;

                //SEND EVENT
                if(getEntity() != nullptr) getEntity()->broadcastMessage(ppcEv);
                onPress_.sendEvent(ppcEv);
                onAll_.sendEvent(ev);
            }
        }
        /* Case: Mouse Released Event*/
        else if ((wasPressed_) && (ev.type == sf::Event::MouseButtonReleased)) {
            if (isCollision({ ev.mouseButton.x ,ev.mouseButton.y })) {

                ppcEv.buttons.mousePos = { ev.mouseButton.x, ev.mouseButton.y };
                ppcEv.buttons.state = Event::ButtonsEv::Release;

                if (ev.mouseButton.button == sf::Mouse::Left) {
                    ppcEv.buttons.activation = Event::ButtonsEv::LeftMouse;
                } else if (ev.mouseButton.button == sf::Mouse::Right) {
                    ppcEv.buttons.activation = Event::ButtonsEv::RightMouse;
                } else {
                    ppcEv.buttons.activation = Event::ButtonsEv::Enter;
                }

				if (getEntity() != nullptr) getEntity()->broadcastMessage(ppcEv);
				onRelease_.sendEvent(ppcEv);
                onAll_.sendEvent(ev);
				wasPressed_ = false;
            }
        }
		else if (ev.type == sf::Event::MouseButtonReleased && 
			ev.mouseButton.button == sf::Mouse::Left) {
			ppc::Event ppcRelease(ev);
			ppcRelease.type = Event::sfEventType;
			ppcRelease.sfEvent.type = sf::Event::MouseButtonReleased;
			ppcRelease.buttons.activation = Event::ButtonsEv::LeftMouse;
			if(getEntity() != nullptr)
				getEntity()->broadcastMessage(ppcRelease);
		}
		/* Case: Mouse Move Event */
		else if ((ev.type == sf::Event::MouseMoved)) {
			if (isCollision({ ev.mouseButton.x, ev.mouseButton.y })) {
                ppcEv.buttons.mousePos = { ev.mouseMove.x, ev.mouseMove.y };
                ppcEv.buttons.state = Event::ButtonsEv::Hover;
				if (getEntity() != nullptr) getEntity()->broadcastMessage(ppcEv);
				onHover_.sendEvent(ev);
                onAll_.sendEvent(ev);
			}
		}
    //Test to no longer be clickable
    }

    if (ppcEv.type == Event::AbleType) {
        setIsClickable(ppcEv.able.enable);
        getEntity()->broadcastMessage(ev);
    }

    return result;
}

bool ppc::ToggleMPB(mousePressButton* ptr, Event ev) {

    if (ev.type == Event::AbleType) {
        ptr->setIsClickable(ev.able.enable);
        ptr->getEntity()->broadcastMessage(ev);
	}
	
	return true;
}

