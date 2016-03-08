#pragma once

#include "../Engine/WindowInterface.h"
#include "../Engine/InputHandler.h"
#include "../Engine/NodeState.h"
#include "buttonUpdateComponent.h"
#include "Database.h"
#include "createButton.h"
#include "../Game/databaseSearchInputComponent.h"
#include "createListElement.h"



///////////////////////////////////////////////////////////////////////
/// @brief A toolkit of functions that sets up a complete window
/// @author Alex Vincent 
/// @details Create/initialize a WindowInterface pointer and pass it by 
/// pointer to any one of these functions. The passed WindowInterface 
/// will be augmented by the function you called on it. Make sure that
/// the input handler you pass is unique to that window.
///////////////////////////////////////////////////////////////////////

namespace ppc {
	//typedef bool (databaseSearchInputComponent::*goBack) (sf::Event&);
	//using backFunction = bool(databaseSearchInputComponent::*goBack)(sf::Event& ev);
	///////////////////////////////////////////////////////////////////////
	///@brief Constructs a console window on the WindowInterface passed.
	///
	///@param The newly created window to add components/entities to.
	///@param The input handler of the listened-to window.
	///@param The filetree for which the console will work on.
	///@param Sprite sheet of it's border component's buttons
	///////////////////////////////////////////////////////////////////////
void spawnConsole(WindowInterface*& windowToModify, InputHandler& ih, NodeState& ns, 
	sf::Image& buttonSheet, float x, float y);

///////////////////////////////////////////////////////////////////////
///@brief Constructs a database window on the WindowInterface passed.
///
///@param The newly created window to add components/entities to.
///@param The input handler of the listened-to window.
///@param Sprite sheet of it's border component's buttons
///////////////////////////////////////////////////////////////////////
void spawnDatabase(WindowInterface*& windowToModify, InputHandler& ih, Database* db,
	sf::Image& buttonSheet, float x, float y);
    
    
///////////////////////////////////////////////////////////////////////
///@brief Constructs a pipeline window on the WindowInterface passed.
///
///@param The newly created window to add components/entities to.
///@param The input handler of the listened-to window.
///@param Sprite sheet of it's border component's buttons
///////////////////////////////////////////////////////////////////////
void spawnPipeline(WindowInterface*& windowToModify, InputHandler& ih, Database* db,
        sf::Image& buttonSheet, float x, float y);
    
void spawnFile(WindowInterface*& windowToModify, InputHandler& ih, NodeState & ns, sf::Image& buttonSheet, float x, float y, string path);

void spawnInbox(WindowInterface*& windowToModify, InputHandler& ih, sf::Image& buttonSheet, float x, float y);
};

