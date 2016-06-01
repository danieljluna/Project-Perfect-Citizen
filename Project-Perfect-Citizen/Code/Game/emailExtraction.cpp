//
//  emailExtraction.cpp
//  Project-Perfect-Citizen
//
//  Created by Brandon Gomez on 3/7/16.
//  Copyright © 2016 Hyperfocus Games. All rights reserved.
//


#include "../ResourceDef.h"
#include "emailExtraction.hpp"
#include "../Engine/NodeState.h"
#include "../Engine/debug.h"
#include "../Library/json/json.h"
#include "../Game/TreeCommands.h"
#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace ppc;

emailExtraction::emailExtraction(){
    
}

Json::Value emailExtraction::parseEmailAsJson(std::string file) {
    Json::Reader reader;
    Json::Value value;
    std::ifstream doc(resourcePath() + file, std::ifstream::binary);
    reader.parse(doc, value);
    parseEmailForInbox(value, "Email");
    return value;
}

void emailExtraction::parseEmailForInbox(Json::Value value, std::string folder) {
    Json::Value directoryObj = value[folder];
    std::vector<std::string> objNames = directoryObj.getMemberNames();
    for (unsigned int i = 0; i < directoryObj.size(); i++){
        auto contentObj = directoryObj[objNames[i]];
        std::string objName = objNames[i];
        if(contentObj.size() > 0){
            parseEmailForInbox(directoryObj, objNames[i]);
        }
        else{
            std::string content = directoryObj[objNames[i]].asString();
            //std::cout << objName+""+content << std::endl;
            if(objName == "Subject"){
                addSubject(content);
            }
            else if(objName == "To"){
                addTo(content);
            }
            else if(objName == "From"){
                addFrom(content);
            }
            else if(objName == "Body"){
                addBody(content);
            }
            else if(objName == "Visible"){
                addVisible(content.compare("1") == 0);
            }
            else{
                std::cout << "ERROR" << std::endl;
            }
        }
    }
}




