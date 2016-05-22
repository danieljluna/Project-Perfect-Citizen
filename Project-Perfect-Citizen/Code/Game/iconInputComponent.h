#pragma once

#include "../Engine/inputComponent.h" //needed

#include "../Engine/subject.h" //needed
#include "../Engine/Audio/AudioQueue.h" //needed


namespace sf {
	class Image;
};

namespace ppc {
	class InputHandler;
	class Desktop;
	class Database;
	class Inbox;
	class WindowInterface;

///////////////////////////////////////////////////////////////////////
/// @brief Designated non-mouse input handling for desktop icons
/// @author Alex Vincent 
/// @details Functionality: opens windows and places them on the desktop
/// by listening for double clicks from the mouse input
///////////////////////////////////////////////////////////////////////
class iconInputComponent : public InputComponent {
private:

	Desktop& theDesktop_;
	sf::Image& buttonSheet_;
	sf::Image& iconSheet_;
	Database* theDatabase_;
    Inbox& theInbox_;
	WindowInterface* openedWindow;
    AudioQueue que;
    Subject onOpen_;
	std::string labelName = "";
    
    Event::OpenEv::OpenTypes type_;

public:

    using IconType = Event::OpenEv::OpenTypes;

	iconInputComponent() = delete;

	//////////////////////////////////////////////////////////////////////
	/// @brief Constructor
	///
	///@param The newly created icon entity to add components to.
	///@param The buttonSheet of the window it will create's buttons.
	///////////////////////////////////////////////////////////////////////
	iconInputComponent(Desktop& theDesktop, Database* db, Inbox& ib, sf::Image& buttonSheet_, sf::Image& iconSheet_, IconType type = IconType::Count);

	
	virtual ~iconInputComponent();
	virtual bool registerInput(Event ev) override;
	virtual void recieveMessage(msgType message) override;
	virtual void recieveMessage(ppc::Event ev) override;

    Subject& onOpen() { return onOpen_; };

	void setIconLabelName(std::string);

    friend bool make_icon_window(iconInputComponent*, ppc::Event);

};
    bool make_icon_window(iconInputComponent*, ppc::Event);
};