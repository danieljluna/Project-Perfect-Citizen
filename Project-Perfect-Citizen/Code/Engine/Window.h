#ifndef WINDOW_H
#define WINDOW_H

#include <vector>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include "inputComponent.h"
#include "updateComponent.h"
#include "renderComponent.h"
#include "WindowInterface.h"


namespace ppc {


///////////////////////////////////////////////////////////////////////
/// @brief Interface for all Window Objects
/// @details 
///////////////////////////////////////////////////////////////////////
class Window : public WindowInterface {
public:

  /////////////////////////////////////////////////////////////////////
  // Constructors & Destructor
  /////////////////////////////////////////////////////////////////////

    Window();

    virtual ~Window();

  /////////////////////////////////////////////////////////////////////
  // Update Functionality
  /////////////////////////////////////////////////////////////////////

    void update(sf::Time deltaTime);




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
    void draw(sf::RenderTarget& target,
        sf::RenderStates states) const override;


    sf::RectangleShape background;
    
    std::vector<InputComponent> inputcmpnts;

    std::vector<InputComponent> updatecmpnts;

    std::vector<InputComponent> rendercmpnts;


};


};      //End namespace ppc


#endif  //End WINDOW_H
