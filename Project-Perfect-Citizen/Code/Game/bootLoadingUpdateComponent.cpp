//
//  bootLoadingUpdateComponent.cpp
//  Project-Perfect-Citizen
//
//  Created by Michael Lowe on 3/7/16.
//  Copyright © 2016 Hyperfocus Games. All rights reserved.
//

#include "../Engine/debug.h"
#include "bootLoadingUpdateComponent.hpp"


bootLoadingUpdateComponent::bootLoadingUpdateComponent(bootLoadingAnimationRender& r,buttonRenderComponent& b, float s):button(b){
    render = &r;
    speed = s;
    framePeriod = sf::seconds(speed);
}

bootLoadingUpdateComponent::~bootLoadingUpdateComponent() {
    render = nullptr;
}

void bootLoadingUpdateComponent::update(sf::Time& deltaTime) {
    if (render->getFrame() != 62) {
        if (render->getFrame() == 30) {
            button.getSprite()->setColor(sf::Color(0,0,0,0));
        }
        counter += deltaTime;
        
        if (counter >= framePeriod) {
            render->animate();
            counter -= framePeriod;
        }
    }
}

