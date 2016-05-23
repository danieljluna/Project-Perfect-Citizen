#pragma once


#include <string>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "../Engine/renderComponent.h"

namespace sf {
    class Sprite;
    class Texture;
    class Image;
    class Font;
    class Text;
    class RenderTarget;
}

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
    class startBarRenderComponent : public ppc::RenderComponent{
    private:
        sf::RectangleShape startBar;
        sf::RectangleShape blackBorder;
        sf::RectangleShape whiteBorder;
        sf::Text dateText;
        sf::Font dateFont;
        
    public:
        ///////////////////////////////////////////////////////////////////////
        /// @brief Constructor for buttonRenderComponent
        /// @param image is the String of a file path of a .png file
        /// @param x is the x position of the target
        /// @param r is the range of indices that the sprite covers
        /// @param f is the frame count of animation. 1 for static sprite
        ///////////////////////////////////////////////////////////////////////
        startBarRenderComponent(sf::Font&);
        
        ~startBarRenderComponent();
        
        std::string getCurrentTime();
        
        
        ///////////////////////////////////////////////////////////////////////
        /// @brief changes the position of the component within its parent view
        ///////////////////////////////////////////////////////////////////////
        void renderPosition(sf::Vector2f pos);
        
        
        void animate();
        ///////////////////////////////////////////////////////////////////////
        /// @brief The main draw function that was inheirted from RenderComponent.
        /// @details You need to define this to create a child of RenderComponent
        /// @param target: This is almost always going to be a sf::renderWindow. states:
        /// This is used to dictate certain states that the object can be rendered in.
        /// For now this can be safely "ignored" Just created a RenderStates object and
        /// shove it in there.
        ///////////////////////////////////////////////////////////////////////
        virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
        
        
        virtual void recieveMessage(Event ev) override;
    };
    
    
    
    
};
