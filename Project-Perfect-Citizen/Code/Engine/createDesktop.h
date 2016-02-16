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

#include "Window.h"
#include "WindowInterface.h"
#include "buttonRenderComponent.h"
#include "consoleUpdateComponent.h"
#include "inputComponent.h"
#include "InputHandler.h"
#include "Entity.h"
#include "subject.h"
#include "desktop.h"
#include "textInputRenderComponent.hpp"
#include "textInputKeys.hpp"
#include "BorderDecorator.h"
#include "createIcon.h"

///////////////////////////////////////////////////////////////////////
/// @brief A toolkit of functions that sets up complete desktops (with icons)
/// @author Alex Vincent 
/// @details Create a desktopreference (statically or dynamically) and pass them
/// by reference to any one of these functions. The passed entity will
/// be augmented by the function you called on it.
///////////////////////////////////////////////////////////////////////

void createPlayerDesktop(ppc::Desktop& desktopToModify, ppc::WindowInterface& desktopWindowToModify, ppc::InputHandler& ih, sf::Image& iconSheet);