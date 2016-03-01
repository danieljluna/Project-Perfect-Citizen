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
	std::stack<Database*> searchHistory;
	std::vector<std::string> displayResults_;
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
	databaseSearchInputComponent(Database* iDB, ppc::InputHandler& ih, databaseSearchRenderComponent& t,
		databaseDisplayRenderComponent& d, sf::Sprite& s);

	///////////////////////////////////////////////////////////////////////
	/// @brief Updates the display output in the database
	/// @param A vector containing the strings of the new output
	///////////////////////////////////////////////////////////////////////
	void updateDisplayOutput(std::vector<std::string> newOut);

	///////////////////////////////////////////////////////////////////////
	/// @brief Clears the existing string of the database search input
	///////////////////////////////////////////////////////////////////////
	void clearSearchBox();

	///////////////////////////////////////////////////////////////////////
	/// @brief Function pointer to back functionality
	///////////////////////////////////////////////////////////////////////
	void(*goBack) ();

	///////////////////////////////////////////////////////////////////////
	/// @brief Sets the display results to be a hardcoded string
	/// @param Vector that will be interpreted and passed to main display
	/// @param hardcoded string to pass into
	///////////////////////////////////////////////////////////////////////
	void updateDisplayResults(std::vector<std::string> displayVec, std::string newDisplay);

	///////////////////////////////////////////////////////////////////////
	/// @brief Default ctor
	///////////////////////////////////////////////////////////////////////
	virtual ~databaseSearchInputComponent();

	///////////////////////////////////////////////////////////////////////
	/// @brief Inherited input component function
	///////////////////////////////////////////////////////////////////////
	virtual bool registerInput(sf::Event& ev) override;

};