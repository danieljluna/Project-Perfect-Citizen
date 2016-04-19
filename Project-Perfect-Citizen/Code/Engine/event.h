#pragma once
//Programmed by Andy
#include <SFML/Graphics.hpp>

namespace ppc {
	//This is the event struct. You can add events here
	//if you need them. Nothing here is final except
	//the template. 

	class Event
	{
	public:
        Event(sf::Event ev);

        operator sf::Event&();

		struct Buttons {
			bool isPushed;
			bool isReleased;
			bool isHovered;
		};

		struct Transformations {
			sf::Vector2f newPos;
		};

		struct Scrollbar {
			float start;
			float end;
		};

		struct Message {
			std::string msg;
		};

		struct FloppyEmotions {
			bool isDefault;
			bool isAngry;
			bool isSurprised;
			bool isPeeked;
		};

		struct FloppyInput {
			std::vector<std::pair<std::string, Event::FloppyEmotions>> input;
			~FloppyInput() {}
		};

		enum EventTypes
		{
			ButtonType,
			TransformationType,
			ScrollbarType,
			sfEventType,
			MessageType,
			FloppyType,
			EmotionType,
			Count
		};

		EventTypes type;

		union {
			Buttons buttons;
			Transformations transformations;
			Scrollbar scrollbar;
			//Message message;
			//FloppyInput floppyinput;
			FloppyEmotions emotions;
            sf::Event sfEvent;
		};
	};
} //end of ppc namespace
