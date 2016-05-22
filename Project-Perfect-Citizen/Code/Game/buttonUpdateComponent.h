#pragma once
#include <iostream>

#include <SFML/System/Vector2.hpp>

#include "../Engine/updateComponent.h"

namespace sf {
	class Time;
}

namespace ppc {
	class buttonRenderComponent;


///////////////////////////////////////////////////////////////////////
/// @brief Designated Update Component for a button
/// @author Alex Vincent
/// @details Updates render position of a button
///////////////////////////////////////////////////////////////////////

class buttonUpdateComponent : public ppc::UpdateComponent {

private:
	buttonRenderComponent& buttonToUpdate_;
	sf::Vector2f lastPosition_;
	

public:

	///////////////////////////////////////////////////////////////////////
	/// @brief Default constructor
	///////////////////////////////////////////////////////////////////////
	buttonUpdateComponent(buttonRenderComponent& bRC);


	///////////////////////////////////////////////////////////////////////
	/// @brief Default destructor
	///////////////////////////////////////////////////////////////////////
	~buttonUpdateComponent();

	///////////////////////////////////////////////////////////////////////
	/// @brief Sets the new button position
	///////////////////////////////////////////////////////////////////////
	void setButtonPosition(sf::Vector2f newPos);

	///////////////////////////////////////////////////////////////////////
	/// @brief Overridden update function of all update components.
	/// Calls renderPosition of the private button
	///////////////////////////////////////////////////////////////////////
	void update(sf::Time& deltaTime) override;

};


};

