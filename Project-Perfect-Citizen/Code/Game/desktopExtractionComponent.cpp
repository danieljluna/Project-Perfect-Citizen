//
//  desktopExtractionComponent.cpp
//  Project-Perfect-Citizen
//
//  Created by Brandon Gomez on 2/12/16.
//  Copyright © 2016 Hyperfocus Games. All rights reserved.
//

//Used to get XCODE working/////////////////////////////////

#ifdef WINDOWS_MARKER
#define resourcePath() std::string("Resources/")
#else
#include "ResourcePath.hpp"
#endif

///////////////////////////////////////////////////////////

#include "desktopExtractionComponent.hpp"
#include "../Library/json/json.h"
#include <iostream>
#include <fstream>

using namespace ppc;

desktopExtractionComponent::desktopExtractionComponent(){
    
}

Json::Value desktopExtractionComponent::parseDesktopAsJson(std::string file) {
    Json::Reader reader;
    Json::Value value;
    std::ifstream doc(resourcePath() + file, std::ifstream::binary);
    reader.parse(doc, value);
    return value;
}

void desktopExtractionComponent::parseForFileTree(Json::Value value, std::string folder){
    Json::Value directoryObj = value[folder];
    std::vector<std::string> objNames = directoryObj.getMemberNames();
    for (unsigned int i = 0; i < directoryObj.size(); i++){
        auto contentObj = directoryObj[objNames[i]];
        std::string objName = objNames[i];
        // name of file/folder
        // std::cout << objName << std::endl;
        if(contentObj.size() > 0){
            parseForFileTree(directoryObj, objNames[i]);
        }
        else{
            // name of the path to access content in resources
            std::string pathName = directoryObj[objNames[i]].asString();
            //std::cout << pathName << std::endl;
        }
    }
}
