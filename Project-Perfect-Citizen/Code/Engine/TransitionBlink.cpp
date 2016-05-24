//
//  TransitionBlink.cpp
//  Project-Perfect-Citizen
//
//  Created by Michael Lowe on 5/20/16.
//  Copyright © 2016 Hyperfocus Games. All rights reserved.
//

#include "TransitionBlink.hpp"
#include "World.h"


/*====================================================
 TEMPORARY TRANSITION CODE (FROM createDesktop.cpp)
 =====================================================
 
 Entity transition;
 
 sf::Image img;
 img.loadFromFile(resourcePath() + "texture1.png");
 
 sf::Image img2;
 img2.loadFromFile(resourcePath() + "texture2.png");
 
 sf::Texture texture;
 texture.loadFromImage(img);
 texture.setRepeated(true);
 sf::Texture texture2;
 texture2.setRepeated(true);
 texture2.loadFromImage(img2);
 
 TransitionRenderComponent* t_render = new TransitionRenderComponent();
 TransitionBlink* t_blink = new TransitionBlink();
 t_render->setTransitionType(t_blink, false, texture, texture2);
 
 transition.addComponent(t_render);
 
 desktopWindowToModify.addEntity(transition);*/


void ppc::TransitionBlink::onAdvance() {
    
    float tpoint = getTransitionPoint();
    
    transitionShape_.setSize({transitionShape_.getSize().x, tpoint * (ppc::World::getGameScreen().sf::Window::getSize().y/2)});
    transitionShape2_.setSize({transitionShape2_.getSize().x, -tpoint * (ppc::World::getGameScreen().sf::Window::getSize().y/2)});

}