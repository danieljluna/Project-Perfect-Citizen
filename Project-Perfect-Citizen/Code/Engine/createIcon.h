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

///////////////////////////////////////////////////////////////////////
/// @brief A toolkit of functions that turn entities into useable icons
/// @author Alex Vincent 
/// @details Create an entity (statically or dynamically) and pass them
/// by reference to any one of these functions. The passed entity will
/// be augmented by the function you called on it.
///////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/// @brief Turns the passed entity into a useable console Icon
/// Pass it the entity, a shared input handler, a spritesheet with 
/// the button animations at (0, 8), (x, y position), and a square scale size.
///////////////////////////////////////////////////////////////////////
void spawnConsoleIcon(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spriteSheet, float x, float y, float size);

//////////////////////////////////////////////////////////////////////
/// @brief Turns the passed entity into a useable settings Icon
/// Pass it the entity, a shared input handler, a spritesheet with 
/// the button animations at (0, 1), (x, y position), and a square scale size.
///////////////////////////////////////////////////////////////////////
void spawnSettingsIcon(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spriteSheet, float x, float y, float size);

//////////////////////////////////////////////////////////////////////
/// @brief Turns the passed entity into a useable folder Icon
/// Pass it the entity, a shared input handler, a spritesheet with 
/// the button animations at (0, 0), (x, y position), and a square scale size.
///////////////////////////////////////////////////////////////////////
void spawnFolderIcon(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spriteSheet, float x, float y, float size);