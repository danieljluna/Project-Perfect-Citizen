#pragma once

#ifdef WINDOWS_MARKER
#define resourcePath() string("Resources/")
#else
#include "ResourcePath.hpp"
#endif

#include "createWindow.h"

#include <iostream>
#include <fstream>
#include <SFML/Main.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "../Engine/Window.h"
#include "../Engine/WindowInterface.h"
#include "buttonRenderComponent.h"
#include "consoleUpdateComponent.h"
#include "../Engine/inputComponent.h"
#include "../Engine/InputHandler.h"
#include "../Engine/Entity.h"
#include "../Engine/subject.h"
#include "../Engine/desktop.h"
#include "textInputRenderComponent.hpp"
#include "textInputKeys.hpp"
#include "../Engine/BorderDecorator.h"
#include "createIcon.h"

///////////////////////////////////////////////////////////////////////
/// @brief A toolkit of functions that sets up complete desktops
/// @author Alex Vincent 
/// @details Create a desktop reference (statically or dynamically) and
/// pass it by reference to any one of these functions. The passed entity 
/// will be augmented by the function you called on it.
///////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////
///@brief Constructs the entire player's desktop with icons.
///
///@param The newly created desktop to add components/entities to.
///@param A reference to the desktop's window interface
///@param A reference to the desktop's window interface's input handler
///@param A sprite sheet from which to read the icon images
///////////////////////////////////////////////////////////////////////
void createPlayerDesktop(ppc::Desktop& desktopToModify, ppc::WindowInterface& desktopWindowToModify, ppc::InputHandler& ih, sf::Image& iconSheet);