#pragma once

#include "../Engine/renderComponent.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "../Engine/renderComponent.h"
#include "../Engine/InputHandler.h"
#include "../Game/mousePressButton.h"
#include "../Game/buttonRenderComponent.h"
#include "../Game/TextDisplayRenderComponent.h"

namespace ppc {
	///////////////////////////////////////////////////////////////////////
	/// @brief Designated Generic Builder Object for Context List Element
	/// ENTITIES (a.k.a - a clickable box with a string in it)
	/// @author Alex Vincent 
	///////////////////////////////////////////////////////////////////////
	class ContextBuilder {
	private:

		WindowInterface* containingWindow;
		ppc::InputHandler* inputHandle;

		/* List Element Label (String) */
		sf::Font labelFont;
		std::string label;
		int labelSize;
		int labelX;
		int labelY;

		int boxX;
		int boxY;
		int boxWidth;
		int boxHeight;
		

	public:
		///////////////////////////////////////////////////////////////////////
		/// @brief Constructor for buttonRenderComponent
		/// @details Creates a default button
		///////////////////////////////////////////////////////////////////////
		ContextBuilder();

		~ContextBuilder();

		///////////////////////////////////////////////////////////////////////
		/// @brief Set a custom string label to display on the list element box
		/// @param The string to be labeled onto list element
		///////////////////////////////////////////////////////////////////////
		void setLabelMessage(std::string l);

		///////////////////////////////////////////////////////////////////////
		/// @brief Set a custom font to display on the list element
		/// @param The font of the custom label
		///////////////////////////////////////////////////////////////////////
		void setLabelFont(sf::Font);

		///////////////////////////////////////////////////////////////////////
		/// @brief Set the label size to display on the list element box
		/// @param The character size of the label
		///////////////////////////////////////////////////////////////////////
		void setLabelSize(int);

		///////////////////////////////////////////////////////////////////////
		/// @brief Set the label position to display on the list element box
		/// @param A vector of the x,y position of the label
		///////////////////////////////////////////////////////////////////////
		void setLabelPosition(sf::Vector2f pos);

		///////////////////////////////////////////////////////////////////////
		/// @brief Set the position of the button
		/// @param X position of the button
		/// @param Y position of the button
		///////////////////////////////////////////////////////////////////////
		void setListElementPosition(float x, float y);

		///////////////////////////////////////////////////////////////////////
		/// @brief Set the position of the list element
		/// @param Vector containing the x and y position of the list element
		///////////////////////////////////////////////////////////////////////
		void setListElementPosition(sf::Vector2f pos);

		///////////////////////////////////////////////////////////////////////
		/// @brief Set the size of the list element
		/// @param Vector containing the width and height of the list element
		///////////////////////////////////////////////////////////////////////
		void setListElementSize(sf::Vector2f pos);

		///////////////////////////////////////////////////////////////////////
		/// @brief Set the input handle of the list element
		/// @param The window's input handler
		///////////////////////////////////////////////////////////////////////
		void setInputHandle(ppc::InputHandler&);

		///////////////////////////////////////////////////////////////////////
		/// @brief Set the context menu's surrounding box (a.k.a window)
		/// @param A pointer to the window used to spawn the context menu
		/// @note This is required because the bounds of any context list element
		/// depends on the size of the window. Its width is that of the entire
		/// context menu.
		///////////////////////////////////////////////////////////////////////
		void setContainingWindow(ppc::WindowInterface*);


		///////////////////////////////////////////////////////////////////////
		/// @brief Returns the constructed context list element
		/// @param The entity to modify
		///////////////////////////////////////////////////////////////////////
		void create(Entity&);
	};

	///////////////////////////////////////////////////////////////////////
	/// @brief Returns the constructed list element, with an attached 
	/// function observer.
	/// @param The entity to modify
	/// @param The target class object
	/// @param The function to execute on a click
	///////////////////////////////////////////////////////////////////////
	template<class T>
	void createWithEventFunc(ContextBuilder& builder, Entity& e, T* target, bool(*func)(T *, ppc::Event)) {

		builder.create(e);
		size_t s = e.cmpntCount();
		ppc::mousePressButton* mpb = dynamic_cast<mousePressButton*>(e.getComponent(s - 1));

		if (mpb != nullptr) {
			setOnPress(mpb, target, func);
		}
		else {
			return;
		}
	}


};