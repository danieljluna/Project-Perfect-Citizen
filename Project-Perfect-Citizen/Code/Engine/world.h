//World.h
// Nader Sleem
#pragma once

#include <vector>
#include "desktop.h"
using namespace std;

namespace ppc {


///////////////////////////////////////////////////////////////////////
/// @brief Holds the Desktops of a level & all of the created worlds.
/// @details A World holds at most 5 desktops and Worlds store
/// themselves in the Worlds vector, which contains all the Worlds
/// created. Worlds are NOT Entities, they are just the system used
/// to contain/load levels, which are Desktops.
/// @author Nader Sleem
/// @todo Add functionallity for parsing save data.
//////////////////////////////////////////////////////////////////////
	class World {

//////////////////////////////////////////////////////////////////////
// PRIVATE FIELD
//////////////////////////////////////////////////////////////////////
	private:

//////////////////////////////////////////////////////////////////////
/// @brief Max amount of Desktops a World should contain
//////////////////////////////////////////////////////////////////////
		static const size_t MAX_DESKTOP_COUNT = 5;

//////////////////////////////////////////////////////////////////////
/// @brief Array that holds the Desktops of a World
//////////////////////////////////////////////////////////////////////
		Desktop* desktops_[MAX_DESKTOP_COUNT];

//////////////////////////////////////////////////////////////////////
/// @brief The number of Desktops managed by the World. Also the
///	size of desktops_.
//////////////////////////////////////////////////////////////////////
		size_t desktopCount_ = 0;

//////////////////////////////////////////////////////////////////////
/// @brief The index of a World in the World vector
//////////////////////////////////////////////////////////////////////
		size_t worldIndex;
	
///////////////////////////////////////////////////////////////////////
// PUBLIC FIELD
///////////////////////////////////////////////////////////////////////
	public:
//////////////////////////////////////////////////////////////////////
/// @brief The static vector that holds all Worlds instantiated
//////////////////////////////////////////////////////////////////////
		static vector<World*> worldsVector;

//////////////////////////////////////////////////////////////////////
/// @breif World Ctor
/// @details Initializes the Desktop pointer array to Null. Also
///		adds the constructed World to the Worlds vector.
//////////////////////////////////////////////////////////////////////
		World();

		// No copying allowed
		World(const World& other) = delete;

//////////////////////////////////////////////////////////////////////
/// @brief World Dtor
/// @details Removes the World of the World vector.
/// @todo Ask about the Dtor during meeting
//////////////////////////////////////////////////////////////////////
		~World();

//////////////////////////////////////////////////////////////////////
/// @brief Return how many Desktops this World contains
/// @return Return how many Desktops this World contains
//////////////////////////////////////////////////////////////////////
		size_t desktopCount() const;

//////////////////////////////////////////////////////////////////////
/// @brief Returns the Desktop at the specified index
/// @pre 0 <= index < desktopCount()
/// @param [in] index The index to be returned
/// @return If the index is valid, returns a pointer to the desired
///	Desktop. Otherwise, nullptr.
//////////////////////////////////////////////////////////////////////
		Desktop* getDesktop(int index) const;

//////////////////////////////////////////////////////////////////////
/// @brief Returns the index of a specified Desktop
/// @param [in] d The pointer to a desired Desktop.
/// @return If the Desktop desired is in the World, then its index is
///	returned. Otherwise, -1 is returned. If nullptr was used, then
///	-1 is returned.
//////////////////////////////////////////////////////////////////////
		int getIndex(Desktop* d);
		
//////////////////////////////////////////////////////////////////////
/// @brief Adds a Desktop to the World
/// @param [in] d The pointer of the Desktop to be added.
/// @return The index of the newly added Desktop. If no more Desktops
///		can fit, then the value of -1 is returned.
/// @post A Desktop is added, desktopCount() increases by 1
/// @todo Update based on Desktop implementation
//////////////////////////////////////////////////////////////////////
		int addDesktop(Desktop* d);

//////////////////////////////////////////////////////////////////////
/// @brief Removes a Desktop 
/// @details If the Desktop is not contained by World, nothing occurs.
/// @param [in] d A pointer to a Desktop
/// @post A Desktop is removed (not deleted), 
///	desktopCount() decreases by 1
/// @todo Update based on Desktop implementation
//////////////////////////////////////////////////////////////////////
		void removeDesktop(Desktop* d);

//////////////////////////////////////////////////////////////////////
/// @brief Removes a Desktop 
/// @details If the Desktop is not contained by World, nothing occurs
/// @param [in] index The index of the Desktop to be removed
/// @pre 0 <= index < desktopCount()
/// @post A Desktop is removed (not deleted), 
///		desktopCount() decreases by 1
/// @todo Update based on Desktop implementation
//////////////////////////////////////////////////////////////////////
		void removeDesktop(int index);

		//todo: add functionality to deal with save data


	};
};

