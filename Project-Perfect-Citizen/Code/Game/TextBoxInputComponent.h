#pragma once

#include <string>

#include <SFML/Graphics.hpp>

#include "../Engine/inputComponent.h" //needed
#include "../Engine/subject.h" //needed
#include "../Engine/FreeFunctionObserver.h" //needed
#include "../Game/TimerUpdateCmpnt.h" //needed


namespace ppc {
	class InputHandler;
	class TextBoxRenderComponent;

	///////////////////////////////////////////////////////////////////////
	/// @brief Designated Input Component for a generic fillable text box
	/// @author Alex Vincent
	/// @details Input Component to handle TextEnter events from
	///          the keyboard. This will mainly be used in combination
	///          with a text box render component.
	///////////////////////////////////////////////////////////////////////
	
	class TextBoxInputComponent : public ppc::InputComponent {
	private:

		//sf::Sprite& textBoxSprt;
		WindowInterface* containingWindow;
		TextBoxRenderComponent& textBox;
		InputHandler& inputHandle;
		TimerUpdateCmpnt* tmr;
		std::string str;
		bool isCollision(sf::Vector2i);
		unsigned int max_chars;
		Subject onSubmit_;

	public:

		TextBoxInputComponent() = delete;

		///////////////////////////////////////////////////////////////////////
		/// @brief Constructor for TextBoxInputComponent
		/// @param ih is the input handler
		/// @param s is the render component where the text will be drawn
		/// @param The limit of characters to display
		///////////////////////////////////////////////////////////////////////
		TextBoxInputComponent(ppc::InputHandler& ih, TextBoxRenderComponent &r, TimerUpdateCmpnt* tmr, int lim);

		template <class T>
		friend void setOnSubmit(TextBoxInputComponent* tbi, T* objPtr,
			bool(*onSubmit)(T*, Event));


		std::string getString();

		void setLimit(int);

		WindowInterface* getContainingWindow();

		///////////////////////////////////////////////////////////////////////
		/// @brief Sets a pointer to the window this text box is currently in
		/// @param The window this textbox is inside
		///////////////////////////////////////////////////////////////////////
		void setContainingWindow(WindowInterface*);

		virtual ~TextBoxInputComponent();
		virtual bool registerInput(Event ev) override;
		virtual void recieveMessage(ppc::Event ev) override;

		Subject& onSubmit() { return onSubmit_; };

	};

	template<class T>
	inline void setOnSubmit(TextBoxInputComponent* tbi, T * objPtr, bool(*onSubmit)(T *, Event)) {

		FreeFunctionObserver<T>* fnObsvr = new FreeFunctionObserver<T>(onSubmit, objPtr);

		tbi->onSubmit().addObserver(fnObsvr);

	}


};