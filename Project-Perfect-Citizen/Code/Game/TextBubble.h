#pragma once

#include <SFML/Graphics.hpp>
#include <list>
#include <queue>
#include "../Engine/event.h"
#include "../Engine/Entity.h"
#include "../Game/ButtonBuilder.h"
#include "../Game/TextDisplayBuilder.h"

namespace ppc {

	class Window;
	class Entity;
	class TextDisplayRenderComponent;

	///////////////////////////////////////////////////////////////////
	///@brief Basic speech text bubble 
	///@author Nader Sleem
	///////////////////////////////////////////////////////////////////
	class TextBubble {

	private:
		
		std::queue<std::string, std::list<std::string>> textQueue_;

		ppc::Window* textBox_;

		std::string currString_;

		ppc::Entity bubbleButton_;

		ppc::ButtonBuilder buttonBuilder_;

		ppc::TextDisplayBuilder textBuilder_;

		ppc::TextDisplayRenderComponent* textDisplay_;

		void formatLine(std::string&);

	public:

		///////////////////////////////////////////////////////////////
		// Ctor
		///////////////////////////////////////////////////////////////
		TextBubble();

		///////////////////////////////////////////////////////////////
		// Dtor
		///////////////////////////////////////////////////////////////
		virtual ~TextBubble();

		///////////////////////////////////////////////////////////////
		///@brief Loads the dialogue text from a file
		///////////////////////////////////////////////////////////////
		bool loadText(std::string filename);

		///////////////////////////////////////////////////////////////
		///@brief Changes the displayed text to the next in the queue.
		///////////////////////////////////////////////////////////////
		void advanceText();

		/////////////////////////////////////////////////////////////
		///@brief Returns the Entity for the Text Bubble button.
		/////////////////////////////////////////////////////////////
		ppc::Entity& getButtonEntity();

		/////////////////////////////////////////////////////////////
		///@brief Returns the Builder for the Text Bubble button.
		/////////////////////////////////////////////////////////////
		ppc::ButtonBuilder& getButtonBuilder();

		ppc::Window& getTextBox();

		/////////////////////////////////////////////////////////////
		///@brief Creates the Button for the TextBubble in the entity.
		///@details Should be called after setting up the parameters
		///for the builder in the TextBubble. Use getButtonBuilder
		/// to access this builder and call its functions.
		/// Function assumes that all the values for the builder
		/// have been properly set.
		/////////////////////////////////////////////////////////////
		void generateBubble();

	};

	///////////////////////////////////////////////////////////////
	///@brief Event function that progresses text.
	///@details Function should be associated with a observer
	/// so when a button is pressed, the dialogue text advances
	/// to the next one.
	///////////////////////////////////////////////////////////////
	bool advanceOnPress(TextBubble* tb, ppc::Event e);
	
};