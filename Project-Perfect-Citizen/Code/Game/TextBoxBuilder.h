#pragma once

#include <SFML/Graphics/Font.hpp>
#include <string>
#include "../Engine/renderComponent.h"
#include "../Engine/InputHandler.h"
#include "../Game/TextBoxInputComponent.h"


namespace ppc {
	///////////////////////////////////////////////////////////////////////
	/// @brief Designated Generic Builder Object for non-editable Text Output Fields
	/// @author Alex Vincent 
	/// @details A package with API function calls allowing for individual
	/// creations and augmentations of an editable ext field. This augments 
	/// and returns an entity.
	///////////////////////////////////////////////////////////////////////
	class TextBoxBuilder {
	private:
		sf::Font* f;
		sf::Color* c;
		float xPos;
		float yPos;
		int s;
		std::string stringToRender;
		InputHandler* ih;
		TextBoxInputComponent* tbi;
		WindowInterface* cw;


	public:
		///////////////////////////////////////////////////////////////////////
		/// @brief Constructor for an editable text box to the screen
		/// @details Creates a default text box
		///////////////////////////////////////////////////////////////////////
		TextBoxBuilder();

		~TextBoxBuilder();

		void setFont(sf::Font& font);

		void setColor(sf::Color color);

		void setPosition(sf::Vector2f vec);

		void setSize(int size);

		void setString(std::string str);

		void setInputHandle(ppc::InputHandler&);

		void setContainingWindow(WindowInterface*);

		TextBoxInputComponent* getTextBoxInputComponent();

		void create(Entity&);

	};


};