#pragma once

#include <vector>
#include <string>
#include <stack>
#include "../Engine/NodeState.h"
#include "../Engine/Entity.h"
#include "../Engine/WindowInterface.h"
#include "../Game/createIcon.h"

///////////////////////////////////////////////////////////////////////
/// @author Alex Vincent
/// @brief A singleton structure to a desktop that governs displaying
/// files in the explorer window
/// @details Contains a vector of emails to which can be added to
/// the email application on the desktop. Each desktop should only
/// have one Inbox in theory.
///////////////////////////////////////////////////////////////////////

namespace ppc {

	class Explorer {

	public:

		///////////////////////////////////////////////////////////////////////
		///@brief Default constructor
		///////////////////////////////////////////////////////////////////////
		Explorer(WindowInterface*& windowToWorkOn, NodeState& ns, sf::Image& buttonSheet);

		
	private:
		WindowInterface*& windowToWorkOn_;
		NodeState& theFileTree_;
		sf::Image& buttonSheet_;
		std::stack<std::vector<ppc::Entity>> explorerHistory_;

		vector<Entity> createVectorFrame();

		void renderTopFrame();
	};

}