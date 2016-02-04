#ifndef WINDOW_INTERFACE_H
#define WINDOW_INTERFACE_H


#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Window/Event.hpp>


namespace ppc {


///////////////////////////////////////////////////////////////////////
/// @brief Interface for all Window interactions.
/// @details Due to the relatively complicated Window hierarchy, this
///     class is needed to define the common interface between all 
///     classes in the hierarchy.
///////////////////////////////////////////////////////////////////////
class WindowInterface : public sf::Drawable, public sf::Transformable {
public:
  /////////////////////////////////////////////////////////////////////
  // Virtual Destructor
  /////////////////////////////////////////////////////////////////////

    virtual ~WindowInterface() {};

    
  /////////////////////////////////////////////////////////////////////
  // Update Functionality
  /////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////
    /// @brief Updates this, and all objects in the Window.
    ///////////////////////////////////////////////////////////////////
    virtual void update(sf::Time& deltaTime) = 0;

    ///////////////////////////////////////////////////////////////////
    /// @brief Reacts to Input for this, and all objects in the Window.
    ///////////////////////////////////////////////////////////////////
    virtual void registerInput(sf::Event&) = 0;


protected:

  /////////////////////////////////////////////////////////////////////
  // Constructors
  /////////////////////////////////////////////////////////////////////
    
    WindowInterface() {};

    WindowInterface(const WindowInterface&) {};


    ///////////////////////////////////////////////////////////////////
    /// @brief Draws this, and all objects in the Window.
    /// @details 
    ///
    /// @param target This is almost always going to be a 
    /// sf::renderWindow. 
    /// @param states This is used to dictate certain states that the 
    /// object can be rendered in. For now this can be safely "ignored"
    /// Just created a RenderStates object and shove it in there. 
    ///////////////////////////////////////////////////////////////////
    virtual void draw(sf::RenderTarget& target,
                      sf::RenderStates states) const override = 0;


};


};      //End namespace



#endif  //End WINDOW_INTERFACE_H
