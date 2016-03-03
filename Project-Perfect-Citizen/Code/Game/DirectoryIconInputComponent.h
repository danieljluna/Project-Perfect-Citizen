#pragma once
#include "../Engine/debug.h"
#include "iconInputComponent.h"
#include <iostream>
#include <string>

///////////////////////////////////////////////////////////////////////
/// @brief Designated non-mouse input handling for desktop icons
/// @author Alex Vincent 
/// @details Functionality: opens windows and places them on the desktop
/// by listening for double clicks from the mouse input
///////////////////////////////////////////////////////////////////////
namespace ppc {

	class DirectoryIconInputComponent : public ppc::InputComponent {
	private:

		sf::Image& bs_;

	public:

		DirectoryIconInputComponent() = delete;

		//////////////////////////////////////////////////////////////////////
		/// @brief Constructor
		///
		///@param The newly created icon entity to add components to.
		///@param The buttonSheet of the window it will create's buttons.
		///////////////////////////////////////////////////////////////////////
		DirectoryIconInputComponent(sf::Image& buttonSheet_);
		virtual ~DirectoryIconInputComponent();
		virtual bool registerInput(sf::Event& ev) override;
		virtual void recieveMessage(msgType message) override;

	};

};