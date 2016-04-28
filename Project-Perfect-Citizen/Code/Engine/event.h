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

        //Used internally to recognize button state
		struct ButtonsEv {
            enum State {
                Hover = 0,
                Clicked,
                DblClicked,
                Release,
                Count
            };

            enum Activation {
                LeftMouse = 0,
                RightMouse,
                Enter
            };

            State state;
            Activation activation;
            sf::Vector2i mousePos;
		};

		struct TransformationEv {
			sf::Vector2f newPos;
		};

        struct NotificationEv {
            unsigned int count;
        };

		struct FloppyEv {
			unsigned int sequence;
			unsigned int frame;
		};

		struct AbleEv {
			bool enable;
		};

		enum EventTypes
		{
			ButtonType,
			OpenType,
			TransformationType,
			ScrollbarType,
			sfEventType,
            NotificationType,
			FloppyType,
			AbleType,
			Count
		};

		struct OpenEv {
            enum OpenTypes {
                Console = 0,
                Help,
                Email,
                Pipeline,
                Search,
                Browser,
                Chat,
                Settings,
                Folder,
                File,
                Explorer,
                HardDrive,
                Count
            };

			OpenTypes window;
		};

		EventTypes type;

		union {
			ButtonsEv buttons;
			OpenEv open;
			TransformationEv transformations;
            NotificationEv notification;
			FloppyEv floppy;
			AbleEv able;
            sf::Event sfEvent;
		};
	};
} //end of ppc namespace
