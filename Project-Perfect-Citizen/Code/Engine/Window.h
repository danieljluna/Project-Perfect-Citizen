#ifndef WINDOW_H
#define WINDOW_H

#include <vector>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include "inputComponent.h"
#include "updateComponent.h"
#include "renderComponent.h"
#include "WindowInterface.h"


namespace ppc {


///////////////////////////////////////////////////////////////////////
/// @brief Manages a sub-screen with its own Components
///////////////////////////////////////////////////////////////////////
class Window : public WindowInterface, public sf::Drawable {
public:

  /////////////////////////////////////////////////////////////////////
  // Constructors and Destructor
  /////////////////////////////////////////////////////////////////////

    Window();

    Window(const Window& other) = delete;

    virtual ~Window();


  /////////////////////////////////////////////////////////////////////
  // Update Functionality
  /////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////
    /// @brief Updates this, and all objects in the Window.
    ///////////////////////////////////////////////////////////////////
    virtual void update(sf::Time deltaTime);

    ///////////////////////////////////////////////////////////////////
    /// @brief Reacts to Input for this, and all objects in the Window.
    ///////////////////////////////////////////////////////////////////
    virtual void getInput();


protected:

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
                      sf::RenderStates states) const override;

  /////////////////////////////////////////////////////////////////////
  // Protected Constructors
  /////////////////////////////////////////////////////////////////////

    //Default Constructor
    Window();

    //Copy Constructor
    Window(const Window& other);

    //Move Constructor
    Window(Window&& other);


  /////////////////////////////////////////////////////////////////////
  // Protected Members
  /////////////////////////////////////////////////////////////////////

    sf::RenderTexture windowSpace;

    sf::View windowView;
    
    std::vector<InputComponent> inputcmpnts;

    std::vector<InputComponent> updatecmpnts;

    std::vector<InputComponent> rendercmpnts;


};


};      //End namespace ppc


#endif  //End WINDOW_H
