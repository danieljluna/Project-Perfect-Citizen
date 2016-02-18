#pragma once

#include "../Engine/WindowInterface.h"
#include "../Engine/InputHandler.h"
#include "../Engine/NodeState.h"


///////////////////////////////////////////////////////////////////////
/// @brief A toolkit of functions that sets up a complete window
/// @author Alex Vincent 
/// @details Create/initialize a WindowInterface pointer and pass it by 
/// pointer to any one of these functions. The passed WindowInterface 
/// will be augmented by the function you called on it. Make sure that
/// the input handler you pass is unique to that window.
///////////////////////////////////////////////////////////////////////

namespace ppc {

	///////////////////////////////////////////////////////////////////////
	///@brief Constructs a console window on the WindowInterface passed.
	///
	///@param The newly created window to add components/entities to.
	///@param The input handler of the listened-to window.
	///@param The filetree for which the console will work on.
	///////////////////////////////////////////////////////////////////////
void spawnConsole(WindowInterface*& windowToModify, InputHandler& ih, NodeState& ns,
	float x, float y);

};

