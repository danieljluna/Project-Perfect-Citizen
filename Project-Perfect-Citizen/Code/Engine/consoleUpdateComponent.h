#pragma once

#include <SFML/Graphics.hpp>
#include "updateComponent.h"
#include "buttonRenderComponent.h"
#include "textInputRenderComponent.hpp"
#include "textInputKeys.hpp"
#include "NodeState.h"

using namespace std;

///////////////////////////////////////////////////////////////////////
/// @brief Designated Update Component for Console
/// @author Alex Vincent
/// @details The Animator Component updates the frame for
///          Button Render Components that have more than two states
///////////////////////////////////////////////////////////////////////

class consoleUpdateComponent : public ppc::UpdateComponent {

private:
	ppc::NodeState& fileTree;
    bool canParse;
	string lastCommand;
    std::vector<string> commandVec;

public:
	consoleUpdateComponent(ppc::NodeState& ns);
	consoleUpdateComponent();
	void toggleParsing();
	void executeCommand(string str);
	~consoleUpdateComponent();
	void update(sf::Time& deltaTime) override;

};