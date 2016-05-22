#pragma once
#include <iostream>
#include <string>

//#include "iconInputComponent.h"


#include "../Engine/inputComponent.h"
#include "../Engine/NodeState.h"
#include "../Engine/subject.h"

//#include "TextBoxInputComponent.h"

namespace sf {
	class Image;
};


///////////////////////////////////////////////////////////////////////
/// @brief Designated input component for explorer folders
/// @author Alex Vincent 
/// @details Functionality: when clicked, finds it's position in the
/// filetree and calls a new command on the nodestate
///////////////////////////////////////////////////////////////////////

namespace ppc {
	class Desktop;
	class TextBoxInputComponent;

	class explorerFolderInputComponent : public ppc::InputComponent {

	private:

		WindowInterface* containingWindow_;
		NodeState theFileTree_;
		Desktop& theDesktop_;
		TextBoxInputComponent* observingTextBox_;
		sf::Image& buttonSheet_;
		sf::Image& iconSheet_;
		sf::FloatRect buttonRect;
		std::string directoryName;
		sf::Clock mouseClock;
		sf::Int32 mouseTime;
		bool isCollision(sf::Vector2i);
		bool hasBeenClicked;

		Subject onPress_;
		Subject onDoublePress_;
		Subject onRelease_;

	public:

		explorerFolderInputComponent() = delete;
		///////////////////////////////////////////////////////////////////////
		///@brief Ctor
		///////////////////////////////////////////////////////////////////////
		explorerFolderInputComponent(Desktop& dt, WindowInterface* cW, ppc::InputHandler& ih, NodeState& ns, sf::Image& bS, sf::Image& iS, sf::FloatRect rect, std::string directoryName);

		///////////////////////////////////////////////////////////////////////
		///@brief Removes all the current observers in the observerArray_
		///////////////////////////////////////////////////////////////////////
		void clearObservers();

		template <class T>
		friend void setOnPress(explorerFolderInputComponent* mpb,
			T* objPtr,
			bool(*onPress)(T*, Event));

		///////////////////////////////////////////////////////////////////////
		//SETTERS
		///////////////////////////////////////////////////////////////////////

		///////////////////////////////////////////////////////////////////////
		///@brief Adds the input handler to the component. Also sets up the
		/// neccessary subject and observers for this component.
		///////////////////////////////////////////////////////////////////////
		void setInputHandle(ppc::InputHandler& ih);

		///////////////////////////////////////////////////////////////////////
		///@brief Sets the FloatRect of the sprite associated with this cmpnt.
		///@details Must pass in the globad bounds of the sprite.
		///////////////////////////////////////////////////////////////////////
		void setFloatRect(sf::FloatRect rect);

		///////////////////////////////////////////////////////////////////////
		///@brief Set the TextBoxInputComponent in case it needs to get the 
		/// string from a text box to compare to this folder's password.
		///@note This should only be used when creating an unlock message prompt
		/// May be changed later, but now the only work around to getting
		/// the unlock prompt menu to work.
		///////////////////////////////////////////////////////////////////////
		void setObservingTextBox(TextBoxInputComponent*);

		///////////////////////////////////////////////////////////////////////
		///@brief Gets the stored observing text box input component
		///@note Only call this if setObservingTextBox was called with a valid
		/// TextBoxInputComponent.
		///////////////////////////////////////////////////////////////////////
		TextBoxInputComponent* getObservingTextBox();


		///////////////////////////////////////////////////////////////////////
		///@brief Gets the stored node state in the file tree for this folder
		///////////////////////////////////////////////////////////////////////
		NodeState* getFolderNodeState();

		///////////////////////////////////////////////////////////////////////
		///@brief Gets the stored name of this folder
		///////////////////////////////////////////////////////////////////////
		std::string getFolderName();

		///////////////////////////////////////////////////////////////////////
		///@brief Gets the stored node state in the file tree for this folder
		///////////////////////////////////////////////////////////////////////
		Desktop* getFolderDesktop();

		virtual ~explorerFolderInputComponent();
		virtual bool registerInput(Event ev) override;

		///////////////////////////////////////////////////////////////////////
		///@brief Moves into the directory, updating the new sprites.
		///@param Whether the change should make a new window or just close/re-
		/// construct the existing. Set to true for a new window to spawn,
		/// set to false for the current window to be overwritten.
		///////////////////////////////////////////////////////////////////////
		void changeDirectory(bool newWindow);


		Subject& onClick() { return onPress_; };
		Subject& onDblClick() { return onDoublePress_; };
		Subject& onRelease() { return onRelease_; };

	};

	template<class T>
	inline void setOnPress(explorerFolderInputComponent* eFIC, T * objPtr, bool(*onPress)(T *, sf::Event &)) {

		FreeFunctionObserver<T>* fnObsvr = new FreeFunctionObserver<T>(onPress, objPtr);

		eFIC->onRelease().addObserver(fnObsvr);

	}

	bool open_folder(explorerFolderInputComponent*, ppc::Event);
	bool open_folder_in_new_window(explorerFolderInputComponent*, ppc::Event);
	bool flag_folder(explorerFolderInputComponent*, ppc::Event);
	bool unlock_folder(explorerFolderInputComponent*, ppc::Event);

};
