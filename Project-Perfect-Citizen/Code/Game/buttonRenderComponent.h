#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../Engine/renderComponent.h"
#include <string>

namespace ppc {

///////////////////////////////////////////////////////////////////////
/// @brief Designated Render Component for a generic window 'X' button
/// @author Alex Vincent / Michael Lowe
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
    sf::IntRect* rectSourceSprite;
	sf::Image& buttonImage;
    int frameCount, width, xIndex, yIndex;
    bool _willAnimate;
    std::string _buttonType;
	static const int size = 128;
    //unsigned int notificationCount_ = 0;
    //sf::CircleShape badge_;
    //sf::Text notificationText_;

public:
	///////////////////////////////////////////////////////////////////////
	/// @brief Constructor for buttonRenderComponent
	/// @param image is the String of a file path of a .png file
	/// @param x is the x position of the target
    /// @param r is the range of indices that the sprite covers
    /// @param f is the frame count of animation. 1 for static sprite
	///////////////////////////////////////////////////////////////////////
	buttonRenderComponent(sf::Image& image, int x, int y, int r, int f);

	~buttonRenderComponent();

    
    ///////////////////////////////////////////////////////////////////////
    /// @brief changes the position of the component within its parent view
    ///////////////////////////////////////////////////////////////////////
	void renderPosition(sf::Vector2f pos);

	///////////////////////////////////////////////////////////////////////
	/// @brief Sets the X/Y scale of the square image texture of the button
	///////////////////////////////////////////////////////////////////////
	void setImageScale(float ScaleX, float ScaleY);

	///////////////////////////////////////////////////////////////////////
	/// @brief Returns a pointer to the button's sprite
	///////////////////////////////////////////////////////////////////////
	sf::Sprite* getSprite();

	///////////////////////////////////////////////////////////////////////
	/// @brief Updates sprite image by changing its spritesheet position
	/// @param x: Designates the COLUMN of the sprite sheet loaded
	/// @param y: Designates the ROW of the sprite sheet loaded
	/// @param r: Designates the WIDTH (range) of the sprite sheet loaded
	///////////////////////////////////////////////////////////////////////
	void setSprite(int x, int y, int r);

    ///////////////////////////////////////////////////////////////////////
    /// @brief Updates the button type (Icon / Button)
    ///////////////////////////////////////////////////////////////////////
    void setButtonType(std::string t);

    ///////////////////////////////////////////////////////////////////////
    /// @brief Returns button type
    ///////////////////////////////////////////////////////////////////////
    std::string getButtonType() const { return _buttonType; }

	///////////////////////////////////////////////////////////////////////
	/// @brief Updates the scale (width) of the sprite
	///////////////////////////////////////////////////////////////////////
	void setButtonScale(int r);
    
    ///////////////////////////////////////////////////////////////////////
    /// @brief Animates the sprite
    ///////////////////////////////////////////////////////////////////////
    void animate();
    
    ///////////////////////////////////////////////////////////////////////
    /// @brief flag that returns true is the sprite should enter
    //         its animation sequence. Resets when animation completes
    ///////////////////////////////////////////////////////////////////////
    bool willAnimate();
    
	///////////////////////////////////////////////////////////////////////
	/// @brief The main draw function that was inheirted from RenderComponent.
	/// @details You need to define this to create a child of RenderComponent
	/// @param target: This is almost always going to be a sf::renderWindow. states:
	/// This is used to dictate certain states that the object can be rendered in. 
	/// For now this can be safely "ignored" Just created a RenderStates object and
	/// shove it in there. 
	///////////////////////////////////////////////////////////////////////
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;


	//virtual void registerInput(sf::Event ev) override;

	virtual void recieveMessage(msgType code) override;
	
	virtual void recieveMessage(Event ev) override;
};




};
