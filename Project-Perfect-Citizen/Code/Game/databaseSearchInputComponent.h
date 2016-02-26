#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "../Engine/inputComponent.h"
#include "../Engine/InputHandler.h"
#include "../Engine/Entity.h"
#include "../Engine/subject.h"
#include "textInputRenderComponent.hpp"
#include "consoleUpdateComponent.h"
#include "textOutputRenderComponent.h"
#include "PipelineCharacter.h"
#include "databaseSearchRenderComponent.h"
#include "databaseDisplayRenderComponent.h"
#include <stack>


///////////////////////////////////////////////////////////////////////
/// @brief Designated Input Component for a generic window 'X' button
/// @author Michael Lowe
/// @details Input Component to handle TextEnter events from
///          the keyboard. This will mainly be used in combination
///          with a text input box render component.
///////////////////////////////////////////////////////////////////////

class databaseSearchInputComponent : public ppc::InputComponent {
private:

	sf::Sprite& textBoxSprt;
	databaseSearchRenderComponent& textBox;
	databaseDisplayRenderComponent& textDisplay;
	ppc::InputHandler& inputHandle;
	//std::stack<Database&> searchHistory;
	sf::Clock mouseClock;
	std::string str;
	float mouseTime;
	bool isCollision(sf::Vector2i);

public:

	databaseSearchInputComponent() = delete;

	///////////////////////////////////////////////////////////////////////
	/// @brief Constructor for databaseSearchInputComponent
	/// @param ih is the input handler
	/// @param s is the render component where the text will be drawn
	///////////////////////////////////////////////////////////////////////
	databaseSearchInputComponent(ppc::InputHandler& ih, databaseSearchRenderComponent& t,
		databaseDisplayRenderComponent& d, sf::Sprite& s);
	virtual ~databaseSearchInputComponent();
	virtual bool registerInput(sf::Event& ev) override;

};