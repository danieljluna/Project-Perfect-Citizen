//
//  desktopExtractionComponent.hpp
//  Project-Perfect-Citizen
//
//  Created by Brandon Gomez on 2/12/16.
//  Copyright © 2016 Hyperfocus Games. All rights reserved.
//

#ifndef desktopExtractionComponent_hpp
#define desktopExtractionComponent_hpp

#include <stdio.h>
#include <string>
#include <vector>

#include "../Library/json/json.h"

namespace ppc {

class desktopExtractionComponent{
    
public:
    
    ///////////////////////////////////////////////////////////////////
    ///@brief constructor for crearting desktop data
    ///////////////////////////////////////////////////////////////////
    desktopExtractionComponent();
    
    ////////////////////////////////////////////////////////////////////
    /// @brief Builds Json::Value Object containing Desktop content and
    //      their appropiate paths
    /// @details Builds a C++ Json representation of Desktop content
    ///     object as specified by a .json file
    /// @param[out] Json::Value         Json object containing
    ///                                 an expressionist grammar
    /// @param[in]  string              Json file name containing an
    ///                                 expressionist grammar
    ////////////////////////////////////////////////////////////////////
    Json::Value parseDesktopAsJson(std::string file);
        
private:

};

};
    


#endif /* desktopExtractionComponent_hpp */