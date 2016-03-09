#include "PipelineLevelBuilder.h"

#include "../Engine/Edge.h"
#include "../Game/expressionistParser.hpp"


#include <random>
#include <ctime>
#include <map>
#include <string>

using namespace ppc;

std::map<std::string, bool> NAME_MAP = {
	{ "A", false },{ "B", false },{ "C", false },{ "D", false },
	{ "E", false },{ "F", false },{ "G", false },{ "H", false },
	{ "I", false },{ "J", false },{ "K", false },{ "L", false },
	{ "M", false },{ "N", false },{ "O", false },{ "P", false },
	{ "Q", false },{ "R", false },{ "S", false },{ "T", false },
	{ "U", false },{ "V", false },{ "W", false },{ "X", false },
	{ "Y", false },{ "Z", false }
};

const int LEVEL_ONE_NUM_NODES = 8;
const int LEVEL_ONE_NUM_EDGES = 8;
const int SMS_MESSAGES_PER_EDGE = 3;

Network* PipelineLevelBuilder::buildLevelOneNetworkSolution() {
	Network* myNetwork = new Network(LEVEL_ONE_NUM_NODES);
	
	std::map<std::string, bool> usednames = NAME_MAP;
	for (int i = 0; i < LEVEL_ONE_NUM_NODES;) {
		PipelineCharacter newpc;
		if (usednames[newpc.getSSN().substr(0, 1)] == false) {
			myNetwork->vert(i).setCharacter(newpc);
			usednames[newpc.getSSN().substr(0, 1)] = true;
			++i;
			//add char to database here I think
		}
	}

	Json::Value exprGrammar = expr::ExpressionistParser::parseExpressionistAsJson("smsPipeline.json");

	populateLevelEdges(0, (LEVEL_ONE_NUM_NODES - 1) / 2,(LEVEL_ONE_NUM_EDGES) / 2, 
		*myNetwork, 0, exprGrammar);

	populateLevelEdges((LEVEL_ONE_NUM_NODES) / 2, LEVEL_ONE_NUM_NODES - 1,
		LEVEL_ONE_NUM_EDGES / 2, *myNetwork, 1, exprGrammar);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, (LEVEL_ONE_NUM_NODES - 1)/2);

	//int first = std::rand() % ((LEVEL_ONE_NUM_NODES - 1) / 2);
	//int second = std::rand() % ((LEVEL_ONE_NUM_NODES) / 2) + (LEVEL_ONE_NUM_NODES - 1) / 2;
	unsigned int first = dis(gen);
	unsigned int second = dis(gen) + LEVEL_ONE_NUM_NODES / 2;

	myNetwork->setCenter(first);

	if (first == second) second += 1;

	Edge thisedge;
	thisedge.setWeight(1);
	thisedge.setColorRed();
	addSmsMessagesToEdge(thisedge, SMS_MESSAGES_PER_EDGE, myNetwork->vert(first).getCharacter(),
		myNetwork->vert(second).getCharacter(), exprGrammar);

	myNetwork->setEdge(first, second, thisedge);
	myNetwork->setEdge(second, first, thisedge);
	return myNetwork;
}

//Goes through a range of vertices and populates them with random edges
//Useful for creating clusters of closely related nodes.  Set a susp
//value of 0 or 1 for all nodes, or use -1 to determine randomly.
void PipelineLevelBuilder::populateLevelEdges(int start, int end, int numEdges, 
	Network& net, int suspLevel, const Json::Value& exprGrammar) {
	int i = 0;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(start, end);
	while (i < numEdges) {
		//int first = std::rand() % (end - start + 1) + start;
		int first = dis(gen);
		//int second = std::rand() % (end - start + 1) + start;
		int second = dis(gen);
		if (first == second) {
			if (first == end) first = start;
			else first += 1;
		}
		if (net.isAdjacent(first, second)) continue;
		
		Edge thisedge;
		if (suspLevel == -1) {
			int weight = std::rand() % 1;
			thisedge.setWeight(weight);
			if (weight == 0) thisedge.setColorGreen();
			else thisedge.setColorRed();
		} 
		else {
			thisedge.setWeight(suspLevel);
			if (suspLevel == 0) thisedge.setColorGreen();
			else thisedge.setColorRed();
		}

		addSmsMessagesToEdge(thisedge, SMS_MESSAGES_PER_EDGE, net.vert(first).getCharacter(),
			net.vert(second).getCharacter(), exprGrammar);

		net.setEdge(first, second, thisedge);
		net.setEdge(second, first, thisedge);
		++i;
	}

}

void PipelineLevelBuilder::addSmsMessagesToEdge(Edge& anEdge, unsigned int numMessages, const PipelineCharacter& sender, 
	const PipelineCharacter& receiver, const Json::Value& exprGrammar) {

	for (unsigned int i = 0; i < numMessages; ++i) {
		std::string exprOutput = expr::ExpressionistParser::expressWithJson(exprGrammar, sender);

		std::vector<std::string> withmeta;
		std::string exprOutputSub;

		int numloops = 0;
		while (exprOutput.length() > 0) {
			if (numloops % 2 == 0) {
				withmeta.push_back("FROM:");
				withmeta.push_back(sender.getSSN());
				withmeta.push_back("TO:");
				withmeta.push_back(receiver.getSSN());
				withmeta.push_back("\n");
			}
			else {
				withmeta.push_back("FROM:");
				withmeta.push_back(receiver.getSSN());
				withmeta.push_back("TO:");
				withmeta.push_back(sender.getSSN());
				withmeta.push_back("\n");
			}
			exprOutputSub = exprOutput.substr(0, exprOutput.find_first_of('%'));
			while (exprOutputSub.length() > 0) {
				size_t firstSpace = exprOutputSub.find_first_of(' ');
				if (firstSpace < string::npos) {
					withmeta.push_back(exprOutputSub.substr(0, firstSpace));
					exprOutputSub = exprOutputSub.substr(firstSpace + 1, std::string::npos);
				}
				else {
					withmeta.push_back(exprOutputSub);
					exprOutputSub = "";
				}
			}
			if (exprOutput.find_first_of('%') < std::string::npos) {
				exprOutput = exprOutput.substr(exprOutput.find_first_of('%'), std::string::npos);
			}
			else {
				exprOutput = "";
			}

			++numloops;
		}
		anEdge.pushSmsData(withmeta);
	}
}