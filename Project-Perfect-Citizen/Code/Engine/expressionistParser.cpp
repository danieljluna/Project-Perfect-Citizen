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
#include <map>

using namespace ppc;

expressionistParser::expressionistParser(){

}

std::vector<expressionistParser> expressionistParser::parse(std::string file){
    Json::Reader reader;
    Json::Value value;
    std::ifstream doc(resourcePath() + file, std::ifstream::binary);
    std::vector<expressionistParser> expressionist;
    if (reader.parse(doc, value)){
        Json::Value nonTerminalObj = value[ "nonterminals" ];
        std::vector<std::string> terminalNames = nonTerminalObj.getMemberNames();
        
        for (unsigned int i = 0; i < nonTerminalObj.size(); i++){
            expressionist.resize(nonTerminalObj.size());
            Json::Value expressionObj = nonTerminalObj[terminalNames[i]];
            expressionist[i].expression_ = terminalNames[i];
            expressionist[i].complete_ = expressionObj.get("complete", "ERROR").asBool();
            expressionist[i].deep_ = expressionObj.get("deep", "ERROR").asBool();
            
            for (unsigned int j = 0; j < expressionObj.size(); j++){
                Json::Value rulesObj = expressionObj["rules"];
                
                for (unsigned int k = 0; k < rulesObj.size(); k++){
                    std::string expansion = rulesObj[k].get("expansion", "ERROR")[0].asString();
                    Json::Value markUpObj = rulesObj[k].get("markup", "ERROR");
                    
                    Json::Value agePre = markUpObj.get("agePreconditions", " ");
                    Json::Value iqPre = markUpObj.get("iqPreconditions", " ");
                    Json::Value linkSus = markUpObj.get("linkSuspicion", " ");
                    Json::Value personalityPre = markUpObj.get("personalityPreconditions", " ");
                    Json::Value relationship = markUpObj.get("relationship", " ");
                    for(unsigned int l = 0; l < agePre.size(); l++){
                        expressionist[i].markUp_["agePreconditions"] = agePre[l].asString();
                    }
                    for(unsigned int l = 0; l < iqPre.size(); l++){
                        expressionist[i].markUp_["iqPreconditions"] = iqPre[l].asString();
                    }
                    for(unsigned int l = 0; l < linkSus.size(); l++){
                        expressionist[i].markUp_["linkSuspicion"] = linkSus[l].asString();
                    }
                    for(unsigned int l = 0; l < personalityPre.size(); l++){
                        expressionist[i].markUp_["personalityPreconditions"] = personalityPre[l].asString();
                    }
                    for(unsigned int l = 0; l < relationship.size(); l++){
                        expressionist[i].markUp_["relationship"] = relationship[l].asString();
                    }
                }
            }
        }
    }
    return expressionist;
}