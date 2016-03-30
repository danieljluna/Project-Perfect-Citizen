#include "../Engine/debug.h"
#include "animatorComponent.hpp"


using namespace ppc;

const std::string MOUSE_DOUBLE_CLICK_CODE = "MDDC";

animatorComponent::animatorComponent(buttonRenderComponent& r, float s){
    render = &r;
    speed = s;
    framePeriod = sf::seconds(speed);
}

animatorComponent::~animatorComponent() {
    render = nullptr;
}

void animatorComponent::update(sf::Time& deltaTime) {
    if (render->willAnimate()) {
        counter += deltaTime;
        
        if (counter >= framePeriod) {
            render->animate();
            counter -= framePeriod;
        }
    }
   
}

