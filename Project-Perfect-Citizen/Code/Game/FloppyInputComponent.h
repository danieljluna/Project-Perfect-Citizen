#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include <vector>
#include "../Engine/subject.h"
#include "../Engine/inputComponent.h"
#include "../Engine/event.h"
#include "../Game/buttonRenderComponent.h"
#include "../Game/mousePressButton.h"


///////////////////////////////////////////////////////////////////////
/// @brief Designated Input Component for a Floppy
/// @author Alex Vincent
/// @details This component recieves a FloppyEvent and tells
/// floppy render component and the text box what to display.
///////////////////////////////////////////////////////////////////////

namespace ppc {

	struct FloppyExpression;
	class FloppyInputComponent : public ppc::InputComponent {
	private:
		unsigned int sequence;
		unsigned int frame;
		Subject onSequenceEnd_;

		buttonRenderComponent* floppyBtnRndr = nullptr;
		mousePressButton* floppyBtnInpt = nullptr;
	
	public:

		FloppyInputComponent();
		virtual ~FloppyInputComponent();

		

		static std::vector<std::vector<FloppyExpression>> floppyDictionary;

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

        static bool initialized;
		
		///////////////////////////////////////////////////////////////////////
		/// Basic Getters
		///////////////////////////////////////////////////////////////////////
		unsigned int getFrame();
		unsigned int getSequence();

		///////////////////////////////////////////////////////////////////////
		/// Basic Setters
		///////////////////////////////////////////////////////////////////////
		void setFrame(unsigned int);
		void setSequence(unsigned int s, unsigned int f = 0);
	
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
        
        virtual bool registerInput(Event ev) override;

		Subject& onSequenceEnd() { return onSequenceEnd_; };

		void setFloppyButtonRenderCmpt(buttonRenderComponent*);
		void setFloppyButtonInputCmpt(mousePressButton*);

		void setFloppyButton(bool);

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

	struct FloppyExpression {
		std::string text;
		unsigned int emotion;
		bool createEnabled;
	};
};
