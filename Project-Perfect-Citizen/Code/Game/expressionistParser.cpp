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
#include "PipelineCharacter.h"

using namespace expr;

////////////////////////////////////////////////////////////////////////
///parsing out the JSON file
////////////////////////////////////////////////////////////////////////

Json::Value expr::parseExpressionistAsJson(std::string file) {
	Json::Reader reader;
	Json::Value value;
	std::ifstream doc(resourcePath() + file, std::ifstream::binary);
	reader.parse(doc, value);
	return value;
}

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

	
	std::string teststring = "";
	if (checkMarkUp(teststring) == false) { return std::make_pair("", false) ; } 



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
	std::string teststring = "";

	if (checkMarkUp(teststring) == false) return std::make_pair("", false);

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


bool makeComparison(const std::string& str1, const std::string& str2, const std::string& oper) {
	return true;
}

bool makeComparison(const int& int1, const int& int2, const std::string& oper) {
	return true;
}

bool checkMarkUpPreconditions(const Json::Value& markup, const ppc::PipelineCharacter& speaker) {
	std::vector<std::string> markupNames = markup.getMemberNames();
	for (size_t i = 0; i < markup.size(); ++i) {
		std::string currMark = markup[markupNames[i]].asString();
		std::string oper;
		std::string req;
		std::string value;

		for (size_t j = 0; j < markup[markupNames[i]].size(); ++j) {
			std::string currCond = markup[markupNames[i]][j].asString();
			req = currCond.substr(0, currCond.find_first_of(" "));
			oper = currCond.substr(currCond.find_first_of(" ") + 1, currCond.find_last_of(" "));
			value = currCond.substr(currCond.find_last_of(" ") + 1, std::string::npos);

			if (currMark == "agePreconditions") {
				if (makeComparison(speaker.getAge(), std::stoi(value), oper) == false) return false;
			}
			else if (currMark == "contentType"){ 
				//unused currently
			}
			else if (currMark == "iqPreconditions") {
				if (makeComparison(speaker.getIQ(), std::stoi(value), oper) == false) return false;
			}
			else if (currMark == "linkSuspicion") {
				//unused currently
			}
			else if (currMark == "personalityPreconditions") {
				//get specific personality trait
			}
			else if (currMark == "relationshipType") {
				//unused currently
			}
		}
	}
	
	return true;
}