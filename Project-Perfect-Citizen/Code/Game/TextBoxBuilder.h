#pragma once

#include <string>

#include <SFML/Graphics/Font.hpp>

#include "TextBoxInputComponent.h" //needed
#include "Entity.h"


namespace ppc {
	class InputHandler;

	///////////////////////////////////////////////////////////////////////
	/// @brief Designated Generic Builder Object for non-editable Text Output Fields
	/// @author Alex Vincent 
	/// @details A package with API function calls allowing for individual
	/// creations and augmentations of an editable ext field. This augments 
	/// and returns an entity.
	///////////////////////////////////////////////////////////////////////
	class TextBoxBuilder {
	private:
		sf::Font* f;
		sf::Color* c;
		float xPos;
		float yPos;
		int s;
		std::string stringToRender;
		InputHandler* ih;
		TextBoxInputComponent* tbi;
		WindowInterface* cw;
		int lim = 15;
		bool mask = false;


	public:
		///////////////////////////////////////////////////////////////////////
		/// @brief Constructor for an editable text box to the screen
		/// @details Creates a default text box
		///////////////////////////////////////////////////////////////////////
		TextBoxBuilder();

		~TextBoxBuilder();

		void setFont(sf::Font& font);

		void setColor(sf::Color color);

		void setPosition(sf::Vector2f vec);

		void setSize(int size);

		void setString(std::string str);

		void setInputHandle(ppc::InputHandler&);

		void setContainingWindow(WindowInterface*);

		void setTextBoxCharacterLimit(int l);

		void setIsMasked(bool);

		TextBoxInputComponent* getTextBoxInputComponent();

		void create(Entity&);

	};

	///////////////////////////////////////////////////////////////////////
	/// @brief Returns the constructed textbox, with an attached function
	/// observer.
	/// @param The builder being used to make the textbox
	/// @param The entity to modify
	/// @param The target class object
	/// @param The function to execute on a click
	///////////////////////////////////////////////////////////////////////
	template<class T>
	void createWithEventFunc(TextBoxBuilder& builder, Entity& e, T* target, bool(*func)(T *, ppc::Event)) {

		builder.create(e);
		size_t s = e.cmpntCount();
		TextBoxInputComponent* tbi = dynamic_cast<TextBoxInputComponent*>(e.getComponent(s - 1));

		if (tbi != nullptr) {
			setOnSubmit(tbi, target, func);
		}
		else {
			return;
		}
	}


};