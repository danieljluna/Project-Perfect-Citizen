#include "PipelineLevelBuilder.h"

#include "../Engine/Edge.h"

#include <random>
#include <ctime>

using namespace ppc;

const int LEVEL_ONE_NUM_NODES = 8;
const int LEVEL_ONE_NUM_EDGES = 8;

Network PipelineLevelBuilder::buildLevelOneNetworkSolution() {
	Network myNetwork(LEVEL_ONE_NUM_NODES);
	for (int i = 0; i < LEVEL_ONE_NUM_NODES; ++i) {
		Vertex& thisvert = myNetwork.vert(i);
		PipelineCharacter newpc;
		thisvert.pipechar = newpc;
		//add char to database here I think
	}

	populateLevelEdges(0, LEVEL_ONE_NUM_NODES / 2, LEVEL_ONE_NUM_EDGES / 2, myNetwork, 0);

	populateLevelEdges(LEVEL_ONE_NUM_NODES / 2, LEVEL_ONE_NUM_NODES,
		LEVEL_ONE_NUM_EDGES / 2, myNetwork, 1);

	int first = std::rand() % (LEVEL_ONE_NUM_NODES / 2);
	int second = std::rand() % (LEVEL_ONE_NUM_NODES / 2) + LEVEL_ONE_NUM_NODES / 2;

	if (first == second) second += 1;

	Edge thisedge;
	thisedge.weight = 1;

	myNetwork.setEdge(first, second, thisedge);
	myNetwork.setEdge(second, first, thisedge);
	return myNetwork;
}

//Goes through a range of vertices and populates them with random edges
//Useful for creating clusters of closely related nodes.  Set a susp
//value of 0 or 1 for all nodes, or use -1 to determine randomly.
void populateLevelEdges(int start, int end, int numEdges, Network& net, int suspLevel) {
	int i = 0;
	std::srand(std::time(0));
	while (i < numEdges) {
		int first = std::rand() % (end - start) + start;
		int second = std::rand() % (end - start) + start;
		if (first == second) {
			if (first == end) first = start;
			else first += 1;
		}
		if (net.isAdjacent(first, second)) continue;
		
		Edge thisedge;
		if (suspLevel == -1) thisedge.weight = std::rand() % 1;
		else thisedge.weight = suspLevel;

		net.setEdge(first, second, thisedge);
		net.setEdge(second, first, thisedge);
		++i;
	}

}