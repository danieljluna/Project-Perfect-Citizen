#include "PipelineLevelBuilder.h"

#include "../Engine/Edge.h"

#include <random>
#include <ctime>

using namespace ppc;

const int LEVEL_ONE_NUM_NODES = 8;
const int LEVEL_ONE_NUM_EDGES = 8;

Network* PipelineLevelBuilder::buildLevelOneNetworkSolution() {
	Network* myNetwork = new Network(LEVEL_ONE_NUM_NODES);
	for (int i = 0; i < LEVEL_ONE_NUM_NODES; ++i) {
		PipelineCharacter newpc;
		myNetwork->vert(i).setCharacter(newpc);
		//add char to database here I think
	}

	populateLevelEdges(0, (LEVEL_ONE_NUM_NODES - 1) / 2,(LEVEL_ONE_NUM_EDGES) / 2, *myNetwork, 0);

	populateLevelEdges((LEVEL_ONE_NUM_NODES) / 2, LEVEL_ONE_NUM_NODES - 1,
		LEVEL_ONE_NUM_EDGES / 2, *myNetwork, 1);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, (LEVEL_ONE_NUM_NODES - 1)/2);

	//int first = std::rand() % ((LEVEL_ONE_NUM_NODES - 1) / 2);
	//int second = std::rand() % ((LEVEL_ONE_NUM_NODES) / 2) + (LEVEL_ONE_NUM_NODES - 1) / 2;
	int first = dis(gen);
	int second = dis(gen) + LEVEL_ONE_NUM_NODES / 2;


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
void PipelineLevelBuilder::populateLevelEdges(int start, int end, int numEdges, Network& net, int suspLevel) {
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


		net.setEdge(first, second, thisedge);
		net.setEdge(second, first, thisedge);
		++i;
	}

}