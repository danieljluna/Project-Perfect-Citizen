#pragma once


#include <SFML/Graphics.hpp>
#include <array>

#include "../Engine/inputComponent.h"
#include "../Engine/InputHandler.h"
#include "../Engine/Entity.h"

///////////////////////////////////////////////////////////////////////
/// @brief Designated Input Component for an email element in the inbox
/// @author Alex Vincent 
/// @details Listens for clicks on an email list element and opens
/// the corresponding window for the email clicked on
/// @note May make a generic ListElementInputComponent and switch
/// on the kind that was clicked on. Talk to Alex about this.
///////////////////////////////////////////////////////////////////////


class emailListElementInputComponent : public ppc::InputComponent {
private:

	sf::FloatRect boxRect;
	sf::Clock mouseClock;
	sf::Int32 mouseTime;
	bool isCollision(sf::Vector2i);

public:

	emailListElementInputComponent();

	///////////////////////////////////////////////////////////////////////
	///@brief This Ctor will be depricated soon. Please use the default 
	///Ctor and setter functions instead.
	///////////////////////////////////////////////////////////////////////
	emailListElementInputComponent(ppc::InputHandler& ih, sf::FloatRect rect);


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

	virtual ~emailListElementInputComponent();

	virtual bool registerInput(sf::Event& ev) override;

};