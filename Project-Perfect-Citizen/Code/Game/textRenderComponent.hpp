#ifndef textRenderComponent_hpp
#define textRenderComponent_hpp

#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "../Engine/renderComponent.h"
#include <string>

namespace ppc {

///////////////////////////////////////////////////////////////////////
/// @brief Designated Render Component for a generic window 'X' button
/// @author Brandon Gomez
/// @details The textRenderComponent is a basic packaged subclass
///     extension of RenderComponent, make specifically to handle
///     all generic "X" button related drawing parts that
///     also broadcast and recieve messages from an input handler.
///		Stick this onto an entity to give it this functionality.
///////////////////////////////////////////////////////////////////////
class textRenderComponent : public ppc::RenderComponent {
private:
	sf::Sprite* sprite;
	sf::Text* text;
	sf::Font font;
	std::string str;
	static const int size = 128;

public:
	///////////////////////////////////////////////////////////////////////
	/// @brief Constructor for textRenderComponent
	/// @param image is the String of a file path of the text
	///////////////////////////////////////////////////////////////////////
	textRenderComponent(sf::Font& f, std::string text, int x, int y, int size);

	///////////////////////////////////////////////////////////////////////
	/// @brief default destructor for textRenderComponent
	///////////////////////////////////////////////////////////////////////
	~textRenderComponent();

	///////////////////////////////////////////////////////////////////////
	/// @brief The main draw function that was inheirted from RenderComponent.
	/// @details You need to define this to create a child of RenderComponent
	/// @param target: This is almost always going to be a sf::renderWindow. states:
	/// This is used to dictate certain states that the object can be rendered in.
	/// For now this can be safely "ignored" Just created a RenderStates object and
	/// shove it in there.
	///////////////////////////////////////////////////////////////////////
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
};

};

#endif /* textRenderComponent_hpp */
