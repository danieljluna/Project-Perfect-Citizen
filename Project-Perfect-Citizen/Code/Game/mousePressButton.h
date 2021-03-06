#pragma once

#include <SFML/Graphics.hpp>
#include <array>

#include "../Engine/inputComponent.h"
#include "../Engine/InputHandler.h"
#include "../Engine/Entity.h"
#include "../Engine/subject.h"
#include "../Engine/FunctionObserver.h"
#include "../Engine/FreeFunctionObserver.h"
#include "../Engine/debug.h"

///////////////////////////////////////////////////////////////////////
/// @brief Designated Input Component for a generic window 'X' button
/// @author Alex Vincent & Nader Sleem
/// @details The mousePressedButton is a basic packaged subclass
///     extension of InputComponent, make specifically to handle
///     all generic "X" button related sfml event parts. 
///		Stick this onto an entity to give it this functionality.
///////////////////////////////////////////////////////////////////////


namespace ppc {


class mousePressButton: public ppc::InputComponent {
private:

	sf::FloatRect buttonRect;
	std::string isBeingPressed;
	sf::Clock mouseClock;
    sf::Int32 mouseTime;
	bool isCollision(sf::Vector2i);
    
    bool wasPressed_ = false;
    Subject onPress_;
    Subject onDoublePress_;
    Subject onRelease_;
	Subject onHover_;

public:

	mousePressButton();

///////////////////////////////////////////////////////////////////////
///@brief This Ctor will be depricated soon. Please use the default 
///Ctor and setter functions instead.
///////////////////////////////////////////////////////////////////////
	mousePressButton(ppc::InputHandler& ih, sf::FloatRect rect, std::string isBeingPressed);

	///////////////////////////////////////////////////////////////////////
	///@brief Removes all the current observers in the observerArray_
	///////////////////////////////////////////////////////////////////////
	void clearObservers();

    template <class T>
    friend void setOnPress(mousePressButton* mpb,
                           T* objPtr,
                           bool(*onPress)(T*, Event));

///////////////////////////////////////////////////////////////////////
//SETTERS
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
///@brief Adds the input handler to the component. Also sets up the
/// neccessary subject and observers for this component.
///////////////////////////////////////////////////////////////////////
	void setInputHandle(ppc::InputHandler& ih);

///////////////////////////////////////////////////////////////////////
///@breif Sets the FloatRect of the sprite associated with this cmpnt.
///@details Must pass in the globad bounds of the sprite.
///////////////////////////////////////////////////////////////////////
	void setFloatRect(sf::FloatRect rect);

    sf::FloatRect getFloatRect() const;

	void setIsBeingPressed(std::string iBP);

	virtual ~mousePressButton();
	virtual bool registerInput(sf::Event ev) override;


    Subject& onClick() { return onPress_; };
    Subject& onDblClick() { return onDoublePress_; };
    Subject& onRelease() { return onRelease_; };
	Subject& onHover() { return onHover_; };

};

template<class T>
inline void setOnPress(mousePressButton* mpb, T * objPtr, bool(*onPress)(T *, Event)) {

    FreeFunctionObserver<T>* fnObsvr = new FreeFunctionObserver<T>(onPress, objPtr);

    mpb->onRelease().addObserver(fnObsvr);

}



};