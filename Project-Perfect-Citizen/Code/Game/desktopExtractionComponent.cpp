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
    /*
    Json::Value nonTerminalObj = value[ "Desktop" ];
    std::vector<std::string> terminalNames = nonTerminalObj.getMemberNames();
    for (unsigned int i = 0; i < nonTerminalObj.size(); i++){
        std::cout << terminalNames[i] << std::endl;
    }
     */
    return value;
}
