#pragma once

#include <SFML/Graphics.hpp>
//#include "desktop.h"
#include <iostream>
#include <fstream>

namespace ppc {

	class Desktop;

	///////////////////////////////////////////////////////////////////
	///@brief Class that handles Level transitions, saving/loading, etc
	///@author Nader Sleem
	///////////////////////////////////////////////////////////////////
	class World {

	private:

		sf::RenderWindow* screen;
		ppc::Desktop* currDesktop;

	public:

		World();
		World(sf::RenderWindow&);
		World(sf::RenderWindow&, ppc::Desktop&);
		~World();

		void setGameScreen(sf::RenderWindow&);

		void setCurrDesktop(ppc::Desktop&);

		Desktop* getCurrDesktop();

		bool runDesktop(ppc::Desktop&);

		bool runCurrDesktop();

		// operator<< 
		friend std::ostream& operator<<(std::ostream& out, const World& world);

		// operator>>
		friend std::istream& operator>>(std::istream& in, const World& world);
	};
};