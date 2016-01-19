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
private:
	int tempVar;

public:

    ///////////////////////////////////////////////////////////////////
    /// @brief This bad boy is a vector that contains pointers to 
    /// RenderComponents. Whenever an object is created to be rendered, 
    /// be sure its added to this vector. 
    ///////////////////////////////////////////////////////////////////
    static std::vector<RenderComponent*> renderVector;

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


    ///////////////////////////////////////////////////////////////////
	/// @brief NOT COMPLETELY TESTED, DO NOT USE
	/// @details Part of the destructor for renderComponent. Removes 
    /// the specified element from RenderComponent::renderVector
	/// @param index is the index you would like to remove
    ///////////////////////////////////////////////////////////////////
	void removeElement(int index);
};

#endif
