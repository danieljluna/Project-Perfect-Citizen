#pragma once

#include <iostream>
#include <fstream>
#include <SFML/Main.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "../Engine/Window.h"
#include "../Engine/inputComponent.h"
#include "../Engine/InputHandler.h"
#include "../Engine/Entity.h"
#include "../Engine/subject.h"
#include "textInputRenderComponent.hpp"
#include "textInputKeys.hpp"
#include "../Engine/InputHandler.h"
#include "animatorComponent.hpp"
#include "mousePressButton.h"
#include "consoleIconRenderComponent.h"
#include "buttonRenderComponent.h"
#include "consoleUpdateComponent.h"
#include "../Engine/NodeState.h"
#include "iconInputComponent.h"
#include "Database.h"

///////////////////////////////////////////////////////////////////////
/// @brief A toolkit of functions that turn entities into useable icons
/// @author Alex Vincent 
/// @details Create an entity (statically or dynamically) and pass them
/// by reference to any one of these functions. The passed entity will
/// be augmented by the function you called on it.
///////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
/// @brief Turns the passed entity into a useable folder Icon
///
///@param The newly created entity to add components to.
///@param The input handler of desktop window
///@param The spritesheet from which to load the icon
///@param The spritesheet of the new window's buttons in the border
///@param The desired x position of the icon
///@param The desired y position of the icon
///@param The desired scaled size of the icon
///@param The desired animation speed of the icon
///////////////////////////////////////////////////////////////////////
void spawnFolderIcon(ppc::Entity& entityToModify, ppc::Desktop& dT, ppc::InputHandler& ih, sf::Image& spriteSheet, sf::Image& buttonSheet, float x, float y, float size, float animSpeed);

//////////////////////////////////////////////////////////////////////
/// @brief Turns the passed entity into a useable settings Icon
///
///@param The newly created entity to add components to.
///@param The input handler of desktop window
///@param The spritesheet from which to load the icon
///@param The spritesheet of the new window's buttons in the border
///@param The desired x position of the icon
///@param The desired y position of the icon
///@param The desired scaled size of the icon
///@param The desired animation speed of the icon
///////////////////////////////////////////////////////////////////////
void spawnSettingsIcon(ppc::Entity& entityToModify, ppc::Desktop& dT,  ppc::InputHandler& ih, sf::Image& spriteSheet, sf::Image& buttonSheet, float x, float y, float size, float animSpeed);

//////////////////////////////////////////////////////////////////////
/// @brief Turns the passed entity into a useable chat Icon
///
///@param The newly created entity to add components to.
///@param The input handler of desktop window
///@param The spritesheet from which to load the icon
///@param The spritesheet of the new window's buttons in the border
///@param The desired x position of the icon
///@param The desired y position of the icon
///@param The desired scaled size of the icon
///@param The desired animation speed of the icon
///////////////////////////////////////////////////////////////////////
void spawnChatIcon(ppc::Entity& entityToModify, ppc::Desktop& dT, ppc::InputHandler& ih, sf::Image& spriteSheet, sf::Image& buttonSheet, float x, float y, float size, float animSpeed);

//////////////////////////////////////////////////////////////////////
/// @brief Turns the passed entity into a useable search Icon
///
///@param The newly created entity to add components to.
///@param The input handler of desktop window
///@param The spritesheet from which to load the icon
///@param The spritesheet of the new window's buttons in the border
///@param The desired x position of the icon
///@param The desired y position of the icon
///@param The desired scaled size of the icon
///@param The desired animation speed of the icon
///////////////////////////////////////////////////////////////////////
void spawnSearchIcon(ppc::Entity& entityToModify, ppc::Desktop& dT, ppc::InputHandler& ih, sf::Image& spriteSheet, sf::Image& buttonSheet, float x, float y, float size, float animSpeed);

//////////////////////////////////////////////////////////////////////
/// @brief Turns the passed entity into a useable pipeline extraction Icon
///
///@param The newly created entity to add components to.
///@param The input handler of desktop window
///@param The spritesheet from which to load the icon
///@param The spritesheet of the new window's buttons in the border
///@param The desired x position of the icon
///@param The desired y position of the icon
///@param The desired scaled size of the icon
///@param The desired animation speed of the icon
///////////////////////////////////////////////////////////////////////
void spawnDataGraphIcon(ppc::Entity& entityToModify, ppc::Desktop& dT, ppc::InputHandler& ih, sf::Image& spriteSheet, sf::Image& buttonSheet, float x, float y, float size, float animSpeed);

//////////////////////////////////////////////////////////////////////
/// @brief Turns the passed entity into a useable help Icon
///
///@param The newly created entity to add components to.
///@param The input handler of desktop window
///@param The spritesheet from which to load the icon
///@param The spritesheet of the new window's buttons in the border
///@param The desired x position of the icon
///@param The desired y position of the icon
///@param The desired scaled size of the icon
///@param The desired animation speed of the icon
///////////////////////////////////////////////////////////////////////
void spawnHelpIcon(ppc::Entity& entityToModify, ppc::Desktop& dT, ppc::InputHandler& ih, sf::Image& spriteSheet, sf::Image& buttonSheet, float x, float y, float size, float animSpeed);

//////////////////////////////////////////////////////////////////////
/// @brief Turns the passed entity into a useable browser Icon
///
///@param The newly created entity to add components to.
///@param The input handler of desktop window
///@param The spritesheet from which to load the icon
///@param The spritesheet of the new window's buttons in the border
///@param The desired x position of the icon
///@param The desired y position of the icon
///@param The desired scaled size of the icon
///@param The desired animation speed of the icon
///////////////////////////////////////////////////////////////////////
void spawnBrowserIcon(ppc::Entity& entityToModify, ppc::Desktop& dT, ppc::InputHandler& ih, sf::Image& spriteSheet, sf::Image& buttonSheet, float x, float y, float size, float animSpeed);

//////////////////////////////////////////////////////////////////////
/// @brief Turns the passed entity into a useable hard drive Icon
///
///@param The newly created entity to add components to.
///@param The input handler of desktop window
///@param The spritesheet from which to load the icon
///@param The spritesheet of the new window's buttons in the border
///@param The desired x position of the icon
///@param The desired y position of the icon
///@param The desired scaled size of the icon
///@param The desired animation speed of the icon
///////////////////////////////////////////////////////////////////////
void spawnHardDriveIcon(ppc::Entity& entityToModify, ppc::Desktop& dT, ppc::InputHandler& ih, sf::Image& spriteSheet, sf::Image& buttonSheet, float x, float y, float size, float animSpeed);

//////////////////////////////////////////////////////////////////////
/// @brief Turns the passed entity into a useable console Icon
///
///@param The newly created entity to add components to.
///@param The desktop in which to link the file tree to the console
///@param The input handler of desktop window
///@param The spritesheet from which to load the icon
///@param The spritesheet of the new window's buttons in the border
///@param The desired x position of the icon
///@param The desired y position of the icon
///@param The desired scaled size of the icon
///@param The desired animation speed of the icon
///////////////////////////////////////////////////////////////////////
void spawnConsoleIcon(ppc::Entity& entityToModify, ppc::Desktop& dt, ppc::InputHandler& ih, sf::Image& spriteSheet, sf::Image& buttonSheet, float x, float y, float size, float animSpeed);



