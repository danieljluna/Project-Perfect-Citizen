#pragma once


namespace ppc {


	class Desktop;


	class World {
	private:

		static const size_t maxDesktopCount = 5;
		Desktop* desktops_[maxDesktopCount];
		size_t desktopCount_;

	public:

		World();
		World(const World& other) = delete;
		~World();





	};
};

