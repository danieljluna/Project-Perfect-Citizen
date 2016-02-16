//
//  expressionistParser.cpp
//  Project-Perfect-Citizen
//
//  Created by Brandon Gomez on 2/15/16.
//  Copyright © 2016 Hyperfocus Games. All rights reserved.
//

//Used to get XCODE working/////////////////////////////////

#ifdef WINDOWS_MARKER
#define resourcePath() string("Resources/")
#else
#include "ResourcePath.hpp"
#endif

///////////////////////////////////////////////////////////

#include "expressionistParser.hpp"
#include "../Library/json/json.h"
#include <iostream>
#include <fstream>

using namespace ppc;

expressionistParser::expressionistParser(){


}

void expressionistParser::parse(std::string file){
    Json::Reader reader;
    Json::Value value;
    std::ifstream doc(resourcePath() + file, std::ifstream::binary);
    if (reader.parse(doc, value)){
        Json::Value nonTerminalObj = value[ "nonterminals" ];
        std::vector<std::string> terminalNames = nonTerminalObj.getMemberNames();
        
        for (unsigned int i = 0; i < nonTerminalObj.size(); i++){
            Json::Value expressionObj = nonTerminalObj[terminalNames[i]];
            this->complete_ = expressionObj.get("complete", "ERROR").asBool();
            this->deep_ = expressionObj.get("deep", "ERROR").asBool();
            
            for (unsigned int j = 0; j < expressionObj.size(); j++){
                Json::Value rulesObj = expressionObj["rules"];
                
                for (unsigned int k = 0; k < rulesObj.size(); k++){
                    this->appRate_ = rulesObj[k].get("app_rate", "ERROR").asInt();
                    this->expansion_ = rulesObj[k].get("expansion", "ERROR")[0].asString();
                    Json::Value markUpObj = rulesObj[k].get("markup", "ERROR");
                    Json::Value agePre = markUpObj.get("agePreconditions", " ");
                    
                    for(unsigned int l = 0; l < agePre.size(); l++){
                        markUp_.push_back(agePre[l].asString());
                    }
                }
            }
        }
    }
}