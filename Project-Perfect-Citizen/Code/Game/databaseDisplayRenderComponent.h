#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../Engine/renderComponent.h"
#include "../Game/Database.h"
#include <string>
#include <stack>
#include "characterRender.hpp"

using namespace std;

///////////////////////////////////////////////////////////////////////
/// @brief Designated Render Component for an Text Output Box
/// @author Michael Lowe / Alex Vincent
/// @details write this later
///////////////////////////////////////////////////////////////////////
class databaseDisplayRenderComponent : public ppc::RenderComponent {
private:

	////////////////////////////////////////////////////////////////////
	/// @brief Character Render used to process and display character
	//					profile.
	////////////////////////////////////////////////////////////////////
    characterRender* render;
    
    
	////////////////////////////////////////////////////////////////////
	/// @brief Sprite to be rendered
	////////////////////////////////////////////////////////////////////
	sf::Sprite* sprite_;

	////////////////////////////////////////////////////////////////////
	/// @brief SFML text to draw
	////////////////////////////////////////////////////////////////////
	sf::Text* text_;

	////////////////////////////////////////////////////////////////////
	/// @brief Font the output will take on
	////////////////////////////////////////////////////////////////////
	sf::Font font_;

	////////////////////////////////////////////////////////////////////
	/// @brief Stack of all database snapshots
	////////////////////////////////////////////////////////////////////
	//std::stack<Database&> theDatabase_;

	////////////////////////////////////////////////////////////////////
	/// @brief The pool of output to be displayed via a string
	////////////////////////////////////////////////////////////////////
	string str_;
	static const int size = 128;

public:

    databaseDisplayRenderComponent(sf::Font& f, sf::Image& faceSheet, int x, int y, int size);

	~databaseDisplayRenderComponent();

	////////////////////////////////////////////////////////////////////
	/// @brief updateString recieves a string from an input component to
	///        display.
	/// @param s is the string recieved from the input component
	////////////////////////////////////////////////////////////////////
	void updateString(std::vector<string> cmd);

	////////////////////////////////////////////////////////////////////
	/// @brief clearString deletes the contents of a string
	/// @param s is the string recieved from the input component
	////////////////////////////////////////////////////////////////////
	void clearString();

	virtual void draw(sf::RenderTarget & target,
		sf::RenderStates states) const;

	//virtual void registerInput(Event ev) override;
	virtual void recieveMessage(msgType code) override;

};