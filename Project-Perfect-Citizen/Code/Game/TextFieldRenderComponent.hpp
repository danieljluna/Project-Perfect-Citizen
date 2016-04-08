#pragma once

#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "../Engine/renderComponent.h"
#include <string>

using namespace std;

///////////////////////////////////////////////////////////////////////
/// @brief Designated Render Component for a text field
/// @author Micahel Lowe
/// @details Draws the actual box
///////////////////////////////////////////////////////////////////////
class TextFieldRenderComponent : public ppc::RenderComponent {
private:
    sf::RectangleShape box;
    sf::RectangleShape shadow;
    sf::RectangleShape shadow2;
    sf::RectangleShape white;
    sf::FloatRect bounds;
    
    
public:
    ///////////////////////////////////////////////////////////////////////
    /// @brief Constructor for buttonRenderComponent
    /// @param w is width
    /// @param h is height
    ///////////////////////////////////////////////////////////////////////
    TextFieldRenderComponent(float x, float y, float w, float h);
    
    ~TextFieldRenderComponent();
    virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
    
};