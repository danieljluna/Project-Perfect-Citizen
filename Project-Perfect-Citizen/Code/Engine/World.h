#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

namespace ppc {

	class Desktop;

	///////////////////////////////////////////////////////////////////
	///@brief Class that handles Level transitions, saving/loading, etc
	///@author Nader Sleem
	///////////////////////////////////////////////////////////////////
	class World {

	private:

		sf::RenderWindow* screen_;
		ppc::Desktop* currDesktop_;

    public:

		World();
		World(sf::RenderWindow&);
		World(sf::RenderWindow&, ppc::Desktop&);

		~World();

      /////////////////////////////////////////////////////////////////
      // Setters
      /////////////////////////////////////////////////////////////////

		void setGameScreen(sf::RenderWindow&);

		void setCurrDesktop(ppc::Desktop&);

		sf::RenderWindow* getGameScreen();

		Desktop* getCurrDesktop();

		/////////////////////////////////////////////////////////////////
		// Desktop Manipulation
		/////////////////////////////////////////////////////////////////

		bool runDesktop(ppc::Desktop&);

		bool runCurrDesktop();


		friend std::istream& operator>>(std::istream& in, World& world);
	};

	// operator>>
	std::istream& operator>>(std::istream& in, World& world);
};