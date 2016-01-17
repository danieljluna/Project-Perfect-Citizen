#pragma once

//Update Component 

///////////////////////////////////////////////////////////////////
/// @brief The base class for all components that update Entities
///	@details New components which revolve around updating the
///	data/fields of Entities inheirit from this class. Components 
///	inheirting from this class must define the virtual function:
/// void update(sf::Time deltaTime). 
/// @todo Add inheritance from Component; Add connection to Entity
///////////////////////////////////////////////////////////////////
class UpdateComponent {

public:
	/////////////////////////////////////////////////////////////
	/// @brief The component updates its Entity when it is called.
	///
	/// @details The update function of all update components are
	/// called after the game loop Input phase. After inputs are read,
	/// the Entity sends messages to update components (e.g. whether a
	/// collision has occurred, a key is pressed, etc.), and update is
	/// called when desired inputs have occurred.
	///
	/// @param in deltaTime Argument which states the time 
	/// required from the last frame to be processed. The arguement
	/// is required to have updates be independent of processor speed.
	/// deltaTime can be converted from sf::Time to seconds by doing:
	/// deltaTime.asSeconds().
	///
	/// @param out None
	///
	/// @post Effect of update should vary based on the 
	/// component defining it.
	///
	/// @return void
	/////////////////////////////////////////////////////////
	virtual void update(sf::Time deltaTime) = 0; 
};