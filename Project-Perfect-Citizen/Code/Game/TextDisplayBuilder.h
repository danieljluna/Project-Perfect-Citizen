#pragma once

#include <SFML/Graphics/Font.hpp>
#include <string>
#include "../Engine/renderComponent.h"
#include "../Engine/InputHandler.h"


namespace ppc {

	///////////////////////////////////////////////////////////////////////
	/// @brief Designated Generic Builder Object for non-editable Text Output Fields
	/// @author Alex Vincent 
	/// @details A package with API function calls allowing for individual
	/// creations and augmentations of a text field. This augments and returns
	/// an entity.
	///////////////////////////////////////////////////////////////////////
	class TextDisplayBuilder {
	private:
		sf::Font* f;
		sf::Color c;
		float xPos;
		float yPos;
		int s;
		std::string stringToRender;


	public:
		///////////////////////////////////////////////////////////////////////
		/// @brief Constructor for non-editable text rendered to the screen
		/// @details Creates a default text output
		///////////////////////////////////////////////////////////////////////
		TextDisplayBuilder();

		~TextDisplayBuilder();

		void setFont(sf::Font& font);

		void setColor(sf::Color color);

		void setPosition(sf::Vector2f vec);

		void setSize(int size);

		void setString(std::string str);

		void create(Entity&);

	};


};