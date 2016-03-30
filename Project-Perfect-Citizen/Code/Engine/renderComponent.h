#ifndef PPC_CMPNT_RENDER
#define PPC_CMPNT_RENDER

#include "Component.h"
#include <SFML/Graphics/Drawable.hpp>


namespace ppc {

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
	/// @param target The target to Render to.
    /// @param states The state passed for Rendering.
    ///////////////////////////////////////////////////////////////////
	virtual void draw(sf::RenderTarget& target, 
                      sf::RenderStates states) const = 0;


};


};  //End namespace ppc


#endif
