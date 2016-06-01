#pragma once

#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

#include "../Engine/renderComponent.h"

namespace ppc {
    
    ///////////////////////////////////////////////////////////////////////
    /// @brief Designated BadCop Render Component
    /// @author Michael Lowe
    /// @details
    ///////////////////////////////////////////////////////////////////////
    class BadCopRenderComponent : public ppc::RenderComponent{
    private:
        sf::Sprite* sprite;
        sf::Texture* texture;
        sf::IntRect* rectSourceSprite;
        sf::Image& BadCopImage;
        int xIndex, yIndex;
        int blackScreen;
        int alpha;
        bool _willAnimate;
        mutable bool hasDrawn = false;
        static const int size = 512;
        
    public:
        
        
        bool willAnimate() const {return _willAnimate;}
        
        ///////////////////////////////////////////////////////////////////////
        /// @brief Constructor for buttonRenderComponent
        /// @param image is the String of a file path of a .png file
        /// @param x is the x position of the target
        /// @param r is the range of indices that the sprite covers
        /// @param f is the frame count of animation. 1 for static sprite
        ///////////////////////////////////////////////////////////////////////
        BadCopRenderComponent(sf::Image& image);
        
        ~BadCopRenderComponent();
        
        
        ///////////////////////////////////////////////////////////////////////
        /// @brief changes the position of the component within its parent view
        ///////////////////////////////////////////////////////////////////////
        void renderPosition(sf::Vector2f pos);
        
        ///////////////////////////////////////////////////////////////////////
        /// @brief Sets the X/Y scale of the square image texture of the button
        ///////////////////////////////////////////////////////////////////////
        void setImageScale(float ScaleX, float ScaleY);
        
        
        ///////////////////////////////////////////////////////////////////////
        /// @brief Animates the sprite
        ///////////////////////////////////////////////////////////////////////
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
        
        
        //virtual void registerInput(Event ev) override;
        
        virtual void recieveMessage(msgType code) override;
        
        virtual void recieveMessage(Event ev) override;
    };
    
    
};
