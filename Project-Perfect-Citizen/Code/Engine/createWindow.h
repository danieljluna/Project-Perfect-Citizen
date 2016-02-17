#pragma once

#include <SFML/System/Vector2.hpp>
#include "WindowInterface.h"
#include "InputHandler.h"
#include "NodeState.h"



namespace ppc {

WindowInterface* spawnConsole(InputHandler& ih, NodeState& ns, int x, int y, int w, int h);

};

