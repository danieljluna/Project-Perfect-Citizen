//
//  expressionistParser.cpp
//  Project-Perfect-Citizen
//
//  Created by Brandon Gomez on 2/15/16.
//  Copyright © 2016 Hyperfocus Games. All rights reserved.
//

//Used to get XCODE working/////////////////////////////////////////////

#ifdef WINDOWS_MARKER
#define resourcePath() std::string("Resources/")
#else
#include "ResourcePath.hpp"
#endif

////////////////////////////////////////////////////////////////////////

#include "expressionistParser.hpp"
#include "../Library/json/json.h"
#include <iostream>
#include <fstream>
#include <map>

using namespace expr;

////////////////////////////////////////////////////////////////////////
///constructor for parsing expressionist data
////////////////////////////////////////////////////////////////////////

expressionistObj::expressionistObj(){

}


std::string expr::express(const std::vector<expressionistObj>& exprObjVec) {
	std::string retString = "";
	
	//Find "deep"
	//Expand that symbol


	return retString;
	
}

std::string expr::expressionistObj::expand(const std::vector<expressionistObj>& exprObjVec) {
	// should these take Json::Value, string& as params?
	// return type bool?
	// non member functions?
	// if doing above, need override for expand incase Json::Value is string?
	// OR need string param to find relevant rule in vector?
	std::string retString = "";
	//

	return retString;
}

void expr::expressionistObj::fire(std::string & ruleName, const std::vector<expressionistObj>& exprObjVec) {
	// check complete, if false, pop out
	// pick branch based on app rate
	// expand all rules in branch
}

/*
NOTE to self:
I think the best way to do this is for expand and fire to return bools.

EXPAND SYMBOL
check markup
if markup fails checks, return failed
look at rules
pick a rule based on app rate (keep track of successes/failures, dont revisit failures)
fire rule
if success, return result of fire
if failed, try again
if all rules tried and failed, return failure

FIRE RULE
check markup
if markup fails checks, return failed
if double brackets its a rule so expand it
if single brackets its a substitution/variable so replace it
otherwise its a string so return it


*/


////////////////////////////////////////////////////////////////////////
///parsing out the JSON file returning a vector of the class
////////////////////////////////////////////////////////////////////////

std::vector<expressionistObj> expr::parseExpressionist(std::string file){
    Json::Reader reader;
    Json::Value value;
    std::ifstream doc(resourcePath() + file, std::ifstream::binary);
    std::vector<expressionistObj> parsed;
    if (reader.parse(doc, value)){
        Json::Value nonTerminalObj = value[ "nonterminals" ];
        std::vector<std::string> terminalNames
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
                    std::string expansion
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
                    int rate
                        = rules[k].get("app_rate", "ERROR").asInt();
                    for(unsigned int l = 0; l < agePre.size(); l++){
                        std::string condition = agePre[l].asString();
                        std::pair<std::string, int> conAndRate(condition, rate);
                        parsed[i].markUp_["agePreconditions"]
                            = conAndRate;
                    }
                    for(unsigned int l = 0; l < iqPre.size(); l++){
                        std::string condition = iqPre[l].asString();
                        std::pair<std::string, int> conAndRate(condition, rate);
                        parsed[i].markUp_["iqPreconditions"]
                            = conAndRate;
                    }
                    for(unsigned int l = 0; l < linkSus.size(); l++){
                        std::string condition = linkSus[l].asString();
						std::pair<std::string, int> conAndRate(condition, rate);
                        parsed[i].markUp_["linkSuspicion"] = conAndRate;
                    }
                    for(unsigned int l = 0; l < personalPre.size(); l++){
						std::string condition = personalPre[l].asString();
						std::pair<std::string, int> conAndRate(condition, rate);
                        parsed[i].markUp_["personalityPreconditions"]
                            = conAndRate;
                    }
                    for(unsigned int l = 0; l < relationship.size(); l++){
						std::string condition = relationship[l].asString();
						std::pair<std::string, int> conAndRate(condition, rate);
                        parsed[i].markUp_["relationship"] = conAndRate;
                    }
                }
            }
        }
    }
    return parsed;
}


