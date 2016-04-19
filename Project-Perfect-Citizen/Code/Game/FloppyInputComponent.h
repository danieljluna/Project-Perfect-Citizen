#pragma once

#include <SFML/Graphics.hpp>
#include <array>

#include "../Engine/inputComponent.h"
#include "../Engine/InputHandler.h"
#include "../Engine/Entity.h"
#include "../Engine/subject.h"
#include "../Engine/FunctionObserver.h"
#include "../Engine/FreeFunctionObserver.h"
#include "../Engine/debug.h"

///////////////////////////////////////////////////////////////////////
/// @brief Designated Input Component for a Floppy
/// @author Alex Vincent & Michael Lowe
/// @details This component recieved a queue event and tells
/// floppy render component and the text box what to display.
///////////////////////////////////////////////////////////////////////


namespace ppc {


	class FloppyInputComponent : public ppc::InputComponent {
	private:

		int currentSequenceIndex = 0;
		std::vector<std::pair<std::string, Event::FloppyEmotions>> currentSequence;
		
	public:

		FloppyInputComponent();
		~FloppyInputComponent();

		void recieveEvent(ppc::Event);
		void updateFloppyEmotion(sf::Event);
		void updateTextBoxString(sf::Event);
		void advanceSequence(sf::Event);
		void regressSequence(sf::Event);

	};


};
