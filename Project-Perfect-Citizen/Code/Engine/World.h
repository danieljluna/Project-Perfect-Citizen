#pragma once

#include <SFML/Graphics.hpp>
//#include "desktop.h"

namespace ppc {

	class Desktop;

	//TODO: Add a State struct (?)

	///////////////////////////////////////////////////////////////////
	///@brief Class that handles Level transitions, saving/loading, etc
	///@author Nader Sleem
	///////////////////////////////////////////////////////////////////
	class World {

	private:

		sf::RenderWindow* screen;
		//ppc::Desktop* currDesktop;

	public:

		World();
		World(sf::RenderWindow&);
		~World();

		void setGameScreen(sf::RenderWindow&);

		bool runDesktop(ppc::Desktop&);

	};
};