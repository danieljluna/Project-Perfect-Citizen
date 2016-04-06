#pragma once

#include <SFML/Graphics.hpp>
//#include "desktop.h"

namespace ppc {

	class Desktop;

	//TODO: Add a State struct (?)
	struct State{
		//ID of the saved Desktop's builder
		//graph solution
		//saved password -- ???
		//checkpoints -- ???
		//received emails
		//player stats -- 
	};




	///////////////////////////////////////////////////////////////////
	///@brief Class that handles Level transitions, saving/loading, etc
	///@author Nader Sleem
	///////////////////////////////////////////////////////////////////
	class World {

	private:
      /////////////////////////////////////////////////////////////////
      // Private Variables
      /////////////////////////////////////////////////////////////////

		sf::RenderWindow* screen_;
		ppc::Desktop* currDesktop_;

	public:

		World();
		World(sf::RenderWindow&);
		~World();

		void setGameScreen(sf::RenderWindow&);

		bool runDesktop(ppc::Desktop&);

	};
};