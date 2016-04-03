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
		sf::Event sfEvent;

		struct Buttons {
			bool isPushed;
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
			Count
		};

		EventTypes type;

		union {
			Buttons buttons;
			Transformations transformations;
			Scrollbar scrollbar;
		};
	};
} //end of ppc namespace
