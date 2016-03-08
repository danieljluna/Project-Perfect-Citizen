//
//  bootLoadingAnimationRender.hpp
//  Project-Perfect-Citizen
//
//  Created by Michael Lowe on 3/7/16.
//  Copyright © 2016 Hyperfocus Games. All rights reserved.
//

#ifndef bootLoadingAnimationRender_hpp
#define bootLoadingAnimationRender_hpp
#pragma once

#include <stdio.h>

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../Engine/renderComponent.h"
#include <string>
#include <vector>

using namespace std;

///////////////////////////////////////////////////////////////////////
/// @brief Designated Render Component for a generic window 'X' button
/// @author Michael Lowe
/// @details The buttonRenderComponent is a basic packaged subclass
///     extension of RenderComponent, make specifically to handle
///     all generic "X" button related drawing/animating parts that
///     also broadcast and recieve messages from an input handler.
///		Stick this onto an entity to give it this functionality.
///////////////////////////////////////////////////////////////////////
class bootLoadingAnimationRender : public ppc::RenderComponent{
private:
    vector<sf::Sprite*> sprites;
    sf::Sprite* sprite;
    sf::Sprite* sprite1;
    sf::Sprite* sprite2;
    sf::Sprite* sprite3;
    sf::Sprite* sprite4;
    sf::Sprite* sprite5;
    sf::Sprite* sprite6;
    sf::Sprite* sprite7;
    sf::Sprite* sprite8;
    sf::Sprite* sprite9;
    sf::Sprite* sprite10;
    sf::Sprite* sprite11;
    sf::Sprite* sprite12;
    sf::Sprite* sprite13;
    sf::Sprite* sprite14;
    sf::Sprite* sprite15;
    sf::Sprite* sprite16;
    sf::Sprite* sprite17;
    sf::Sprite* sprite18;
    sf::Sprite* sprite19;
    sf::Sprite* sprite20;
    sf::Sprite* sprite21;
    sf::Sprite* sprite22;
    sf::Sprite* sprite23;
    sf::Sprite* sprite24;
    sf::Sprite* sprite25;
    sf::Sprite* sprite26;
    sf::Sprite* sprite27;
    sf::Sprite* sprite28;
    sf::Sprite* sprite29;
    sf::Sprite* sprite30;
    sf::Sprite* spriteLoaded;
    sf::Texture* texture;
    sf::Image& image;
    
    float loadX;
    int frame, opacity;

    
public:
    
    int getFrame() const {return frame;}
    
    ///////////////////////////////////////////////////////////////////////
    /// @brief Constructor for buttonRenderComponent
    /// @param imag is the sf::Image to be used
    /// @param x is the x index of the target sprite
    /// @param y is the y index of the target sprite
    ///////////////////////////////////////////////////////////////////////
    bootLoadingAnimationRender(sf::Image& img, int x, int y);
    ~bootLoadingAnimationRender();
    
    
    ///////////////////////////////////////////////////////////////////////
    /// @brief called by the update component. Updates the color of
    ///        loading bar
    ///////////////////////////////////////////////////////////////////////
    void animate();
    
    virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

    
};

#endif /* bootLoadingAnimationRender_hpp */
