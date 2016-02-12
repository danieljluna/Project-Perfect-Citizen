#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "renderComponent.h"
#include <string>

using namespace std;

///////////////////////////////////////////////////////////////////////
/// @brief Designated Render Component for an Text Input Box
/// @author Michael Lowe / Alex Vincent
/// @details write this later
///////////////////////////////////////////////////////////////////////
class textInputRenderComponent : public ppc::RenderComponent{
private:
    sf::Sprite* sprite;
//   sf::Texture* texture;
  //  sf::IntRect* rectSourceSprite;
    sf::Text* text;
    sf::Font* font;
    string str;
   // int frameCount, width, xIndex, yIndex;
    static const int size = 128;

public:
    
    textInputRenderComponent(sf::Font& f);
    
    ~textInputRenderComponent();
    
    void updateString(string s);
    
    ///////////////////////////////////////////////////////////////////////
    /// @brief
    ///////////////////////////////////////////////////////////////////////
    virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
    
    
    //virtual void registerInput(sf::Event& ev) override;
    virtual void recieveMessage(msgType code) override;

};