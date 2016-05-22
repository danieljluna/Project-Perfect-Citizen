//
//  endAnimationUpdateComponent.cpp
//  Project-Perfect-Citizen
//
//  Created by Michael Lowe on 3/10/16.
//  Copyright © 2016 Hyperfocus Games. All rights reserved.
//

#include "endAnimationUpdateComponent.hpp"
#include "endingAnimationRender.hpp"
#include "../Engine/debug.h"

using namespace ppc;

endAnimationUpdateComponent::endAnimationUpdateComponent(endingAnimationRender& r,float s){
    render = &r;
    speed = s;
    framePeriod = sf::seconds(speed);
}

endAnimationUpdateComponent::~endAnimationUpdateComponent() {
    render = nullptr;
}

void endAnimationUpdateComponent::update(sf::Time& deltaTime) {

    counter += deltaTime;
    
    if (counter >= framePeriod) {
        render->animate();
        counter -= framePeriod;
    }
    
}

