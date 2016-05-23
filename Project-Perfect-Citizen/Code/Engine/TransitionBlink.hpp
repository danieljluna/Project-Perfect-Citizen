//
//  TransitionBlink.hpp
//  Project-Perfect-Citizen
//
//  Created by Michael Lowe on 5/20/16.
//  Copyright © 2016 Hyperfocus Games. All rights reserved.
//

#ifndef TransitionBlink_hpp
#define TransitionBlink_hpp

#include <stdio.h>
#include "Transition.h"

namespace ppc {


class TransitionBlink : public Transition {
  
    void onAdvance() override;
    
};
    
};




#endif /* TransitionBlink_hpp */
