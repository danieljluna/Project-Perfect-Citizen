#pragma once

#include "../Engine/WindowInterface.h"
#include "../Engine/InputHandler.h"
#include "../Engine/NodeState.h"


namespace ppc {

WindowInterface* spawnConsole(InputHandler& ih, NodeState& ns, int x, int y, int w, int h);

};

