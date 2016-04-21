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
        Event();
        Event(sf::Event ev);

        operator sf::Event&();

		struct ButtonsEv {
			bool isPushed;
			bool isReleased;
			bool isHovered;
		};

		struct TransformationEv {
			sf::Vector2f newPos;
		};

		struct ScrollbarEv {
			float start;
			float end;
		};

        struct NotificationEv {
            unsigned int count;
        };

		struct FloppyEv {
			unsigned int sequence;
			unsigned int frame;
		};

		enum EventTypes
		{
			ButtonType,
			TransformationType,
			ScrollbarType,
			sfEventType,
            NotificationType,
			FloppyType,
			Count
		};

		EventTypes type;

		union {
			ButtonsEv buttons;
			TransformationEv transformations;
			ScrollbarEv scrollbar;
            NotificationEv notification;
			FloppyEv floppy;
            sf::Event sfEvent;
		};
	};
} //end of ppc namespace
