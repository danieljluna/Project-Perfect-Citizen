#pragma once

#include <SFML/Graphics.hpp>

#include "../Engine/inputComponent.h"
#include "../Engine/InputHandler.h"
#include "../Engine/Entity.h"
#include "../Engine/subject.h"
#include "../Engine/desktop.h"
#include "createWindow.h"
#include "../Engine/Window.h"
#include "../Engine/WindowInterface.h"


///////////////////////////////////////////////////////////////////////
/// @brief Designated non-mouse input handling for desktop icons
/// @author Alex Vincent 
/// @details Functionality: opens windows and places them on the desktop
/// by listening for double clicks from the mouse input
///////////////////////////////////////////////////////////////////////


class iconInputComponent : public ppc::InputComponent {
private:

	ppc::Desktop& theDesktop_;
	ppc::InputHandler& inputHandler_;

public:

	iconInputComponent() = delete;
	iconInputComponent(ppc::Desktop& theDesktop, ppc::InputHandler& ih);
	virtual ~iconInputComponent();
	virtual bool registerInput(sf::Event& ev) override;
	virtual void recieveMessage(msgType message) override;

};