#pragma once

#include "../Engine/debug.h"
#include "iconInputComponent.h"
#include <iostream>


///////////////////////////////////////////////////////////////////////
/// @brief Designated input component for explorer folders
/// @author Alex Vincent 
/// @details Functionality: when clicked, finds it's position in the
/// filetree and calls a new command on the nodestate
///////////////////////////////////////////////////////////////////////

namespace ppc {

	class explorerFolderInputComponent : public ppc::InputComponent {

	private:

		NodeState& theFileTree_;
		//Explorer& theExplorer_;
		sf::FloatRect buttonRect;
		std::string directoryName;
		sf::Clock mouseClock;
		sf::Int32 mouseTime;
		bool isCollision(sf::Vector2i);

		Subject onPress_;
		Subject onDoublePress_;
		Subject onRelease_;

	public:

		explorerFolderInputComponent() = delete;
		///////////////////////////////////////////////////////////////////////
		///@brief Ctor
		///////////////////////////////////////////////////////////////////////
		explorerFolderInputComponent(ppc::InputHandler& ih, NodeState& ns, sf::FloatRect rect, std::string directoryName);

		///////////////////////////////////////////////////////////////////////
		///@brief Removes all the current observers in the observerArray_
		///////////////////////////////////////////////////////////////////////
		void clearObservers();

		template <class T>
		friend void setOnPress(explorerFolderInputComponent* mpb,
			T* objPtr,
			bool(*onPress)(T*, sf::Event&));

		///////////////////////////////////////////////////////////////////////
		//SETTERS
		///////////////////////////////////////////////////////////////////////

		///////////////////////////////////////////////////////////////////////
		///@brief Adds the input handler to the component. Also sets up the
		/// neccessary subject and observers for this component.
		///////////////////////////////////////////////////////////////////////
		void setInputHandle(ppc::InputHandler& ih);

		///////////////////////////////////////////////////////////////////////
		///@breif Sets the FloatRect of the sprite associated with this cmpnt.
		///@details Must pass in the globad bounds of the sprite.
		///////////////////////////////////////////////////////////////////////
		void setFloatRect(sf::FloatRect rect);

		virtual ~explorerFolderInputComponent();
		virtual bool registerInput(sf::Event& ev) override;


		Subject& onClick() { return onPress_; };
		Subject& onDblClick() { return onDoublePress_; };
		Subject& onRelease() { return onRelease_; };

	};

	template<class T>
	inline void setOnPress(explorerFolderInputComponent* eFIC, T * objPtr, bool(*onPress)(T *, sf::Event &)) {

		FreeFunctionObserver<T>* fnObsvr = new FreeFunctionObserver<T>(onPress, objPtr);

		eFIC->onRelease().addObserver(fnObsvr);

	}

};
