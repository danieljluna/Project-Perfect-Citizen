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
		unsigned int sequence;
		unsigned int frame;
		
		int currentSequenceIndex = 0;

		
	public:

		FloppyInputComponent();
		~FloppyInputComponent();

		static std::vector<std::vector<std::pair<std::string, unsigned int>>> floppyDictionary;

		unsigned int getFrame();
		unsigned int getSequence();

		void setFrame(unsigned int);
		void setSequence(unsigned int);
	
		void initializeFloppyDict();
		void advanceFrame();
		void regressFrame();
		void advanceSequence();
		void regressSequence();

	};

	////////////////////////////////////////////////////////////////
	/// Accepts a FloppyType event that contains a sequence/frame
	/// Creates an event with the new sequence, frame
	/// Sends that event to the entity
	///////////////////////////////////////////////////////////////
	bool summonFloppyDialog(FloppyInputComponent*, ppc::Event);
 
	////////////////////////////////////////////////////////////////
	/// Accepts a ButtonType event 
	/// Increments the saved state frame
	/// Creates an event with the new frame
	/// Sends that event to the entity
	///////////////////////////////////////////////////////////////
	bool incrementFloppyDialog(FloppyInputComponent*, ppc::Event);


};
