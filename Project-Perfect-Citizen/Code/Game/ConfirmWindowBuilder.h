#pragma once

#include "../Engine/renderComponent.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "../Engine/renderComponent.h"
#include "../Engine/InputHandler.h"
#include "../Game/mousePressButton.h"
#include "../Game/buttonRenderComponent.h"
#include "../Game/TextDisplayRenderComponent.h"
#include "../Game/errorMessageRenderComponent.h"

namespace ppc {
	class Desktop;
	///////////////////////////////////////////////////////////////////////
	/// @brief Designated Generic Builder Object for confirmation windows
	/// @author Alex Vincent 
	/// @details 
	///////////////////////////////////////////////////////////////////////
	class ConfirmWindowBuilder {
	private:

		float posX;
		float posY;

		sf::Image* spriteSheet;
		ppc::InputHandler* inputHandle;


		std::string windowCaption;

		std::string confirmMessage;
		std::string confirmButtonMessage;
		std::string cancelButtonMessage;

		sf::Font messageFont;
		sf::Font buttonFont;
		
		int messageFontSize;

		mousePressButton* confirmBtnIC;
		mousePressButton* cancelBtnIC;

	public:
		///////////////////////////////////////////////////////////////////////
		/// @brief Constructor for ConfirmWindowBuilder
		/// @details Creates a default confirm window
		///////////////////////////////////////////////////////////////////////
		ConfirmWindowBuilder();

		~ConfirmWindowBuilder();

		///////////////////////////////////////////////////////////////////////
		/// @brief Set a custom string message for the window
		/// @param The string to be labeled onto the button
		///////////////////////////////////////////////////////////////////////
		void setWindowCaption(std::string);

		///////////////////////////////////////////////////////////////////////
		/// @brief Set a custom string message for the window
		/// @param The string to be labeled onto the button
		///////////////////////////////////////////////////////////////////////
		void setPosition(sf::Vector2f pos);

		///////////////////////////////////////////////////////////////////////
		/// @brief Set a custom string message for the window
		/// @param The string to be labeled onto the button
		///////////////////////////////////////////////////////////////////////
		void setConfirmMessage(std::string);

		///////////////////////////////////////////////////////////////////////
		/// @brief Set a custom string button label to display on the button
		/// @param The string to be labeled onto the button
		///////////////////////////////////////////////////////////////////////
		void setConfirmButtonLabel(std::string);

		///////////////////////////////////////////////////////////////////////
		/// @brief Set a custom string button label to display on the button
		/// @param The string to be labeled onto the button
		///////////////////////////////////////////////////////////////////////
		void setCancelButtonLabel(std::string);

		///////////////////////////////////////////////////////////////////////
		/// @brief Set a custom string button label to display on the button
		/// @param The font of the custom label
		///////////////////////////////////////////////////////////////////////
		void setMessageFont(sf::Font);

		///////////////////////////////////////////////////////////////////////
		/// @brief Set a custom string button label to display on the button
		/// @param The font of the custom label
		///////////////////////////////////////////////////////////////////////
		void setMessageFontSize(int);

		///////////////////////////////////////////////////////////////////////
		/// @brief Set a custom string button label to display on the button
		/// @param The font of the custom label
		///////////////////////////////////////////////////////////////////////
		void setButtonLabelFont(sf::Font);

		///////////////////////////////////////////////////////////////////////
		/// @brief Set the sprite sheet of the button
		/// @param The sprite sheet sf::image of the button
		///////////////////////////////////////////////////////////////////////
		void setSpriteSheet(sf::Image&);

		mousePressButton* getConfirmButtonMPB();

		mousePressButton* getCancelButtonMPB();

		///////////////////////////////////////////////////////////////////////
		/// @brief Returns the constructed confirm window
		/// @param The entity to modify
		///////////////////////////////////////////////////////////////////////
		void create(WindowInterface*&);

	};

	bool ConfirmSubmitFiles(ppc::Desktop * ptr, ppc::Event ev);

	///////////////////////////////////////////////////////////////////////
	/// @brief Returns the constructed button, with a attached function
	/// observer.
	/// @param The entity to modify
	/// @param The target class object
	/// @param The function to execute on a click
	///////////////////////////////////////////////////////////////////////
	template<class T>
	void createWithEventFunc(ConfirmWindowBuilder& builder, WindowInterface*& e, T* target, bool(*func)(T *, ppc::Event)) {

		builder.create(e);
		ppc::mousePressButton* mpb = builder.getConfirmButtonMPB();
			
		if (mpb != nullptr) setOnPress(mpb, target, func);
		else return;
	}

};