#pragma once

#include <vector>
#include <string>
#include <stack>
#include "../Engine/NodeState.h"
#include "../Engine/Entity.h"
#include "../Engine/WindowInterface.h"
#include "../Game/createIcon.h"
#include "../Game/explorerFolderInputComponent.h"
#include "../Game/explorerFileInputComponent.h"

///////////////////////////////////////////////////////////////////////
/// @author Alex Vincent
/// @brief A singleton structure to a desktop that governs displaying
/// files in the explorer window
/// @details Contains a vector of emails to which can be added to
/// the email application on the desktop.
///////////////////////////////////////////////////////////////////////

namespace ppc {

	class Explorer {

	public:

		///////////////////////////////////////////////////////////////////////
		///@brief Default constructor
		///////////////////////////////////////////////////////////////////////
		Explorer(Desktop& dt, WindowInterface* windowToWorkOn, NodeState& ns, sf::Image& buttonSheet, sf::Image& iconSheet);

		///////////////////////////////////////////////////////////////////////
		///@brief Re-grabs the file state from the tree
		///////////////////////////////////////////////////////////////////////
		void updateExplorerDisplay();

		///////////////////////////////////////////////////////////////////////
		///@brief Re-grabs the file state from the tree
		///////////////////////////////////////////////////////////////////////
		vector<Entity> createVectorFrame(vector<string> filenames);

		
	private:
		Desktop& theDesktop_;
		WindowInterface* windowToWorkOn_;
		NodeState& theFileTree_;
		sf::Image& buttonSheet_;
		sf::Image& iconSheet_;

		///////////////////////////////////////////////////////////////////////
		///@brief Stack of previously rendered vectors of entities
		///////////////////////////////////////////////////////////////////////
		std::stack<std::vector<ppc::Entity>> explorerHistory_;


		///////////////////////////////////////////////////////////////////////
		///@brief Displays the top vector of the stack
		///////////////////////////////////////////////////////////////////////
		void renderTopFrame();
	};

}