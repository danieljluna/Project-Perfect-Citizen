#pragma once
//Programmed by Andy

#include <SFML/Graphics.hpp>

namespace ppc {

    class Network;
    class WindowInterface;
    class BaseFileType;

	//This is the event struct. You can add events here
	//if you need them. Nothing here is final except
	//the template. 

	class Event
	{
	public:
        Event();
        Event(sf::Event ev);

        operator sf::Event&();


        enum EventTypes
        {
            ButtonType,
            OpenType,
            sfEventType,
            NotificationType,
            FloppyType,
            AbleType,
            NetworkType,
            SubmissionType,
            AnimationType,
            TimerType,
            Count
        };

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
			unsigned int frame;
		};

		struct AbleEv {
			bool enable;
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
                BaseFileType* file;
            };
			OpenTypes winType;
            bool success;
		};

        struct NetworkEv {
            enum NetworkEvType {
                Selected = 0,
                Created,
                Edited,
                Removed,
                Center,
                Submit,
                Count
            };

            NetworkEvType type;

            Network* net;

            size_t u;
            size_t v;
        };

        struct TimerEv {
            enum timerState {
                Reset = 0,
                FastForward,
                Play,
                Pause,
                Rewind,
                Finished
            };

            int timerIndex;
            sf::Time time;
            timerState action;
            
        };

        struct SubmissionEv {
            enum SubmissionType {
                Mark = 0,
                Unmark,
                Scan,
                Submit
            };

            SubmissionType type;
            union {
                BaseFileType* file;
                unsigned int count;
            };
        };

        struct AnimationEv {
            size_t index;
        };

		EventTypes type;

		union {
			ButtonsEv buttons;
			OpenEv open;
            NotificationEv notification;
			FloppyEv floppy;
			AbleEv able;
            NetworkEv network;
            SubmissionEv submission;
            AnimationEv animation;
            TimerEv timer;
            sf::Event sfEvent;
		};


        bool operator==(const ppc::Event& other) const;

	};
} //end of ppc namespace
