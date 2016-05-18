#include "LevelPacket.h"


void ppc::LevelPacket::push(World::DesktopList d, int i) {
	nextVec_.push_back({ d,i });
}

ppc::World::DesktopList ppc::LevelPacket::getNext(int i) {
	
	World::DesktopList d = World::DesktopCount;

	if (nextVec_.empty()) return d;

	int min = 100; //arbitrarily large value

	for (auto it = nextVec_.begin(); it != nextVec_.end(); ++it) {
		int n = it->second;
		if (n <= min) d = it->first;
	}

	return d;
}
