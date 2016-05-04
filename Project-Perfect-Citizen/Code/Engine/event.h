#pragma once
//Programmed by Andy
#include <SFML/Graphics.hpp>

namespace ppc {

    class Network;
    class WindowInterface;
<<<<<<< HEAD
	class FloppyInputComponent;
=======
    class NodeState;
>>>>>>> refs/remotes/origin/experimental

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

        struct NotificationEv {
            unsigned int count;
        };

		struct FloppyEv {
			unsigned int sequence;
			//FloppyInputComponent::FloppySequenceName seqname;
			unsigned int frame;
		};

		struct AbleEv {
			bool enable;
		};

		enum EventTypes
		{
			ButtonType,
			OpenType,
			ScrollbarType,
			sfEventType,
            NotificationType,
			FloppyType,
			AbleType,
            NetworkType,
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

            union {
                WindowInterface* window;
                NodeState* nodeState;
            };
			OpenTypes winType;
		};

        struct NetworkEv {
            enum NetworkEvType {
                Selected = 0,
                Created,
                Edited,
                Removed,
                Center,
                Count
            };

            NetworkEvType type;

            Network* net;

            size_t u;
            size_t v;
        };

		EventTypes type;

		union {
			ButtonsEv buttons;
			OpenEv open;
            NotificationEv notification;
			FloppyEv floppy;
			AbleEv able;
            NetworkEv network;
            sf::Event sfEvent;
		};
	};
} //end of ppc namespace
