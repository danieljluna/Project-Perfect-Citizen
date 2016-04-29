#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../Engine/renderComponent.h"
#include <string>

namespace ppc {
    
    ///////////////////////////////////////////////////////////////////////
    /// @brief Designated Floppy Render Component
    /// @author Michael Lowe
    /// @details
    ///////////////////////////////////////////////////////////////////////
    class FloppyRenderComponent : public ppc::RenderComponent{
    private:
        sf::Sprite* sprite;
        sf::Sprite* staticBox;
        sf::Texture* texture;
        sf::IntRect* rectSourceSprite;
        sf::Image& floppyImage;
        int emotion;
        int xIndex, yIndex;
        bool _willAnimate;
        static const int size = 128;
        
    public:
        
        enum Emotes{
            Default,
            Angry,
            Surprised,
            Peek,
        };
        
        bool willAnimate() const {return _willAnimate;}
        
        ///////////////////////////////////////////////////////////////////////
        /// @brief Constructor for buttonRenderComponent
        /// @param image is the String of a file path of a .png file
        /// @param x is the x position of the target
        /// @param r is the range of indices that the sprite covers
        /// @param f is the frame count of animation. 1 for static sprite
        ///////////////////////////////////////////////////////////////////////
        FloppyRenderComponent(sf::Image& image);
        
        ~FloppyRenderComponent();
        
        
        ///////////////////////////////////////////////////////////////////////
        /// @brief changes the position of the component within its parent view
        ///////////////////////////////////////////////////////////////////////
        void renderPosition(sf::Vector2f pos);
        
        ///////////////////////////////////////////////////////////////////////
        /// @brief Sets the X/Y scale of the square image texture of the button
        ///////////////////////////////////////////////////////////////////////
        void setImageScale(float ScaleX, float ScaleY);
    
        
        ///////////////////////////////////////////////////////////////////////
        /// @brief Sets the animation for Floppy
        ///////////////////////////////////////////////////////////////////////
        //void setAnimationLoad();
       
        
        void  setEmotion(int e);
        
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
