#pragma once

#include "../Engine/WindowInterface.h"
#include "../Engine/InputHandler.h"
#include "../Engine/NodeState.h"


///////////////////////////////////////////////////////////////////////
/// @brief A toolkit of functions that sets up a complete window
/// @author Alex Vincent 
/// @details Create/initialize a WindowInterface pointer and pass it by 
/// pointer to any one of these functions. The passed WindowInterface 
/// will be augmented by the function you called on it.
///////////////////////////////////////////////////////////////////////

namespace ppc {

	///////////////////////////////////////////////////////////////////////
	///@brief Constructs a console window on the WindowInterface passed.
	///
	///@param The newly created window to add components/entities to.
	///@param The input handler of which the window will listen to.
	///@param The filetree for which the console will work on.
	///////////////////////////////////////////////////////////////////////
void spawnConsole(WindowInterface* windowToModify, InputHandler& ih, NodeState& ns,
	float x, float y);

};

