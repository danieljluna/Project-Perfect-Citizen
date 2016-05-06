#pragma once

#include <iostream>
#include <fstream>
#include <SFML/Main.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "Database.h"
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
#include "databaseSearchInputComponent.h"
#include "../Engine/Network.h"
#include "NetworkCheckFunctor.h"
#include "FloppyInputComponent.h"


//typedef bool (databaseSearchInputComponent::*backFn)(sf::Event&);
///////////////////////////////////////////////////////////////////////
/// @brief A toolkit of functions that turn entities into useable buttons
/// @author Alex Vincent 
/// @details Create an entity (statically or dynamically) and pass them
/// by reference to any one of these functions. The passed entity will
/// be augmented by the function you called on it.
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
/// @brief Turns the passed entity into a useable back button
/// Pass it the entity, a shared input handler, a spritesheet with 
/// the button animations at (0, 3, 1), (x, y position), and a square scale size.
///////////////////////////////////////////////////////////////////////
void spawnBackButton(databaseSearchInputComponent* db, ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spritesheet,
    float x, float y, float size);

//////////////////////////////////////////////////////////////////////
/// @brief Turns the passed entity into a useable start button
/// Pass it the entity, a shared input handler, a spritesheet with 
/// the button animations at (0, 3, 1), (x, y position), and a square scale size.
///////////////////////////////////////////////////////////////////////
void spawnStartButton(ppc::Entity& entityToModify, Desktop&, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size);


//////////////////////////////////////////////////////////////////////
/// @brief TEMPORARY FOR FLOPPY
///////////////////////////////////////////////////////////////////////
void spawnStartButton2(ppc::Entity& entityToModify, Desktop&, FloppyInputComponent*, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size);

// * THIS IS TEMPORARY FOR FIRST PLAYABLE *//
void spawnNetworkOkayButton(ppc::Network* theNetwork_, ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size, NetworkCheckFunctor* ncf,
	sf::Font);

//////////////////////////////////////////////////////////////////////
/// @brief Turns the passed entity into a useable confirmed icon (non clickable)
/// Pass it the entity, a shared input handler, a spritesheet with 
/// the button animations, (x, y position), and a square scale size.
///////////////////////////////////////////////////////////////////////
void spawnConfirmedIcon(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size);

//////////////////////////////////////////////////////////////////////
/// @brief Turns the passed entity into a useable alert icon (non clickable)
/// Pass it the entity, a shared input handler, a spritesheet with 
/// the button animations, (x, y position), and a square scale size.
///////////////////////////////////////////////////////////////////////
void spawnAlertIcon(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size);


//////////////////////////////////////////////////////////////////////
/// @brief Turns the passed entity into a useable alert icon (non clickable)
/// Pass it the entity, a shared input handler, a spritesheet with
/// the button animations, (x, y position), and a square scale size.
///////////////////////////////////////////////////////////////////////
void spawnPromptIcon(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size);

void spawnSuspicionButton(ppc::Entity& entityToModify, Desktop& d, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size);

namespace ppc {
	bool spawnStartMenu(Desktop*, Event);
	bool spawnSuspicionMenu(Desktop*, Event);
    bool displayFloppy(FloppyInputComponent*, Event);
	bool LogOff(Desktop*, Event);
	bool displayFileInfo(Desktop*, Event);
}
