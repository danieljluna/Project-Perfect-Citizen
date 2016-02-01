#ifndef WINDOW_H
#define WINDOW_H

#include <vector>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include "windowInterface.h"
#include "inputComponent.h"
#include "updateComponent.h"
#include "renderComponent.h"


namespace ppc {


///////////////////////////////////////////////////////////////////////
/// @brief Manages a sub-screen with its own Components
/// @author Daniel Luna
///////////////////////////////////////////////////////////////////////
class Window : public WindowInterface {
public:

  /////////////////////////////////////////////////////////////////////
  // Constructors and Destructor
  /////////////////////////////////////////////////////////////////////

    //No Default Constructor
    Window() = delete;

    ///////////////////////////////////////////////////////////////////
    /// @brief Window Constructor
    /// @details Creates a Window of the given width and height.
    ///
    /// @param width The desired width of the Window
    /// @param height The desired height of the Window
    ///////////////////////////////////////////////////////////////////
    Window(unsigned int width, 
           unsigned int height, 
           sf::Color color = sf::Color::Black);

    ///////////////////////////////////////////////////////////////////
    /// @brief Window Constructor
    /// @details Creates a Window of the given size.
    ///
    /// @param size The desired size of the Window
    ///////////////////////////////////////////////////////////////////
    Window(const sf::Vector2u& size);

    ///////////////////////////////////////////////////////////////////
    /// @brief Copy Constructor
    ///////////////////////////////////////////////////////////////////
    Window(const Window& other);

    ///////////////////////////////////////////////////////////////////
    /// @brief Virtual Destructor
    ///////////////////////////////////////////////////////////////////
    virtual ~Window();


  /////////////////////////////////////////////////////////////////////
  // Step Functionality
  /////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////
    /// @brief Updates this, and all objects in the Window.
    ///////////////////////////////////////////////////////////////////
    virtual void update(sf::Time& deltaTime) override;

    ///////////////////////////////////////////////////////////////////
    /// @brief Reacts to Input for this, and all objects in the Window.
    ///////////////////////////////////////////////////////////////////
    virtual void registerInput() final;

    ///////////////////////////////////////////////////////////////////
    /// @brief Refreshes the Window so it is ready to draw again.
    /// @details Should be called any time a Component of the Window
    ///     might change.
    ///
    /// @post The next call to draw the Window will correctly depict
    ///     the state of all renderComponents in this Window at this 
    ///     time.
    /// @param states Used to manipulate draw 
    ///////////////////////////////////////////////////////////////////
    void refresh(sf::RenderStates states = sf::RenderStates());


protected:

    ///////////////////////////////////////////////////////////////////
    /// @brief Draws the last Window refresh
    /// @details This does NOT draw all objects within the window, it
    ///     merely draws the texture which was last updated in the last
    ///     call to refresh().
    ///
    /// @param target The target to draw to.
    /// @param states Used to manipulate draw calls
    ///////////////////////////////////////////////////////////////////
    void draw(sf::RenderTarget& target, 
              sf::RenderStates states) const override;


  /////////////////////////////////////////////////////////////////////
  // Protected Members
  /////////////////////////////////////////////////////////////////////

    sf::RenderTexture windowSpace_;

    sf::Color backgroundColor_;

    sf::View windowView_;
    
    std::vector<InputComponent*> inputcmpnts_;

    std::vector<UpdateComponent*> updatecmpnts_;

    std::vector<RenderComponent*> rendercmpnts_;


};


};      //End namespace ppc


#endif  //End WINDOW_H
