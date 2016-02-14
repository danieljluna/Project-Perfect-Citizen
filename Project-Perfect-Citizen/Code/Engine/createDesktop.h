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

void createPlayerDesktop(ppc::Desktop& desktopToModify, ppc::WindowInterface& desktopWindowToModify, ppc::InputHandler& ih, sf::Image& iconSheet);