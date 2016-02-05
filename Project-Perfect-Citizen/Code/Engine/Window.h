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
    Window(float width, 
           float height, 
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
  // Setters
  /////////////////////////////////////////////////////////////////////

    //TODO: Add Setters
    
  /////////////////////////////////////////////////////////////////////
  // Adding Entities and Components
  /////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////
    /// @brief Adds an Input Component to the Window.
    /// @details This function adds an Input Component to the Window.
    ///     Currently merely appends the Component.
    /// @todo Add functionality to assign Components order in the 
    ///     Vector
    ///
    /// @pre inputcmpnt != nullptr
    /// @param inputcmpnt A pointer to the InputComponent to add.
    ///////////////////////////////////////////////////////////////////
    void addInputComponent(InputComponent* inputcmpnt);

    ///////////////////////////////////////////////////////////////////
    /// @brief Adds an Render Component to the Window.
    /// @details This function adds an Render Component to the Window.
    ///     Currently merely appends the Component.
    /// @todo Add functionality to assign Components order in the 
    ///     Vector
    ///
    /// @pre rendercmpnt != nullptr
    /// @param rendercmpnt A pointer to the RenderComponent to add.
    ///////////////////////////////////////////////////////////////////
    void addRenderComponent(RenderComponent* rendercmpnt);
  
    ///////////////////////////////////////////////////////////////////
    /// @brief Adds an Update Component to the Window.
    /// @details This function adds an Update Component to the Window.
    ///     Currently merely appends the Component.
    /// @todo Add functionality to assign Components order in the 
    ///     Vector
    ///
    /// @pre updatecmpnt != nullptr
    /// @param updatecmpnt A pointer to the UpdateComponent to add.
    ///////////////////////////////////////////////////////////////////
    void addUpdateComponent(UpdateComponent* updatecmpnt);

    ///////////////////////////////////////////////////////////////////
    /// @brief Adds an Entity to the Window
    /// @details More specifically, this adds the Components connected
    ///     to this Entity to the Window. Currently merely appends the 
    ///     Components.
    /// @todo Add functionality to assign Components order in the 
    ///     Vector
    ///
    /// @param entity The entity to add to the Window.
    ///////////////////////////////////////////////////////////////////
    void addEntity(Entity& entity);

    
  /////////////////////////////////////////////////////////////////////
  // Step Functionality
  /////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////
    /// @brief Updates this, and all objects in the Window.
    ///
    /// @param deltaTime The time the object needs to catch up with.
    ///////////////////////////////////////////////////////////////////
    virtual void update(sf::Time& deltaTime) override;

    ///////////////////////////////////////////////////////////////////
    /// @brief Reacts to Input for this, and all objects in the Window.
    ///////////////////////////////////////////////////////////////////
    virtual void registerInput(sf::Event&) final;

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

    //The texture that will be the final window
    sf::RenderTexture windowSpace_;

    //The background color of the window
    sf::Color backgroundColor_;

    //The view of the Texture used when drawing the Window.
    //Not in use yet.
    sf::View windowView_;
    
    //HACK: Holds all inputComponents for the Window.
    //Eventually this will be a means of passing events to components
    //  via subjects and observers
    std::vector<InputComponent*> inputcmpnts_;

    //All the update Components currently in the window. Will be 
    //  iterated over.
    std::vector<UpdateComponent*> updatecmpnts_;

    //All the render Components currently in the window. Will be 
    //  iterated over.
    std::vector<RenderComponent*> rendercmpnts_;


};


};      //End namespace ppc


#endif  //End WINDOW_H
