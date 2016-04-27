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
			bool isLeft;
			bool isRight;
			float mouseX;
			float mouseY;
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
                openConsole = 0,
                openHelp,
                openEmail,
                openPipeline,
                openSearch,
                openBrowser,
                openChat,
                openSettings,
                openFolder,
                openHarddrive
            };

			OpenTypes window;
		};

		EventTypes type;

		union {
			ButtonsEv buttons;
			OpenEv open;
			TransformationEv transformations;
			ScrollbarEv scrollbar;
            NotificationEv notification;
			FloppyEv floppy;
			AbleEv able;
            sf::Event sfEvent;
		};
	};
} //end of ppc namespace
