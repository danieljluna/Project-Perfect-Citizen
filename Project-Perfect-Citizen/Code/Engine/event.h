#pragma once
//Programmed by Andy
#include <SFML/Graphics.hpp>

#include "EmailUpdateEvent.h"

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
		};

		struct Transformations {
			sf::Vector2f newPos;
		};

		struct Scrollbar {
			float start;
			float end;
		};

		enum EventTypes
		{
			ButtonType,
			TransformationType,
			ScrollbarType,
			sfEventType,
            EmailUpdateType,
			Count
		};

		EventTypes type;

		union {
			Buttons buttons;
			Transformations transformations;
			Scrollbar scrollbar;
            EmailUpdate emailUpdate;
            sf::Event sfEvent;
		};
	};
} //end of ppc namespace
