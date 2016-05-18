#pragma once

#include <vector>
#include <utility>


namespace ppc {

	struct LevelPacket {

	//ppc::World::DesktopList iniCurr_;
	// first int corresponds to enum values,
	// second corresponds to score from file holder (smallest value is 1).
	std::vector<std::pair<int, int>> nextVec_;

	void push(int, int);
		
	int getNext(int);



	};

};