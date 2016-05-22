#pragma once

#include <map>
#include <string>

#include "../Engine/debug.h"


///////////////////////////////////////////////////////////////////////
/// @author Mark Biundo
/// @brief Builds procedurally generated PE levels based on a ruleset
/// @details This space is used for level design, containing several
///   handy functions for quickly building and modifying pipeline
///   extraction scenarios.
///////////////////////////////////////////////////////////////////////
namespace Json {
	class Value;
};

namespace ppc {
	class Network;
	class Edge;
	class PipelineCharacter;

class PipelineLevelBuilder {
public:
	static Network* buildTutorialOne();

	static Network* buildTutorialTwo();
	
	///////////////////////////////////////////////////////////////////
	/// @brief A function that builds the first (example) level of the
	///   pipeline extraction
	/// @param [out]  Network  a network solution used for the pipeline
	///                        level.  The player's work is compared
	///                        against this.
	///////////////////////////////////////////////////////////////////
	static Network* buildLevelOneNetworkSolution();

	static Network* buildLevelTwoANetworkSolution();
	static Network* buildLevelTwoBNetworkSolution();

	static Network* buildLevelThreeNetworkSolution();

	static Network* buildDefaultNetwork();

	static const std::map<std::string, int> LEVEL_MAP;

private:

	//static Network * initNetwork(int numnodes);

	static Network* LevelTwoWithOption(std::string file);

	static void populateLevelEdges(int start, int end, int numEdges, 
		Network& net, int suspLevel, const Json::Value& exprGrammar);

	static void addSmsMessagesToEdge(Edge& anEdge, unsigned int numMessages, const PipelineCharacter& sender,
		const PipelineCharacter& receiver, const Json::Value& exprGrammar);

	static std::pair<int,int> designateCenter(unsigned int start, unsigned int end, Network & net);
	
	static void addEdge(int first, int second, Network & net, int suspLevel, const Json::Value & exprGrammar);

	static std::string trimWhiteSpace(std::string& str);

	static void populateEdgesBySet(const std::vector<std::pair<unsigned int, unsigned int>> set, Network& net, Json::Value& expr, int suspLevel);
};

};