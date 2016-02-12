#pragma once

#include <iostream>
#include <fstream>
#include <SFML/Main.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "Window.h"
#include "inputComponent.h"
#include "InputHandler.h"
#include "Entity.h"
#include "subject.h"
#include "textInputRenderComponent.hpp"
#include "textInputKeys.hpp"
#include "InputHandler.h"
#include "buttonRenderComponent.h"
#include "consoleUpdateComponent.h"
#include "NodeState.h"

ppc::Window* spawnConsole(ppc::InputHandler& ih, ppc::NodeState& ns);