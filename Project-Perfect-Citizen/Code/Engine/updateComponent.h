//Update Component 
// Nader Sleem
#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Component.h"

using namespace std;

namespace ppc {

	///////////////////////////////////////////////////////////////////
	/// @brief The base class for all components that update Entities
	///	@details New components which revolve around updating the
	///	data/fields of Entities inheirit from this class. Components 
	///	inheirting from this class must define the virtual function:
	/// void update(sf::Time deltaTime). 
	///////////////////////////////////////////////////////////////////
	class updateComponent : public ppc::Component {

	////////////////////////////////////////////////////////
	// PRIVATE FIELDS
	////////////////////////////////////////////////////////
	private:
		/////////////////////////////////////////////////////////////
		/// @brief Index of the component in the update vector
		/// @details Automatically set by the Ctor when
		/// the component is pushed into the vector
		/////////////////////////////////////////////////////////////
		size_t index;

	////////////////////////////////////////////////////////
	// PUBLIC FIELDS
	////////////////////////////////////////////////////////
	public:

		/////////////////////////////////////////////////////////////
		/// @brief Stores pointers to all existing update components.
		/// @details New components are added by the Ctor. Pointers
		/// in the vector are deleted by the Dtor when it is called.
		/////////////////////////////////////////////////////////////
		static vector<updateComponent*> updateVector;

		/////////////////////////////////////////////////////////////
		/// @brief Ctor for updateComponent
		/// @details Adds the newly created update component
		/// to the updateVector. 
		/////////////////////////////////////////////////////////////
		updateComponent();

		////////////////////////////////////////////////////////////
		/// @brief Dtor for updateComponent
		/// @details Calls removeElement with index as its argument,
		/// therefore having the component delete itself from
		/// the update vector.
		////////////////////////////////////////////////////////////
		virtual ~updateComponent();

		/////////////////////////////////////////////////////////////
		/// @brief Removes a component from updateComponent::updateVector
		/// @details Erases the component. The Dtor calls this.
		/// @param [in] [index] Index in the update vector. Should have
		/// been saved when it was added to the vector. Right when a
		/// component is added, its index should be: (size of the
		/// vector - 1 )
		/////////////////////////////////////////////////////////////
		void removeElement(int index);


		/////////////////////////////////////////////////////////////
		/// @brief The component updates its Entity when it is called.
		///
		/// @details The update function of all update components are
		/// called after the game loop Input phase. After inputs are read,
		/// the Entity sends messages to update components (e.g. whether
		/// a collision has occurred, a key is pressed, etc.), and update
		/// is called when desired inputs have occurred.
		///
		/// @param [in] deltaTime Time required from the last frame to
		/// be processed. Required to have updates be independent of 
		/// processor speed. Should be uses as deltaTime.asSeconds().
		///
		/// @post Effect of update should vary based on the 
		/// component defining it.
		///
		/// @return void
		/////////////////////////////////////////////////////////
		virtual void update(sf::Time deltaTime) = 0;
};
} //end of namespace


