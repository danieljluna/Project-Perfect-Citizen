//
//  testButtonPress.hpp
//  Project-Perfect-Citizen
//
//  Created by Michael Lowe on 2/2/16.
//  Copyright © 2016 Hyperfocus Games. All rights reserved.
//

#ifndef testButtonPress_hpp
#define testButtonPress_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "inputComponent.h"

class ButtonPress : public ppc::InputComponent {
public:
    
    virtual ~ButtonPress() {};
    
    virtual void registerInput(sf::Event&) override;
    
};

#endif /* testButtonPress_hpp */
