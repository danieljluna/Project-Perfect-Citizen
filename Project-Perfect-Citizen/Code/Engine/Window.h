#ifndef WINDOW_H
#define WINDOW_H

#include <vector>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include "windowInterface.h"
#include "inputComponent.h"
#include "updateComponent.h"
#include "renderComponent.h"
#include "InputHandler.h"


namespace ppc {


///////////////////////////////////////////////////////////////////////
/// @brief Manages a sub-screen with its own Components
/// @author Daniel Luna
/// @details The Window class defines a space and an in-game Window
///     with which to add Entities and Components to.
/// @note Many functions are not documented in the .h file as Doxygen
///     automatically take the docs from parent classes when none are
///     provided.
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
    /// @param color The background color of the Window
    ///////////////////////////////////////////////////////////////////
    Window(unsigned int width, 
           unsigned int height, 
           sf::Color col = sf::Color::Black);

    ///////////////////////////////////////////////////////////////////
    /// @brief Window Constructor
    /// @details Creates a Window of the given size.
    ///
    /// @param size The desired size of the Window
    /// @param color The background color of the Window
    ///////////////////////////////////////////////////////////////////
    Window(const sf::Vector2u& size, sf::Color col = sf::Color::Black);

    ///////////////////////////////////////////////////////////////////
    /// @brief Copy Constructor
    ///////////////////////////////////////////////////////////////////
    Window(const Window& other);

    ///////////////////////////////////////////////////////////////////
    /// @brief Virtual Destructor
    ///////////////////////////////////////////////////////////////////
    virtual ~Window();


    // Space Getters

    virtual sf::Vector2u getSize() const override;
    virtual sf::FloatRect getBounds() const override;
    
    // Space Setters

    virtual void setSize(unsigned int width, unsigned int height) override;


    // View Manipulation

    const sf::View& getView() const override;
    void setView(const sf::View& view) override;
    const sf::View& getDefaultView() override;
    

    // Transformation Setters

    virtual void setPosition(float x, float y) override;
    virtual void move(float dx, float dy) override;
    virtual void setScale(float xscale, float yscale) override;
    virtual void scale(float xscale, float yscale) override;

    //Transformation Getters

    virtual sf::Vector2f getPosition() const override;
    virtual sf::Vector2f getScale() const override;

    //Component Manipulation

    virtual void addInputComponent(InputComponent* inputcmpnt) override;
    virtual void addRenderComponent(RenderComponent* rendercmpnt) override;
    virtual void addUpdateComponent(UpdateComponent* updatecmpnt) override;
    virtual void addEntity(Entity& entity) override;

    //Other Getters

    virtual InputHandler& getInputHandler() override;

    //Game Loop Functionality

    virtual void update(sf::Time& deltaTime) override;
    virtual void registerInput(sf::Event&) override;
    virtual void refresh(sf::RenderStates states = sf::RenderStates()) override;

    // Close State

    void close() override { closed_ = true; };
    bool isOpen() const override { return !closed_; };


private:

    void draw(sf::RenderTarget& target, 
              sf::RenderStates states) const override;


  /////////////////////////////////////////////////////////////////////
  // Helper Functions
  /////////////////////////////////////////////////////////////////////

    //Deletes all Entities that aren't part of the windowSpace
    void trimEntities();

    //Deletes an Entity along with its components
    void deleteEntity(std::vector<Entity>::iterator entityIt);

    //Removes a Component. Will not delete it.
    void removeComponent(Component* cmpntPtr);


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

    //Used to pass Events to inputComponents which are part of the 
    //  Window
    InputHandler inputHandler_;
    
    //Eventually this will be a means of passing events to components
    //  via subjects and observers
    std::vector<InputComponent*> inputcmpnts_;

    //All the update Components currently in the window. Will be 
    //  iterated over.
    std::vector<UpdateComponent*> updatecmpnts_;

    //All the render Components currently in the window. Will be 
    //  iterated over.
    std::vector<RenderComponent*> rendercmpnts_;

    //Stores all the Entities that reside in this room
    std::vector<Entity> entityVec_;

    //Stores the Transformation applicable to the Window
    sf::Transformable transform_;

    //Tells us if the Window is closeds
    bool closed_ = false;


};


};      //End namespace ppc


#endif  //End WINDOW_H
