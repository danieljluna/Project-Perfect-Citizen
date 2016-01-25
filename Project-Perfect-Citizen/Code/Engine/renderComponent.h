#ifndef PPC_CMPNT_RENDER
#define PPC_CMPNT_RENDER

#include "Component.h"
#include <SFML/Graphics.hpp>
#include <vector>

///////////////////////////////////////////////////////////////////////
/// @brief The base class for all components that need to be rendered!
/// @details Remember, any class that is a child of RenderComponent 
///     must implement void draw(sf::RenderTarget& target, 
///     sf::RenderStates states). 
///////////////////////////////////////////////////////////////////////

class RenderComponent : public ppc::Component, public sf::Drawable {
protected:

    ///////////////////////////////////////////////////////////////////
	/// @brief draw function inherited from sf::Drawable
	/// @details Every class that inheirits from RenderComponent MUST 
    /// define draw(sf::RenderTarget& target, sf::RenderStates states) 
    /// as it is an abstract function.
    ///
	/// @param target This is almost always going to be a 
    /// sf::renderWindow. 
    /// @param states This is used to dictate certain states that the 
    /// object can be rendered in. For now this can be safely "ignored"
    /// Just created a RenderStates object and shove it in there. 
    ///////////////////////////////////////////////////////////////////
	virtual void draw(sf::RenderTarget& target, 
                      sf::RenderStates states) const = 0;


};

#endif
