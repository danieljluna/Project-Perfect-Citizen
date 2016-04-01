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
const int LEVEL_ONE_NODES_LOW = (LEVEL_ONE_NUM_NODES - 1) / 2; // 0 - 3
const int LEVEL_ONE_NODES_HIGH = (LEVEL_ONE_NUM_NODES / 2);    // 4 - 7
const int SMS_MESSAGES_PER_EDGE = 1;

Network* PipelineLevelBuilder::buildLevelOneNetworkSolution() {
	Network* myNetwork = new Network(LEVEL_ONE_NUM_NODES);
	
	std::map<std::string, bool> usednames = NAME_MAP;
	//These characters are randomly generated here, but should be more
	//specific in practice
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

	//Fill random edges on low side - non suspicious
	populateLevelEdges(0, LEVEL_ONE_NODES_LOW, (LEVEL_ONE_NUM_EDGES) / 2, 
		*myNetwork, 0, exprGrammar);

	//Fill random edges on high side - suspicious
	populateLevelEdges(LEVEL_ONE_NODES_HIGH, LEVEL_ONE_NUM_NODES - 1,
		LEVEL_ONE_NUM_EDGES / 2, *myNetwork, 1, exprGrammar);

	std::pair<int, int> centerAndTarget = designateCenter(0, LEVEL_ONE_NODES_LOW, *myNetwork);
	myNetwork->setCenter(centerAndTarget.first);
	addEdge(centerAndTarget.first, centerAndTarget.second, *myNetwork, 1, exprGrammar);

	/*
	//Pick a random node to be the "center" from the first half of nodes
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, LEVEL_ONE_NODES_LOW);

	
	unsigned int first = 0;
	unsigned int numFirstEdges = 0;
	for (unsigned int i = 0; i < (LEVEL_ONE_NUM_NODES - 1) / 2; ++i) {
		unsigned int currNumEdges = 0;
		for (unsigned int j = 0; j < myNetwork->size(); ++j) {
			if (i == j) continue;
			if (myNetwork->isAdjacent(i, j)) {
				currNumEdges++;
			}
		}
		if (currNumEdges > numFirstEdges) {
			first = i;
			numFirstEdges = currNumEdges;
		}
	}

	unsigned int second = dis(gen) + LEVEL_ONE_NUM_NODES / 2;

	//experimental excuse magic number (a 3 here means center has minimum 4 edges)
	//this will be encapuslated as a function call if this method continues to be used
	int third = dis(gen) + LEVEL_ONE_NUM_NODES / 2;
	if (numFirstEdges < 3) {
		if (third == second) {
			third++;
			if (third > (LEVEL_ONE_NUM_NODES - 1)) third = LEVEL_ONE_NUM_NODES / 2;
		}

		unsigned int thirdEdgeCount = 0;
		for (unsigned int i = LEVEL_ONE_NUM_NODES / 2; i < LEVEL_ONE_NUM_NODES; ++i) {
			if (i == third) continue;
			if (myNetwork->isAdjacent(i, second)) ++thirdEdgeCount;
		}
		while (thirdEdgeCount >= numFirstEdges) {
			unsigned int vert = dis(gen) + LEVEL_ONE_NUM_NODES / 2;
			if (vert == third) continue;
			if (myNetwork->isAdjacent(third, vert)) {
				myNetwork->removeEdge(third, vert);
				myNetwork->removeEdge(vert, third);
				thirdEdgeCount--;
			}
		}

		Edge thisedge;
		thisedge.setWeight(1);
		thisedge.setColorRed();
		addSmsMessagesToEdge(thisedge, SMS_MESSAGES_PER_EDGE, myNetwork->vert(first).getCharacter(),
			myNetwork->vert(third).getCharacter(), exprGrammar);

		myNetwork->setEdge(first, third, thisedge);
		myNetwork->setEdge(third, first, thisedge);
	}
	
	unsigned int secondEdgeCount = 0;
	for (unsigned int i = LEVEL_ONE_NUM_NODES / 2; i < LEVEL_ONE_NUM_NODES; ++i) {
		if (i == second) continue;
		if (myNetwork->isAdjacent(i, second)) ++secondEdgeCount;
	}
	while (secondEdgeCount >= numFirstEdges) {
		unsigned int vert = dis(gen) + LEVEL_ONE_NUM_NODES / 2;
		if (vert == second) continue;
		if (myNetwork->isAdjacent(second, vert)) {
			myNetwork->removeEdge(second, vert);
			myNetwork->removeEdge(vert, second);
			secondEdgeCount--;
		}
	}

	myNetwork->setCenter(first);
	Edge thisedge;
	thisedge.setWeight(1);
	thisedge.setColorRed();
	addSmsMessagesToEdge(thisedge, SMS_MESSAGES_PER_EDGE, myNetwork->vert(first).getCharacter(),
		myNetwork->vert(second).getCharacter(), exprGrammar);

	myNetwork->setEdge(first, second, thisedge);
	myNetwork->setEdge(second, first, thisedge);

	for (unsigned int i = LEVEL_ONE_NUM_NODES / 2; i < LEVEL_ONE_NUM_NODES; ++i) {
		if (myNetwork->isAdjacent(i, first)) break;

		for (unsigned int j = i + 1; j < LEVEL_ONE_NUM_NODES; ++j) {
			if (myNetwork->isAdjacent(i, j)) break;
		}
		unsigned int othervert = dis(gen) + LEVEL_ONE_NUM_NODES / 2;
		if (othervert == second) {
			othervert++;
			if (othervert >= LEVEL_ONE_NUM_NODES) othervert = LEVEL_ONE_NUM_NODES / 2;
			if (othervert == third) {
				othervert++;
				if (othervert >= LEVEL_ONE_NUM_NODES) othervert = LEVEL_ONE_NUM_NODES / 2;
			}
		}
		Edge thisedge;
		thisedge.setWeight(1);
		thisedge.setColorRed();
		addSmsMessagesToEdge(thisedge, SMS_MESSAGES_PER_EDGE, myNetwork->vert(i).getCharacter(),
			myNetwork->vert(othervert).getCharacter(), exprGrammar);

		myNetwork->setEdge(i, othervert, thisedge);
		myNetwork->setEdge(othervert, i, thisedge);
	}
	*/

	return myNetwork;
}


