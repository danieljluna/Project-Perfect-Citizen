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


void desktopExtractionComponent::setDesktop(std:: string file){
    Json::Reader reader;
    Json::Value value;
    std::vector<std::string> vectorHolder;;
    std::ifstream doc(resourcePath() + file, std::ifstream::binary);
    if (reader.parse(doc, value)){
        Json::Value emailObj = value[ "Emails" ];
        for (unsigned int i = 0; i < emailObj.size(); i++){
            vectorHolder.push_back(emailObj[i].asString());
        }
        this->setEmail(vectorHolder);
        vectorHolder.clear();
        Json::Value chatObj = value[ "Chat Messages" ];
        for (unsigned int i = 0; i < chatObj.size(); i++){
            vectorHolder.push_back(chatObj[i].asString());
        }
        this->setMessages(vectorHolder);
        vectorHolder.clear();
        Json::Value historyObj = value[ "Local History" ];
        for (unsigned int i = 0; i < historyObj.size(); i++){
            vectorHolder.push_back(historyObj[i].asString());
        }
        this->setHistory(vectorHolder);
        vectorHolder.clear();
        Json::Value documentsObj = value[ "Local Documents" ];
        for (unsigned int i = 0; i < documentsObj.size(); i++){
            vectorHolder.push_back(documentsObj[i].asString());
        }
        this->setDocuments(vectorHolder);
    }
}