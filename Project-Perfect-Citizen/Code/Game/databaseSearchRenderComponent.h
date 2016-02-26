#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../Engine/renderComponent.h"
#include <string>

using namespace std;

///////////////////////////////////////////////////////////////////////
/// @brief Designated Render Component for the database search box
/// @author Alex Vincent
/// @details TO-DO
///////////////////////////////////////////////////////////////////////
class databaseSearchRenderComponent : public ppc::RenderComponent {
private:
	sf::Sprite* sprite;
	sf::Text* text;
	sf::Font font;
	string str;
	static const int size = 128;

public:

	databaseSearchRenderComponent(sf::Font& f, int x, int y, int size);

	~databaseSearchRenderComponent();

	////////////////////////////////////////////////////////////////////
	/// @brief updateString recieves a string from an input component to
	///        display.
	/// @param s is the string recieved from the input component
	////////////////////////////////////////////////////////////////////
	void updateString(string s);

	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

	virtual void recieveMessage(msgType code) override;

};