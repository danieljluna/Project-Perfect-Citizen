#pragma once

#include "../Engine/debug.h"
#include "iconInputComponent.h"
#include <iostream>

namespace ppc {


    ///////////////////////////////////////////////////////////////////////
    /// @brief Designated input component for explorer files
    /// @author Alex Vincent 
    /// @details Functionality: when clicked opens the corresponding file 
    ///////////////////////////////////////////////////////////////////////
	class explorerFileInputComponent : public ppc::InputComponent {

	private:

		Desktop& theDesktop_;
		NodeState theFileTree_;
		sf::FloatRect buttonRect;
		sf::Image& buttonSheet_;
		std::string fileName;
		sf::Clock mouseClock;
		sf::Int32 mouseTime;
		bool isCollision(sf::Vector2i);

		Subject onPress_;
		Subject onDoublePress_;
		Subject onRelease_;

	public:

		explorerFileInputComponent() = delete;
		///////////////////////////////////////////////////////////////////////
		///@brief Ctor
		///////////////////////////////////////////////////////////////////////
		explorerFileInputComponent(Desktop& dt, ppc::InputHandler& ih, NodeState& ns, sf::Image& bS, sf::FloatRect rect, std::string directoryName);

		///////////////////////////////////////////////////////////////////////
		///@brief Removes all the current observers in the observerArray_
		///////////////////////////////////////////////////////////////////////
		void clearObservers();

		template <class T>
		friend void setOnPress(explorerFileInputComponent* mpb,
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
		///@breif Sets the FloatRect of the sprite associated with this cmpnt.
		///@details Must pass in the globad bounds of the sprite.
		///////////////////////////////////////////////////////////////////////
		void setFloatRect(sf::FloatRect rect);

		virtual ~explorerFileInputComponent();
		virtual bool registerInput(sf::Event ev) override;


		Subject& onClick() { return onPress_; };
		Subject& onDblClick() { return onDoublePress_; };
		Subject& onRelease() { return onRelease_; };

	};

	template<class T>
	inline void setOnPress(explorerFileInputComponent* eFIC, T * objPtr, bool(*onPress)(T *, sf::Event &)) {

		FreeFunctionObserver<T>* fnObsvr = new FreeFunctionObserver<T>(onPress, objPtr);

		eFIC->onRelease().addObserver(fnObsvr);

	}

};