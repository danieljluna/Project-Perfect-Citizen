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
#include "animatorComponent.hpp"
#include "mousePressButton.h"
#include "consoleIconRenderComponent.h"
#include "buttonRenderComponent.h"
#include "consoleUpdateComponent.h"
#include "NodeState.h"

void spawnConsoleIcon(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spriteSheet);

void spawnSettingsIcon(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spriteSheet);

void spawnFolderIcon(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spriteSheet);