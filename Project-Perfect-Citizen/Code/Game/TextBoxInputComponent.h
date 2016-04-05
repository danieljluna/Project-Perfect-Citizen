#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "../Engine/inputComponent.h"
#include "../Engine/InputHandler.h"
#include "../Engine/Entity.h"
#include "../Engine/subject.h"
#include "../Game/TextBoxRenderComponent.h"

namespace ppc {

	///////////////////////////////////////////////////////////////////////
	/// @brief Designated Input Component for a generic fillable text box
	/// @author Alex Vincent
	/// @details Input Component to handle TextEnter events from
	///          the keyboard. This will mainly be used in combination
	///          with a text box render component.
	///////////////////////////////////////////////////////////////////////
	
	class TextBoxInputComponent : public ppc::InputComponent {
	private:

		//sf::Sprite& textBoxSprt;
		TextBoxRenderComponent& textBox;
		InputHandler& inputHandle;
		std::string str;
		bool isCollision(sf::Vector2i);

	public:

		TextBoxInputComponent() = delete;

		///////////////////////////////////////////////////////////////////////
		/// @brief Constructor for TextBoxInputComponent
		/// @param ih is the input handler
		/// @param s is the render component where the text will be drawn
		///////////////////////////////////////////////////////////////////////
		TextBoxInputComponent(ppc::InputHandler& ih, TextBoxRenderComponent &r);

		string getString();

		virtual ~TextBoxInputComponent();
		virtual bool registerInput(sf::Event& ev) override;

	};


};