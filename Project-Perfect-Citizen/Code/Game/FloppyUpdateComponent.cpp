#include "../Engine/debug.h"
#include "FloppyUpdateComponent.hpp"


using namespace ppc;


FloppyUpdateComponent::FloppyUpdateComponent(FloppyRenderComponent& r, float s){
    render = &r;
    speed = s;
    framePeriod = sf::seconds(speed);
}

FloppyUpdateComponent::~FloppyUpdateComponent() {
    render = nullptr;
}

void FloppyUpdateComponent::update(sf::Time& deltaTime) {
    if (render->willAnimate()) {
        counter += deltaTime;
        
        if (counter >= framePeriod) {
          //  if (render->getAnimationType() == 0) {
                render->animate();
                 counter -= framePeriod;
        }
    }
    
}

