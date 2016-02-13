#pragma once

#include <SFML/Graphics.hpp>

#include "inputComponent.h"
#include "InputHandler.h"
#include "Entity.h"
#include "subject.h"
#include "desktop.h"
#include "createWindow.h"
#include "Window.h"
#include "WindowInterface.h"


///////////////////////////////////////////////////////////////////////
/// @brief Designated non-mouse input handling for desktop icons
/// @author Alex Vincent 
/// @details Functionality: opens windows and places them on the desktop
/// by listening for double clicks from the mouse input
///////////////////////////////////////////////////////////////////////



class iconInputComponent : public ppc::InputComponent {
private:

	ppc::Desktop& theDesktop;
	ppc::InputHandler& inputHandler;

public:

	iconInputComponent() = delete;
	iconInputComponent(ppc::Desktop& theDesktop, ppc::InputHandler& ih);
	virtual ~iconInputComponent();
	virtual bool registerInput(sf::Event& ev) override;
	virtual void recieveMessage(msgType message) override;

};