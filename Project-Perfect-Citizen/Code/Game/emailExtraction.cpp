//
//  emailExtraction.cpp
//  Project-Perfect-Citizen
//
//  Created by Brandon Gomez on 3/7/16.
//  Copyright © 2016 Hyperfocus Games. All rights reserved.
//


#ifdef WINDOWS_MARKER
#define resourcePath() std::string("Resources/")
#else
#include "ResourcePath.hpp"
#endif

///////////////////////////////////////////////////////////

#include "emailExtraction.hpp"
#include "../Engine/debug.h"
#include "../Library/json/json.h"
#include "../Game/TreeCommands.h"
#include <iostream>
#include <fstream>

using namespace ppc;

emailExtraction::emailExtraction(){
    
}

Json::Value emailExtraction::parseEmailAsJson(std::string file, std::string obj) {
    Json::Reader reader;
    Json::Value value;
    std::ifstream doc(resourcePath() + file, std::ifstream::binary);
    reader.parse(doc, value);
    parseEmailForInbox(value, obj);
    return value;
}

void emailExtraction::parseEmailForInbox(Json::Value value, std::string folder) {
    Json::Value directoryObj = value[folder];
    std::vector<std::string> objNames = directoryObj.getMemberNames();
    for (unsigned int i = 0; i < directoryObj.size(); i++){
        auto contentObj = directoryObj[objNames[i]];
        std::string objName = objNames[i];
        if(contentObj.size() > 0){
            addSubject(objNames[i]);
            parseEmailForInbox(directoryObj, objNames[i]);
        }
        else{
            std::string body = directoryObj[objNames[i]].asString();
            addContent(body);
        }
    }
}




