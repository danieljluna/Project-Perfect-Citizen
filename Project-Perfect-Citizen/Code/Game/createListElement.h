#pragma once

#include "../Engine/InputHandler.h"
#include "emailListElementRenderComponent.h"
#include "emailListElementInputComponent.h"
#include "../Engine/Entity.h"
#include "Email.h"

///////////////////////////////////////////////////////////////////////
/// @brief A toolkit of functions that sets up a list element in an app
/// @author Alex Vincent 
/// @details Create/initialize an Entity and pass it by 
/// pointer to any one of these functions. The passed Entity
/// will be augmented by the function you called on it. Make sure that
/// the input handler you pass is unique to that window.
///////////////////////////////////////////////////////////////////////

namespace ppc {
	
	///////////////////////////////////////////////////////////////////////
	/// @brief Creates one element of an email list inside of the inbox
	/// @author Alex Vincent 
	/// @details A box with text in it that listens for clicks.
	/// @note Apologies for the monstrous parameter list - it's not a
	/// class so we can't have a default constructor behavior
	//////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////
	/// @details Creates a clickable email list element in the inbox
	/// @param The naked entity to augment into an emailListElement
	/// @param A reference to the desktop so this element can spawn new windows
	/// @param A reference to the close button sprite sheet 
	/// @param A reference to the window's input handler 
	/// @param A reference to the element's textfield
	/// @param A reference to the email to eventually display
	/// @param An integer specifying the box's X position
	/// @param An integer specifying the box's Y position
	/// @param An integer specifying the box's Width
	/// @param An integer specifying the box's Height
	/// @param An integer specifying the text's x position
	/// @param An integer specifying the text's y position
	/// @param An integer specifying the text/font's size
	///////////////////////////////////////////////////////////////////////
	void createEmailListElement(ppc::Entity& entityToModify, Desktop& dt, sf::Image& buttonSheet, ppc::InputHandler& ih, 
		sf::Font& f, Email* eM, int boxX, int boxY, int boxWidth, int boxHeight, int x, int y, int size);

	//////////////////////////////////////////////////////////////////////
	/// @details Creates a clickable context menu list element in the cm.
	/// @param The naked entity to augment into an emailListElement
	/// @param A reference to the desktop so this element can spawn new windows
	/// @param A reference to the window's input handler 
	/// @param A reference to the element's font
	/// @param The string label of the list element
	/// @param An integer specifying the box's X position
	/// @param An integer specifying the box's Y position
	/// @param An integer specifying the box's Width
	/// @param An integer specifying the box's Height
	/// @param An integer specifying the text's x position
	/// @param An integer specifying the text's y position
	/// @param An integer specifying the text/font's size
	///////////////////////////////////////////////////////////////////////
	void createContextListElement(ppc::Entity& entityToModify, WindowInterface* win, Desktop& dt, ppc::InputHandler& ih,
		sf::Font& f, std::string s, bool(*func)(Desktop* desk, Event ev), int boxX, int boxY, int boxWidth, int boxHeight, int x, int y, int size);

}