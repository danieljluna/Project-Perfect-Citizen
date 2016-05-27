//
//  interpolateUpdateComponent.cpp
//  Project-Perfect-Citizen
//
//  Created by Michael Lowe on 3/8/16.
//  Copyright © 2016 Hyperfocus Games. All rights reserved.
//

#include "interpolateUpdateComponent.hpp"

using namespace ppc;

Interpolate::Interpolate(int i, int j, float f) {
    start = i;
    finish = j;
    value_ = start;
    speed = f;
    begin_ = false;
    running_ = false;
}

void Interpolate::begin() {
    begin_ = true;
    running_ = true;
}

Interpolate::~Interpolate() {
    
}

void Interpolate::update(sf::Time& deltaTime) {
    if (begin_) {
        if (value_ != finish) {
            counter += deltaTime;
        
            if (counter >= framePeriod) {
                if (start < finish) value_ += 1;
                else if(start > finish) value_ -= 1;
                counter -= framePeriod;
            }
        } else {
            running_ = false;
            begin_ = false;
        }
    }
   
}

