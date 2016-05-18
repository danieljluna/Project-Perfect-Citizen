#pragma once

#include <vector>
#include <utility>
#include "World.h"

namespace ppc {

	class LevelPacket {

	private:

		std::vector<std::pair<World::DesktopList, int>> nextVec_;

	public:

		void push(World::DesktopList, int);
		
		World::DesktopList getNext(int);

	};

};