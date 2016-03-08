#pragma once

#include "mousePressButton.h"
#include "emailListElementRenderComponent.h"
#include "../Engine/Entity.h"

///////////////////////////////////////////////////////////////////////
/// @brief A toolkit of functions that sets up a list element in an app
/// @author Alex Vincent 
/// @details Create/initialize an Entity and pass it by 
/// pointer to any one of these functions. The passed Entity
/// will be augmented by the function you called on it. Make sure that
/// the input handler you pass is unique to that window.
///////////////////////////////////////////////////////////////////////

namespace ppc {
	
	void createEmailListElement(ppc::Entity& entityToModify, sf::Font& f, std::string subjectLine, int boxX, int boxY, int boxWidth, int boxHeight, int x, int y, int size);

}