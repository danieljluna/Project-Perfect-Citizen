//
//  expressionistParser.cpp
//  Project-Perfect-Citizen
//
//  Created by Brandon Gomez on 2/15/16.
//  Copyright © 2016 Hyperfocus Games. All rights reserved.
//

#include "../ResourceDef.h"
#include "../Engine/debug.h"
#include "expressionistParser.hpp"
//#include "../Library/json/json.h"
#include <iostream>
#include <fstream>
#include <map>
#include <random>
#include <list>
#include <cstddef>

#include "../Game/PipelineCharacter.h"
#include "../Engine/Edge.h"

using namespace expr;

////////////////////////////////////////////////////////////////////////
///parsing out the JSON file
////////////////////////////////////////////////////////////////////////

Json::Value expr::ExpressionistParser::parseExpressionistAsJson(std::string file) {
	Json::Reader reader;
	Json::Value value;
	std::ifstream doc(resourcePath() + file, std::ifstream::binary);
	if (!doc.good()) throw std::runtime_error("Expressionist: File not found.");
	reader.parse(doc, value);
	return value;
}

std::string expr::ExpressionistParser::expressWithJson(const Json::Value& exprOutput, const ppc::PipelineCharacter& speaker, const ppc::Edge& link) {
	size_t i = 0;		
	Json::Value nonTerminalObj = exprOutput["nonterminals"];
	std::vector<std::string> terminalNames = nonTerminalObj.getMemberNames();
	for (; i < exprOutput["nonterminals"].size(); ++i) {
		if (exprOutput["nonterminals"][terminalNames[i]]["deep"].asBool() == true) break;
	}

	std::pair<std::string, bool> result = expandWithJson(exprOutput, exprOutput["nonterminals"][terminalNames[i]], speaker, link);
	if (result.second == true) return result.first;

	return "";


}

std::pair<std::string, bool> expr::ExpressionistParser::expandWithJson(const Json::Value& exprOutput, const Json::Value& symbol, const ppc::PipelineCharacter& speaker, const ppc::Edge& link) {

	if (symbol["complete"].asBool() == false) return std::make_pair("", false);

	
	std::string teststring = "";
	if (checkMarkUpPreconditions(symbol["markup"], speaker, link) == false) { return std::make_pair("", false) ; } 



	std::vector<Json::Value> unvisited;

	for (unsigned int i = 0; i < symbol["rules"].size(); ++i) {
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
				std::pair<std::string, bool> fireResult = fireWithJson(exprOutput, unvisited[i], speaker, link);
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

std::pair<std::string, bool> expr::ExpressionistParser::fireWithJson(const Json::Value& exprOutput, const Json::Value& rule, const ppc::PipelineCharacter& speaker, const ppc::Edge& link) {
	std::string result = "";
	std::string teststring = "";

	if (checkMarkUpPreconditions(rule["markup"], speaker, link) == false) {
		//std::cout << "Markup check failed in Fire." << std::endl;
		return std::make_pair("", false);
	}
	//std::cout << rule["expansion"][0].asString() << std::endl;

	//go through all strings in expansion
	for (unsigned int i = 0; i < rule["expansion"].size(); ++i) {
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
			std::pair<std::string, bool> subResult = expandWithJson(exprOutput, newExp, speaker, link);
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
	//std::cout << "strcmp: " << str1 << oper << str2 << std::endl;
	
	if (oper.compare("==") == 0) {
		return (str1.compare(str2) == 0);
	}
	else if (oper.compare("!=") == 0) {
		return (str1.compare(str2) != 0);
	}
	return false;
}

bool makeComparison(const int& int1, const int& int2, const std::string& oper) {
	//std::cout << "IntComp: " << int1 << oper << int2 << std::endl;
	//std::cout << "oper = \"" << oper << "\"" << std::endl;
	if (oper.compare("==") == 0) {
		return int1 == int2;
	} 
	else if (oper.compare(">=") == 0) {
		return int1 >= int2;
	}
	else if (oper.compare(">") == 0) {
		return int1 > int2;
	}
	else if (oper.compare("<=") == 0) {
		return int1 <= int2;
	}
	else if (oper.compare("<") == 0) {
		return int1 < int2;
	}
	else if (oper.compare("!=") == 0) {
		return int1 != int2;
	}

	return false;
}

bool expr::ExpressionistParser::checkMarkUpPreconditions(const Json::Value& markup, const ppc::PipelineCharacter& speaker, const ppc::Edge& link) {
	std::vector<std::string> markupNames = markup.getMemberNames();
	for (size_t i = 0; i < markup.size(); ++i) {
		Json::Value currMark = markup[markupNames[i]];
		std::string oper;
		//std::string req;
		std::string value;

		for (unsigned int j = 0; j < currMark.size(); ++j) {
			std::string currCond = currMark[j].asString();
			//std::cout << "CurrCond = " << currCond << " markupNames[i] = " << markupNames[i] << std::endl;
			size_t firstspace = currCond.find_first_of(" ");
			size_t lastspace = currCond.find_last_of(" ");
			//req = currCond.substr(0, firstspace);
			if (firstspace == lastspace) {
				oper = currCond.substr(0, firstspace);
			}
			else {
				oper = currCond.substr(firstspace + 1, (currCond.find_last_of(" ") - firstspace) - 1);
			}
			value = currCond.substr(currCond.find_last_of(" ") + 1, std::string::npos);
			if (markupNames[i].compare("agePreconditions") == 0) {
				//std::cout << "Making Age Comparison" << std::endl;

				if (makeComparison(speaker.getAge(), std::stoi(value), oper) == false) return false;
				continue;
			}
			else if (markupNames[i].compare("linkSuspicion") == 0) {
				if (link.getWeight() == 1) {
					if (makeComparison("Ambiguous", value, "==")) continue;
					if (makeComparison("Suggestive", value, "==")) continue;
					if (makeComparison("ClearlySuspicious", value, "==")) continue;
					return false;
				}
				else {
					if (makeComparison("ClearlyClean", value, "==")) continue;
					if (makeComparison("SlightlySuspicious", value, "==")) continue;
					//if (makeComparison("Ambiguous", value, "==")) continue;
					return false;
				}
				continue;
			}
			else if (markupNames[i].compare("relationship") == 0) {
				//unused currently
				//needs target as well as speaker? or just link?
				continue;
			}
			else if (markupNames[i].compare("assertiveness") == 0) {
				if (makeComparison(speaker.getPersAssertive(), std::stoi(value), oper) == false) return false;
				continue;
			}
			else if (markupNames[i].compare("directness") == 0) {
				if (makeComparison(speaker.getPersDirectness(), std::stoi(value), oper) == false) return false;
				continue;
			}
			else if (markupNames[i].compare("jerk") == 0) {
				if (makeComparison(speaker.getPersJerk(), std::stoi(value), oper) == false) return false;
				continue;
			}
		}
	}
	
	return true;
}