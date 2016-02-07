#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "renderComponent.h"
#include <string>

using namespace std;

///////////////////////////////////////////////////////////////////////
/// @brief Designated Render Component for a generic window 'X' button
/// @author Alex Vincent
/// @details The buttonRenderComponent is a basic packaged subclass
///     extension of RenderComponent, make specifically to handle
///     all generic "X" button related drawing/animating parts that
///     also broadcast and recieve messages from an input handler.
///		Stick this onto an entity to give it this functionality.
///////////////////////////////////////////////////////////////////////
class buttonRenderComponent : public ppc::RenderComponent{
private:
	sf::Sprite* sprite;
	sf::Texture* texture;
	sf::Image& buttonImage;
	static const int size = 128;

public:
	///////////////////////////////////////////////////////////////////////
	/// @brief Constructor for buttonRenderComponent
	/// @param image is the String of a file path of a .png file
	/// @param x is the x position of the target
	///////////////////////////////////////////////////////////////////////
	buttonRenderComponent(sf::Image& image, int x, int y, int r);

	~buttonRenderComponent();

	void renderPosition(sf::Vector2f pos);

	///////////////////////////////////////////////////////////////////////
	/// @brief Returns a pointer to the button's sprite
	///////////////////////////////////////////////////////////////////////
	sf::Sprite* getSprite();

	///////////////////////////////////////////////////////////////////////
	/// @brief Updates sprite image by changing its spritesheet position
	/// @param x: Designates the COLUMN of the sprite sheet loaded
	/// @param y: Designates the ROW of the sprite sheet loaded
	/// @param r: Designates the WIDTH of the sprite sheet loaded
	///////////////////////////////////////////////////////////////////////
	void setSprite(int x, int y, int r);

	///////////////////////////////////////////////////////////////////////
	/// @brief Updates the scale (width) of the sprite
	///////////////////////////////////////////////////////////////////////
	void setButtonScale(int r);

	///////////////////////////////////////////////////////////////////////
	/// @brief The main draw function that was inheirted from RenderComponent.
	/// @details You need to define this to create a child of RenderComponent
	/// @param target: This is almost always going to be a sf::renderWindow. states:
	/// This is used to dictate certain states that the object can be rendered in. 
	/// For now this can be safely "ignored" Just created a RenderStates object and
	/// shove it in there. 
	///////////////////////////////////////////////////////////////////////
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;


	//virtual void registerInput(sf::Event& ev) override;
	virtual void recieveMessage(msgType code) override;
	
};
