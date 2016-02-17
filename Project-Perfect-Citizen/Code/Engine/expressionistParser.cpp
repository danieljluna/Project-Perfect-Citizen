//
//  expressionistParser.cpp
//  Project-Perfect-Citizen
//
//  Created by Brandon Gomez on 2/15/16.
//  Copyright © 2016 Hyperfocus Games. All rights reserved.
//

//Used to get XCODE working/////////////////////////////////////////////

#ifdef WINDOWS_MARKER
#define resourcePath() string("Resources/")
#else
#include "ResourcePath.hpp"
#endif

////////////////////////////////////////////////////////////////////////

#include "expressionistParser.hpp"
#include "../Library/json/json.h"
#include <iostream>
#include <fstream>
#include <map>

using namespace std;

////////////////////////////////////////////////////////////////////////
///constructor for parsing expressionist data
////////////////////////////////////////////////////////////////////////

expressionistParser::expressionistParser(){

}

////////////////////////////////////////////////////////////////////////
///parsing out the JSON file returning a vector of the class
////////////////////////////////////////////////////////////////////////

vector<expressionistParser> expressionistParser::parse(string file){
    Json::Reader reader;
    Json::Value value;
    ifstream doc(resourcePath() + file, ifstream::binary);
    vector<expressionistParser> parsed;
    if (reader.parse(doc, value)){
        Json::Value nonTerminalObj = value[ "nonterminals" ];
        vector<string> terminalNames
            = nonTerminalObj.getMemberNames();
        
        for (unsigned int i = 0; i < nonTerminalObj.size(); i++){
            parsed.resize(nonTerminalObj.size());
            Json::Value expressionObj
                = nonTerminalObj[terminalNames[i]];
            parsed[i].expression_ = terminalNames[i];
            parsed[i].complete_
                = expressionObj.get("complete", "ERROR").asBool();
            parsed[i].deep_
                = expressionObj.get("deep", "ERROR").asBool();
            
            for (unsigned int j = 0; j < expressionObj.size(); j++){
                Json::Value rules = expressionObj["rules"];
                
                for (unsigned int k = 0; k < rules.size(); k++){
                    parsed[i].appRate_
                    = rules[k].get("app_rate", "ER").asInt();
                    string expansion
                        = rules[k].get("expansion", "ER")[0].asString();
                    Json::Value markUps
                        = rules[k].get("markup", "ERROR");
                    
                    Json::Value agePre
                        = markUps.get("agePreconditions", " ");
                    Json::Value iqPre
                        = markUps.get("iqPreconditions", " ");
                    Json::Value linkSus
                        = markUps.get("linkSuspicion", " ");
                    Json::Value personalPre
                        = markUps.get("personalityPreconditions", " ");
                    Json::Value relationship
                        = markUps.get("relationship", " ");
                    for(int l = 0; l < agePre.size(); l++){
                        parsed[i].markUp_["agePreconditions"]
                            = agePre[l].asString();
                    }
                    for(int l = 0; l < iqPre.size(); l++){
                        parsed[i].markUp_["iqPreconditions"]
                            = iqPre[l].asString();
                    }
                    for(int l = 0; l < linkSus.size(); l++){
                        parsed[i].markUp_["linkSuspicion"]
                            = linkSus[l].asString();
                    }
                    for(int l = 0; l < personalPre.size(); l++){
                        parsed[i].markUp_["personalityPreconditions"]
                            = personalPre[l].asString();
                    }
                    for(int l = 0; l < relationship.size(); l++){
                        parsed[i].markUp_["relationship"]
                            = relationship[l].asString();
                    }
                }
            }
        }
    }
    return parsed;
}