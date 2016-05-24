#include "startBarUpdateComponent.hpp"
#include "../Engine/debug.h"


using namespace ppc;


startBarUpdateComponent::startBarUpdateComponent(startBarRenderComponent& r){
    render = &r;
    framePeriod = sf::seconds(speed);
}

startBarUpdateComponent::~startBarUpdateComponent() {
    render = nullptr;
}

void startBarUpdateComponent::update(sf::Time& deltaTime) {
    
    counter += deltaTime;
        
    if (counter >= framePeriod) {
        render->animate();
        counter -= framePeriod;
    }
}

