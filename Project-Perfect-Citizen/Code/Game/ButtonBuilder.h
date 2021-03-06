#pragma once

#include "../Engine/renderComponent.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "../Engine/renderComponent.h"
#include "../Engine/InputHandler.h"
#include "../Game/mousePressButton.h"

namespace ppc {
	///////////////////////////////////////////////////////////////////////
	/// @brief Designated Generic Builder Object for Buttons
	/// @author Alex Vincent 
	/// @details A fully dynamic builder class that allows the caller to make
	/// a button from a spritesheet or a custom small/large button.
	/// @note Small buttons are created by making a button with a label of only
	/// one character, whereas large buttons have labels of > 1 characters.
	/// This can also be used to generate icons, just make sure to set
	/// the button to non-clickable and give it the right sprite indicies.
	///////////////////////////////////////////////////////////////////////
	class ButtonBuilder {
	private:
		int sheetX;
		int sheetY;
		int width;
		int frames;
		float size;

		float posX;
		float posY;

		sf::Sprite* sprtUp;
		sf::Sprite* sprtDown;

		sf::Image* spriteSheet;
		ppc::InputHandler* inputHandle;

		std::string label;
		sf::Font* font;
		int labelSize;
		bool clickable = true;

	public:
		///////////////////////////////////////////////////////////////////////
		/// @brief Constructor for buttonRenderComponent
		/// @details Creates a default button
		///////////////////////////////////////////////////////////////////////
		ButtonBuilder();

		~ButtonBuilder();

		///////////////////////////////////////////////////////////////////////
		/// @brief Set the down and up sprite when the button is pressed
		///////////////////////////////////////////////////////////////////////
		void setSpritesByIndicies(int x, int y, int r, int f);

		///////////////////////////////////////////////////////////////////////
		/// @brief Set the scale of the button.
		/// @param A scaling factor to the button
		/// @note The original size of a small button sprite is 128x128 and 
		/// the large button sprite is 128x256 in (width x height) format.
		///////////////////////////////////////////////////////////////////////
		void setSize(float s);

		///////////////////////////////////////////////////////////////////////
		/// @brief Sets whether the button will be non-clickable.
		/// @note This means the button will be non-clickable for it's entire
		/// life cycle. Use this when creating non-clickable icons that
		/// want to use a button builder but don't want click functionality.
		///////////////////////////////////////////////////////////////////////
		void setNonClickable();

		///////////////////////////////////////////////////////////////////////
		/// @brief Set a custom string button label to display on the button
		/// @param The string to be labeled onto the button
		///////////////////////////////////////////////////////////////////////
		void setLabelMessage(std::string l);

		///////////////////////////////////////////////////////////////////////
		/// @brief Set a custom string button label to display on the button
		/// @param The font of the custom label
		///////////////////////////////////////////////////////////////////////
		void setLabelFont(sf::Font&);

		///////////////////////////////////////////////////////////////////////
		/// @brief Set a custom string button label to display on the button
		/// @param The character size of the label
		///////////////////////////////////////////////////////////////////////
		void setLabelSize(int);

		///////////////////////////////////////////////////////////////////////
		/// @brief Set the position of the button
		/// @param X position of the button
		/// @param Y position of the button
		///////////////////////////////////////////////////////////////////////
		void setButtonPosition(float x, float y);

		///////////////////////////////////////////////////////////////////////
		/// @brief Set the position of the button
		/// @param Vector containing the x and y position of the button
		///////////////////////////////////////////////////////////////////////
		void setButtonPosition(sf::Vector2f pos);

		///////////////////////////////////////////////////////////////////////
		/// @brief Set the sprite sheet of the button
		/// @param The sprite sheet sf::image of the button
		///////////////////////////////////////////////////////////////////////
		void setSpriteSheet(sf::Image&);

		///////////////////////////////////////////////////////////////////////
		/// @brief Set the input handle of the button
		/// @param The window's input handler
		///////////////////////////////////////////////////////////////////////
		void setInputHandle(ppc::InputHandler&);

		///////////////////////////////////////////////////////////////////////
		/// @brief Returns the constructed button
		/// @param The entity to modify
		///////////////////////////////////////////////////////////////////////
		void create(Entity&);
	};

	///////////////////////////////////////////////////////////////////////
	/// @brief Returns the constructed button, with a attached function
	/// observer.
	/// @param The entity to modify
	/// @param The target class object
	/// @param The function to execute on a click
	///////////////////////////////////////////////////////////////////////
	template<class T>
	void createWithEventFunc(ButtonBuilder& builder, Entity& e, T* target, bool(*func)(T *, ppc::Event)) {

		builder.create(e);
		size_t s = e.cmpntCount();
		ppc::mousePressButton* mpb = dynamic_cast<mousePressButton*>(e.getComponent(s-1));

		if (mpb != nullptr) {
			setOnPress(mpb, target, func);
		} else {
			return;
		}
	}


};


