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

		static std::vector<std::vector<std::pair<std::string, unsigned int>>> floppyDictionary;

		struct currentEvent {
			unsigned int sequence;
			unsigned int frame;
		};
		
		int currentSequenceIndex = 0;

		
	public:

		FloppyInputComponent();
		~FloppyInputComponent();

		
		//void setSequenceAndFrame(unsigned int seq, unsigned int frame);
		//void setSequenceAndFrame(unsigned)
		void advanceSequence(sf::Event);
		void regressSequence(sf::Event);

	};


};
