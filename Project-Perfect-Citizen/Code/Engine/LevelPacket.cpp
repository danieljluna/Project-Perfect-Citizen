#include "LevelPacket.h"
#include <math.h>
#include <iostream>


void ppc::LevelPacket::push(int d, int i) {
	nextVec_.push_back({ d, i });
}

int ppc::LevelPacket::getNext(int i) {
	
	int d = -1;

	if (nextVec_.empty()) return d;

	int minDist = 100; //arbitrarily large value

	for (auto it = nextVec_.begin(); it != nextVec_.end(); ++it) {
        int n = std::abs(i - it->second);
		if (n <= minDist) {
			d = it->first;
			minDist = n;
		}
	}

	return d;
}
