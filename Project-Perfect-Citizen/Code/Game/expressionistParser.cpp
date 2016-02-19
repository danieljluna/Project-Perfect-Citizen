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
//#include "../Library/json/json.h"
#include <iostream>
#include <fstream>
#include <map>
#include <random>
#include <list>
#include <cstddef>

using namespace expr;

std::string expr::expressWithJson(const Json::Value& exprOutput) {
	size_t i = 0;		
	Json::Value nonTerminalObj = exprOutput["nonterminals"];
	std::vector<std::string> terminalNames = nonTerminalObj.getMemberNames();
	for (; i < exprOutput["nonterminals"].size(); ++i) {
		if (exprOutput["nonterminals"][terminalNames[i]]["deep"].asBool() == true) break;
	}

	std::pair<std::string, bool> result = expandWithJson(exprOutput, exprOutput["nonterminals"][terminalNames[i]]);
	if (result.second == true) return result.first;

	return "";


}

std::pair<std::string, bool> expr::expandWithJson(const Json::Value& exprOutput, const Json::Value& symbol) {

	if (symbol["complete"].asBool() == false) return std::make_pair("", false);

	
	
	// if (checkMarkUp(speaker?) == false) { return false; } 



	std::vector<Json::Value> unvisited;

	for (size_t i = 0; i < symbol["rules"].size(); ++i) {
		Json::Value rule = symbol["rules"][i];
		unvisited.push_back(rule);
	}

	std::random_device rd;
	std::mt19937 gen(rd());

	int unvsize = unvisited.size();
	while (unvsize > 0) {
		int totalAppRate = 0;
		for (size_t i = 0; i < unvisited.size(); ++i) {
			totalAppRate += unvisited[i]["app_rate"].asInt();
		}

		std::uniform_int_distribution<> appd(1, totalAppRate);
		int currAppRate = appd(gen);
		size_t i = 0;
		for (; i < unvisited.size(); ++i) {
			currAppRate -= unvisited[i]["app_rate"].asInt();
			if (currAppRate <= 0) {
				std::pair<std::string, bool> fireResult = fireWithJson(exprOutput, unvisited[i]);
				if (fireResult.second == true) {
					return fireResult;
				}
			}
		}
		unvisited.erase(unvisited.begin() + i - 1);
		unvsize = unvisited.size();
	}

	return std::make_pair("", false);

}

size_t trimBraces(std::string& str) {
	size_t origLen = str.length();
	for (size_t i = 0; i < origLen; ++i) {
		size_t firstLetter = str.find_first_not_of('[');
		if (firstLetter == 0) return i;

		str.erase(0, 1);
		str.erase(str.length() - 1, 1);
	}
	return std::string::npos;
}

std::pair<std::string, bool> expr::fireWithJson(const Json::Value& exprOutput, const Json::Value& rule) {
	std::string result = "";

	//Check validity of markup, if invalid, return make_pair(result, false);

	//go through all strings in expansion
	for (size_t i = 0; i < rule["expansion"].size(); ++i) {
		std::string currExp = rule["expansion"][i].asString();
		size_t braceCount = trimBraces(currExp);
		if (braceCount == 0) {
			//this is just a string, append it to the result
			result += currExp;
		} else if (braceCount == 1) {
			//this is a run time variable that needs to be substituted for, otherwise treated as a string
			//do replacement for system/run time variable
		} else if (braceCount == 2) {
			Json::Value newExp = exprOutput["nonterminals"][currExp];
			//recursively expands upon a new non terminal symbol (newExp), yielding a valid result if one is possible
			std::pair<std::string, bool> subResult = expandWithJson(exprOutput, newExp);
			if (subResult.second == true) result += subResult.first;
			
			//if there were no valid expansions, this rule cannot be completed
			else return std::make_pair("", false);
		}
		else {
			//something was wrong in the exprOutput
			return std::make_pair("ERROR", false);
		}

	}


	return std::make_pair(result, true);
}


////////////////////////////////////////////////////////////////////////
///parsing out the JSON file returning a vector of the class
////////////////////////////////////////////////////////////////////////

Json::Value expr::parseExpressionistAsJson(std::string file) {
	Json::Reader reader;
	Json::Value value;
	std::ifstream doc(resourcePath() + file, std::ifstream::binary);
	reader.parse(doc, value);
	return value;
}

/*
DEPRECATED
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
            
			parsed[i].rules_ = expressionObj["rules"];

			parsed[i].jmarkUp_ = expressionObj["markup"];
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
*/


