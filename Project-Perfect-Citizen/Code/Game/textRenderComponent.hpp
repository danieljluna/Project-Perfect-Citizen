//
//  textRenderComponent.hpp
//  Project-Perfect-Citizen
//
//  Created by Brandon Gomez on 3/2/16.
//  Copyright © 2016 Hyperfocus Games. All rights reserved.
//

#ifndef textRenderComponent_hpp
#define textRenderComponent_hpp

#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "../Engine/renderComponent.h"
#include <string>

using namespace std;

class textRenderComponent : public ppc::RenderComponent{
private:
    sf::Sprite* sprite;
    sf::Text* text;
    sf::Font font;
    string str;
    static const int size = 128;
    
public:
    
    textRenderComponent(sf::Font& f, string text, int x, int y, int size);
    
    ~textRenderComponent();
    
    virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
};

#endif /* textRenderComponent_hpp */
