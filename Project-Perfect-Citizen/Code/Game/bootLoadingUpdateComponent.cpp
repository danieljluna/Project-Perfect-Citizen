//
//  bootLoadingUpdateComponent.cpp
//  Project-Perfect-Citizen
//
//  Created by Michael Lowe on 3/7/16.
//  Copyright © 2016 Hyperfocus Games. All rights reserved.
//

#include "../Engine/debug.h"
#include "bootLoadingUpdateComponent.hpp"


bootLoadingUpdateComponent::bootLoadingUpdateComponent(bootLoadingAnimationRender& r, float s){
    render = &r;
    speed = s;
    framePeriod = sf::seconds(speed);
}

bootLoadingUpdateComponent::~bootLoadingUpdateComponent() {
    render = nullptr;
}

void bootLoadingUpdateComponent::update(sf::Time& deltaTime) {
 
    counter += deltaTime;
    
    if (counter >= framePeriod) {
        render->animate();
        counter -= framePeriod;
    }

}

