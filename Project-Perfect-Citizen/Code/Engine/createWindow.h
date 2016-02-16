#pragma once

#include "WindowInterface.h"
#include "InputHandler.h"
#include "NodeState.h"


namespace ppc {

WindowInterface* spawnConsole(InputHandler& ih, NodeState& ns, int x, int y, int w, int h);

};

