//
//  interpolateUpdateComponent.hpp
//  Project-Perfect-Citizen
//
//  Created by Michael Lowe on 3/8/16.
//  Copyright © 2016 Hyperfocus Games. All rights reserved.
//

#ifndef interpolateUpdateComponent_hpp
#define interpolateUpdateComponent_hpp

#include <stdio.h>

#include <SFML/Graphics.hpp>
#include "../Engine/updateComponent.h"

using namespace std;

///////////////////////////////////////////////////////////////////////
/// @brief Interpolate Class for Updating Variables Between Two Values
/// @author Michael Lowe
/// @details Interpolate Class for Updating Variables Between Two Values
///////////////////////////////////////////////////////////////////////

class Interpolate: public ppc::UpdateComponent{
    
private:
    int start;
    int finish;
    int value_;
    float speed;
    bool begin_;
    bool running_;
    sf::Time counter;
    sf::Time framePeriod;
    
public:
    
    Interpolate(int i, int j, float f);
    ~Interpolate();
    
    void begin();
    int value() const {return value_;}
    bool running() const {return running_;}
    
    
    ////////////////////////////////////////////////////////////////////
    /// @brief update method for bootLoadingUpdateComponent
    /// @param deltaTime is the time that has passed since the last
    ///        render update by the engine.
    ////////////////////////////////////////////////////////////////////
    void update(sf::Time& deltaTime) override;
    

};



#endif /* interpolateUpdateComponent_hpp */
