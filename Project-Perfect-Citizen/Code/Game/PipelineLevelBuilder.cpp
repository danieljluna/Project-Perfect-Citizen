#include "PipelineLevelBuilder.h"

#include "../Engine/Edge.h"
#include "../Game/expressionistParser.hpp"


#include <random>
#include <ctime>

using namespace ppc;

const int LEVEL_ONE_NUM_NODES = 8;
const int LEVEL_ONE_NUM_EDGES = 8;
const int SMS_MESSAGES_PER_EDGE = 3;

Network* PipelineLevelBuilder::buildLevelOneNetworkSolution() {
	Network* myNetwork = new Network(LEVEL_ONE_NUM_NODES);
	for (int i = 0; i < LEVEL_ONE_NUM_NODES; ++i) {
		PipelineCharacter newpc;
		myNetwork->vert(i).setCharacter(newpc);
		//add char to database here I think
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
			int weight = static_cast<float>(std::rand() % 1);
			thisedge.setWeight(weight);
			if (weight == 0) thisedge.setColorGreen();
			else thisedge.setColorRed();
		} 
		else {
			thisedge.setWeight(static_cast<float>(suspLevel));
			if (suspLevel == 0) thisedge.setColorGreen();
			else thisedge.setColorRed();
		}

		for (int i = 0; i < SMS_MESSAGES_PER_EDGE; ++i) {
			addSmsMessageToEdge(thisedge, net.vert(first).getCharacter(),
				net.vert(second).getCharacter(), exprGrammar);
		}

		net.setEdge(first, second, thisedge);
		net.setEdge(second, first, thisedge);
		++i;
	}

}

void PipelineLevelBuilder::addSmsMessageToEdge(Edge& anEdge, const PipelineCharacter& sender, 
	const PipelineCharacter& receiver, const Json::Value& exprGrammar) {
	std::string exprOutput = expr::ExpressionistParser::expressWithJson(exprGrammar, sender);
	
	std::string withmeta = "";

	int numloops = 0;
	while (exprOutput.length() > 0) {
		if (numloops % 2 == 0) {
			withmeta += "FROM: " + sender.getSSN() + " TO: " + receiver.getSSN() + "\n";
		}
		else {
			withmeta += "FROM: " + receiver.getSSN() + " TO: " + sender.getSSN() + "\n";
		}
		withmeta += exprOutput.substr(0, exprOutput.find_first_of('%'));
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