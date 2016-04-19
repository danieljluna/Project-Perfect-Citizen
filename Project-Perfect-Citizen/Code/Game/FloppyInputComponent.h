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
		//FloppyRenderComponent floppyRender; 
		//TextBubbleRenderComponent tbr;
		//TextBubbleInputComponent tbi;
		
		
	public:

		FloppyInputComponent();
		~FloppyInputComponent();

		enum EventTypes
		{
			ButtonType,
			TransformationType,
			ScrollbarType,
			sfEventType,
			FloppyType,
			EmotionType,
			Count
		};

		struct Emotions {
			bool isDefault;
			bool isAngry;
			bool isSurprised;
			bool isPeeked;
			bool isHidden;
		};

		void recieveEvent(ppc::Event);
		void updateFloppyEmotion();
		void updateTextBoxString();
		//std::vector<std::pair<std::string, ppc::Emotion>> currentSequence;
		
	};


};
