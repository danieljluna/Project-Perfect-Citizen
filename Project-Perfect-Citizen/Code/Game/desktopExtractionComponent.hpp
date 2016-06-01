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
#include "../Engine/NodeState.h"

namespace ppc {
    
    class desktopExtractionComponent{
        
    public:
        
        ///////////////////////////////////////////////////////////////////
        ///@brief constructor for crearting desktop data
        ///////////////////////////////////////////////////////////////////
        desktopExtractionComponent(NodeState* fileTree_);
        
        ////////////////////////////////////////////////////////////////////
        /// @brief Builds Json::Value Object containing Desktop content and
        ///      their appropiate paths
        /// @details Builds a C++ Json representation of Desktop content
        ///     object as specified by a .json file
        /// @param[out] Json::Value         Json object containing
        ///                                 an expressionist grammar
        /// @param[in]  string              Json file name containing an
        ///                                 expressionist grammar
        ////////////////////////////////////////////////////////////////////
        Json::Value parseDesktopAsJson(std::string file, std::string obj);
        
        ///////////////////////////////////////////////////////////////////
        /// @brief parses the JSON file and gets the appropiate file name
        ///     & path, to be used with a desktop file tree
        /// @param[in] Json::Value          Json object containg the dir
        ///                                 objects
        /// @param[in] std::string          The name of the folder to be
        ///                                 entered
        ///////////////////////////////////////////////////////////////////
        void parseForFileTree(Json::Value obj, std::string folder);
        
        
    private:
        NodeState* fileTree_;
    };
    
};



#endif /* desktopExtractionComponent_hpp */