// Finds a valid vertex in range [start, end] designates it as center,
// adds an edge between it and the other side of the graph
// Needs to be updated to reflect suspicion level if link suspicion is used
// for puzzle solving
std::pair<int, int> PipelineLevelBuilder::designateCenter(unsigned int start, unsigned int end, Network& net) {
	std::vector<unsigned int> vertEdgeCounts (net.size(), 0);
	for (unsigned int i = 0; i < net.size(); ++i) {
		unsigned int edgeCount = 0;
		for (unsigned int j = 0; j < net.size(); j++) {
			if (i == j) continue;
			if (net.isAdjacent(i, j)) {
				edgeCount++;
			}
		}
		vertEdgeCounts[i] = edgeCount;
	}

	std::vector<unsigned int> centerTargets;
	std::vector<unsigned int> strayNodes;
	unsigned int centerEdges = 0;
	for (unsigned int i = 0; i < net.size(); ++i) {
		if (i >= start && i <= end) {
			if (vertEdgeCounts[i] > centerEdges) {
				centerEdges = vertEdgeCounts[i];
				centerTargets.clear();
				centerTargets.push_back(i);
			}		
			if (vertEdgeCounts[i] == centerEdges) {
				centerTargets.push_back(i);
			}
		}

		if (vertEdgeCounts[i] == 0) {
			strayNodes.push_back(i);
		}
	}

	//Okay that edges are tied here, going to be adding one to center anyway
	unsigned int center = centerTargets[std::rand() % centerTargets.size()];


	//Needs to be updated to reflect suspicion level if link suspicion is used
	//for puzzle solving
	std::vector<unsigned int> validTargets;
	std::vector<unsigned int> needsEdgeRemoved;
	for (unsigned int i = 0; i < net.size(); ++i) {
		if (i == center) continue;
		if (vertEdgeCounts[i] > centerEdges) needsEdgeRemoved.push_back(i);
		if (i < start || i > end) {
			if (vertEdgeCounts[i] < centerEdges) validTargets.push_back(i);
		}
	}
	
	for (unsigned int i = 0; i < needsEdgeRemoved.size(); ++i) {
		//remove edges
	}

	unsigned int target = validTargets[std::rand() % validTargets.size()];

	return std::make_pair(center, target);

}

void PipelineLevelBuilder::addEdge(int first, int second, Network& net, int suspLevel, const Json::Value& exprGrammar) {
	Edge thisedge;
	//Color here is unused by the player, but is useful for checking
	//correctness of a solution
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
		//Pick two random nodes, if they have an edge between them
		//retry, otherwise create one

		int first = dis(gen);
		int second = dis(gen);

		if (first == second) {
			if (first == end) first = start;
			else first += 1;
		}
		if (net.isAdjacent(first, second)) continue;
		
		addEdge(first, second, net, suspLevel, exprGrammar);
		++i;
	}

}


//Using the link information contained in anEdge, as well as the sender's details,
//Build an Expression, format it for display, and append each word to a vector
void PipelineLevelBuilder::addSmsMessagesToEdge(Edge& anEdge, unsigned int numMessages, const PipelineCharacter& sender, 
	const PipelineCharacter& receiver, const Json::Value& exprGrammar) {

	for (unsigned int i = 0; i < numMessages; ++i) {
		std::string exprOutput = expr::ExpressionistParser::expressWithJson(exprGrammar, sender, anEdge);

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
				if (firstSpace < std::string::npos) {
					withmeta.push_back(exprOutputSub.substr(0, firstSpace));
					exprOutputSub = exprOutputSub.substr(firstSpace + 1, std::string::npos);
				}
				else {
					withmeta.push_back(exprOutputSub);
					exprOutputSub = "";
				}
			}
			if (exprOutput.find_first_of('%') < std::string::npos) {
				exprOutput = exprOutput.substr(exprOutput.find_first_of('%') + 1, std::string::npos);
				withmeta.push_back("\n");
			}
			else {
				exprOutput = "";
				withmeta.push_back("\n");
			}

			++numloops;
		}
		anEdge.pushSmsData(withmeta);
	}
}