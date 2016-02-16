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
/// @brief A toolkit of functions that turn entities into useable buttons
/// @author Alex Vincent 
/// @details Create an entity (statically or dynamically) and pass them
/// by reference to any one of these functions. The passed entity will
/// be augmented by the function you called on it.
///////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/// @brief Turns the passed entity into a useable back button
/// Pass it the entity, a shared input handler, a spritesheet with 
/// the button animations at (0, 3, 1), (x, y position), and a square scale size.
///////////////////////////////////////////////////////////////////////
void spawnBackButton(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size);

//////////////////////////////////////////////////////////////////////
/// @brief Turns the passed entity into a useable start button
/// Pass it the entity, a shared input handler, a spritesheet with 
/// the button animations at (0, 3, 1), (x, y position), and a square scale size.
///////////////////////////////////////////////////////////////////////
void spawnStartButton(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size);

//////////////////////////////////////////////////////////////////////
/// @brief Turns the passed entity into a useable next button
/// Pass it the entity, a shared input handler, a spritesheet with 
/// the button animations, (x, y position), and a square scale size.
///////////////////////////////////////////////////////////////////////
void spawnNextButton(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size);

//////////////////////////////////////////////////////////////////////
/// @brief Turns the passed entity into a useable blank large button
/// Pass it the entity, a shared input handler, a spritesheet with 
/// the button animations, (x, y position), and a square scale size.
///////////////////////////////////////////////////////////////////////
void spawnBlankLargeButton(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size);

//////////////////////////////////////////////////////////////////////
/// @brief Turns the passed entity into a okay button
/// Pass it the entity, a shared input handler, a spritesheet with 
/// the button animations, (x, y position), and a square scale size.
///////////////////////////////////////////////////////////////////////
void spawnOkayButton(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size);

//////////////////////////////////////////////////////////////////////
/// @brief Turns the passed entity into a cancel button
/// Pass it the entity, a shared input handler, a spritesheet with 
/// the button animations, (x, y position), and a square scale size.
///////////////////////////////////////////////////////////////////////
void spawnCancelButton(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size);

//////////////////////////////////////////////////////////////////////
/// @brief Turns the passed entity into a useable close button
/// Pass it the entity, a shared input handler, a spritesheet with 
/// the button animations, (x, y position), and a square scale size.
///////////////////////////////////////////////////////////////////////
void spawnCloseButton(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size);

//////////////////////////////////////////////////////////////////////
/// @brief Turns the passed entity into a useable maximize button
/// Pass it the entity, a shared input handler, a spritesheet with 
/// the button animations, (x, y position), and a square scale size.
///////////////////////////////////////////////////////////////////////
void spawnMaximizeButton(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size);

//////////////////////////////////////////////////////////////////////
/// @brief Turns the passed entity into a useable minimize button
/// Pass it the entity, a shared input handler, a spritesheet with 
/// the button animations, (x, y position), and a square scale size.
///////////////////////////////////////////////////////////////////////
void spawnMinimizeButton(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size);


//////////////////////////////////////////////////////////////////////
/// @brief Turns the passed entity into a useable blank small button
/// Pass it the entity, a shared input handler, a spritesheet with 
/// the button animations, (x, y position), and a square scale size.
///////////////////////////////////////////////////////////////////////
void spawnBlankSmallButton(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size);

//////////////////////////////////////////////////////////////////////
/// @brief Turns the passed entity into a useable up button
/// Pass it the entity, a shared input handler, a spritesheet with 
/// the button animations, (x, y position), and a square scale size.
///////////////////////////////////////////////////////////////////////
void spawnUpButton(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size);

//////////////////////////////////////////////////////////////////////
/// @brief Turns the passed entity into a useable down button
/// Pass it the entity, a shared input handler, a spritesheet with 
/// the button animations, (x, y position), and a square scale size.
///////////////////////////////////////////////////////////////////////
void spawnDownButton(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size);

//////////////////////////////////////////////////////////////////////
/// @brief Turns the passed entity into a useable right button
/// Pass it the entity, a shared input handler, a spritesheet with 
/// the button animations, (x, y position), and a square scale size.
///////////////////////////////////////////////////////////////////////
void spawnRightButton(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size);

//////////////////////////////////////////////////////////////////////
/// @brief Turns the passed entity into a useable left button
/// Pass it the entity, a shared input handler, a spritesheet with 
/// the button animations, (x, y position), and a square scale size.
///////////////////////////////////////////////////////////////////////
void spawnLeftButton(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size);

//////////////////////////////////////////////////////////////////////
/// @brief Turns the passed entity into a useable scroll bar container
/// Pass it the entity, a shared input handler, a spritesheet with 
/// the button animations, (x, y position), and a square scale size.
///////////////////////////////////////////////////////////////////////
void spawnScrollBarContainer(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size);

//////////////////////////////////////////////////////////////////////
/// @brief Turns the passed entity into a useable scroll bar handle
/// Pass it the entity, a shared input handler, a spritesheet with 
/// the button animations, (x, y position), and a square scale size.
///////////////////////////////////////////////////////////////////////
void spawnScrollBarHandle(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size);

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