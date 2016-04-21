#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include <vector>
#include "../Engine/inputComponent.h"
#include "../Engine/event.h"


///////////////////////////////////////////////////////////////////////
/// @brief Designated Input Component for a Floppy
/// @author Alex Vincent
/// @details This component recieves a FloppyEvent and tells
/// floppy render component and the text box what to display.
///////////////////////////////////////////////////////////////////////

namespace ppc {


	class FloppyInputComponent : public ppc::InputComponent {
	private:
		unsigned int sequence;
		unsigned int frame;
	
	public:

		FloppyInputComponent();
		virtual ~FloppyInputComponent();

		static std::vector<std::vector<std::pair<std::string, unsigned int>>> floppyDictionary;

		///////////////////////////////////////////////////////////////////////
		/// Map of Floppy Sequence names to integers
		///////////////////////////////////////////////////////////////////////
		static std::map<std::string, unsigned int> Floppy_Sequence_Names;
		    /*{"Welcome", 0},
			{"Connections", 1},
			{"Edges", 2},
			{"Goal", 3},
			{"Suspicion", 4},
			{"Center", 5},
			{"Feedback", 6}*/

		///////////////////////////////////////////////////////////////////////
		/// Basic Getters
		///////////////////////////////////////////////////////////////////////
		unsigned int getFrame();
		unsigned int getSequence();

		///////////////////////////////////////////////////////////////////////
		/// Basic Setters
		///////////////////////////////////////////////////////////////////////
		void setFrame(unsigned int);
		void setSequence(unsigned int);
	
		///////////////////////////////////////////////////////////////////////
		/// @brief Initializes the table of what Floppy says and how he emotes
		///////////////////////////////////////////////////////////////////////
		void initializeFloppyDict();

		///////////////////////////////////////////////////////////////////////
		/// Basic incrementers and decrementers (by one)
		///////////////////////////////////////////////////////////////////////
		void advanceFrame();
		void regressFrame();
		void advanceSequence();
		void regressSequence();
        
        virtual bool registerInput(sf::Event ev) override;




	};

	////////////////////////////////////////////////////////////////
	/// @brief Accepts a generic floppy type, saves the frame and
	/// sequence for future use, and then passes that event to
	/// the entity
	/// @param Pointer to Floppy's input component
	/// @param A FloppyType'd event with a set frame and sequence
	////////////////////////////////////////////////////////////////
	bool summonFloppyDialog(FloppyInputComponent*, ppc::Event);
 
	////////////////////////////////////////////////////////////////
	/// @brief Accepts a generic button type, increments the saved frame
	/// and sends a new event to the entity
	////////////////////////////////////////////////////////////////
	bool incrementFloppyDialog(FloppyInputComponent*, ppc::Event);


};
