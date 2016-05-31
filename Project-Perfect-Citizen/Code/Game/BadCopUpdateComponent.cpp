//
//  BadCopUpdateComponent.cpp
//  Project-Perfect-Citizen
//
//  Created by Michael Lowe on 5/11/16.
//  Copyright © 2016 Hyperfocus Games. All rights reserved.
//

#include "BadCopUpdateComponent.hpp"
#include "../Engine/debug.h"
#include <SFML/System/Time.hpp>

using namespace ppc;


BadCopUpdateComponent::BadCopUpdateComponent(BadCopRenderComponent& r, float s){
    render = &r;
    speed = s;
    framePeriod = sf::seconds(speed);
}

BadCopUpdateComponent::~BadCopUpdateComponent() {
    render = nullptr;
}

void BadCopUpdateComponent::update(sf::Time& deltaTime) {
    if (render->willAnimate()) {
        counter += deltaTime;
        
       // if (counter.asSeconds() > speed)
         //   counter = framePeriod;
        
        if (counter >= framePeriod) {
            render->animate();
            counter -= framePeriod;
        }
    }
}

