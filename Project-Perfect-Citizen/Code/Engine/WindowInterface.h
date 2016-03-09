#ifndef WINDOW_INTERFACE_H
#define WINDOW_INTERFACE_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include "inputComponent.h"
#include "updateComponent.h"
#include "renderComponent.h"
#include "entity.h"


namespace ppc {


///////////////////////////////////////////////////////////////////////
/// @brief Interface for all Window interactions.
/// @details Due to the relatively complicated Window hierarchy, this
///     class is needed to define the common interface between all 
///     classes in the hierarchy.
///////////////////////////////////////////////////////////////////////
class WindowInterface : public sf::Drawable {
public:
  /////////////////////////////////////////////////////////////////////
  // Virtual Destructor
  /////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////
    /// @brief Virtual Destructor
    ///////////////////////////////////////////////////////////////////
    virtual ~WindowInterface() {};


  /////////////////////////////////////////////////////////////////////
  // Space Getters
  /////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////
    /// @brief Returns the size of the Window Space.
    ///////////////////////////////////////////////////////////////////
    virtual sf::Vector2u getSize() = 0;

    ///////////////////////////////////////////////////////////////////
    /// @brief Returns the Bounding Box of the entire Window. 
    ///////////////////////////////////////////////////////////////////
    virtual sf::FloatRect getBounds() = 0;

    
  /////////////////////////////////////////////////////////////////////
  // Space Setters
  /////////////////////////////////////////////////////////////////////
    

    ///////////////////////////////////////////////////////////////////
    /// @brief Sets the size of the Window.
    /// @details Specifically, this function sets the size space that 
    ///     represents this room. A Window can be displayed independant
    ///     of its size.
    ///
    /// @param width The desired width of the Window.
    /// @param height The desired height of the Window.
    /// @post Any components defined as part of the Window that now lay
    ///     outside of it are destroyed.
    ///////////////////////////////////////////////////////////////////
    virtual void setSize(unsigned int width, unsigned int height) = 0;
  
    ///////////////////////////////////////////////////////////////////
    /// @brief Sets the size of the Window.
    /// @details Specifically, this function sets the size space that 
    ///     represents this room. A Window can be displayed independant
    ///     of its size.
    ///
    /// @param size A vector denoting the desired size of the Window.
    /// @post Any components defined as part of the Window that now lay
    ///     outside of it are destroyed.
    ///////////////////////////////////////////////////////////////////
    void setSize(sf::Vector2u& size);


  /////////////////////////////////////////////////////////////////////
  // View Manipulation
  /////////////////////////////////////////////////////////////////////
    
    ///////////////////////////////////////////////////////////////////
    /// @brief Returns the FloatRect that represents the View.
    ///////////////////////////////////////////////////////////////////
    virtual const sf::View& getView() const = 0;
  
    ///////////////////////////////////////////////////////////////////
    /// @brief Sets the view of the Window
    ///
    /// @param view The desired view for the Window.
    ///////////////////////////////////////////////////////////////////
    virtual void setView(const sf::View& view) = 0;
    
    ///////////////////////////////////////////////////////////////////
    /// @brief Resets the view of the Window to the entire Window
    ///////////////////////////////////////////////////////////////////
    virtual const sf::View& getDefaultView() = 0;
    
    
  /////////////////////////////////////////////////////////////////////
  // Transformation Setters
  /////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////
    /// @brief Sets the position of the Window.
    ///
    /// @param x The desired x coordinate for the Window.
    /// @param y The desired y coordinate for the Window.
    ///////////////////////////////////////////////////////////////////
    virtual void setPosition(float x, float y) = 0;

    ///////////////////////////////////////////////////////////////////
    /// @brief Sets the position of the Window.
    ///
    /// @param pos The desired position for the Window.
    ///////////////////////////////////////////////////////////////////
    void setPosition(const sf::Vector2f& pos);

    ///////////////////////////////////////////////////////////////////
    /// @brief Adjusts the position of the Window.
    ///
    /// @param dx The desired horizontal shift in position for the 
    ///     Window.
    /// @param dy The desired vertical shift in position for the 
    ///     Window.
    ///////////////////////////////////////////////////////////////////
    virtual void move(float dx, float dy) = 0;
    
    ///////////////////////////////////////////////////////////////////
    /// @brief Adjusts the position of the Window.
    ///
    /// @param dpos The desired shift in position for the Window as a 
    ///     Vector.
    ///////////////////////////////////////////////////////////////////
    void move(const sf::Vector2f& dpos);

    ///////////////////////////////////////////////////////////////////
    /// @brief Sets the scale of the Window.
    ///
    /// @param xscale The desired horizontal scale factor of the 
    ///     Window.
    /// @param yscale The desired vertical scale factor of the Window.
    ///////////////////////////////////////////////////////////////////
    virtual void setScale(float xscale, float yscale) = 0;
    
    ///////////////////////////////////////////////////////////////////
    /// @brief Sets the scale of the Window.
    ///
    /// @param scale The desired scale factor of the Window.
    ///////////////////////////////////////////////////////////////////
    void setScale(float scale);

    ///////////////////////////////////////////////////////////////////
    /// @brief Sets the scale of the Window.
    ///
    /// @param scale The desired scale factor of the Window as a 
    ///     Vector.
    ///////////////////////////////////////////////////////////////////
    void setScale(const sf::Vector2f& scale);

    ///////////////////////////////////////////////////////////////////
    /// @brief Scales the Window relative to its current scale.
    ///
    /// @param xscale The desired horizontal scaling factor.
    /// @param yscale The desired vertical scaling factor.
    ///////////////////////////////////////////////////////////////////
    virtual void scale(float xscale, float yscale) = 0;

    ///////////////////////////////////////////////////////////////////
    /// @brief Scales the Window relative to its current scale.
    ///
    /// @param scaleFactor The desired scaling factor.
    ///////////////////////////////////////////////////////////////////
    void scale(float scaleFactor);

    ///////////////////////////////////////////////////////////////////
    /// @brief Scales the Window relative to its current scale.
    ///
    /// @param scaleVec The desired scaling factor as a Vector.
    ///////////////////////////////////////////////////////////////////
    void scale(const sf::Vector2f& scaleVec);


  /////////////////////////////////////////////////////////////////////
  // Transformation Getters
  /////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////
    /// @brief Returns the position of the Window.
    ///////////////////////////////////////////////////////////////////
    virtual sf::Vector2f getPosition() const = 0;

    ///////////////////////////////////////////////////////////////////
    /// @brief Returns the scale of the Window.
    ///////////////////////////////////////////////////////////////////
    virtual sf::Vector2f getScale() const = 0 ;

    
  /////////////////////////////////////////////////////////////////////
  // Other Getters
  /////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////
    /// @brief Returns the InputHandler associated with this Window.
    ///////////////////////////////////////////////////////////////////
    virtual InputHandler& getInputHandler() = 0;

  /////////////////////////////////////////////////////////////////////
  // Component Manipulation
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
    virtual void addInputComponent(InputComponent* inputcmpnt) = 0;

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
    virtual void addRenderComponent(RenderComponent* rendercmpnt) = 0;

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
    virtual void addUpdateComponent(UpdateComponent* updatecmpnt) = 0;

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
    virtual void addEntity(Entity& entity) = 0;


  /////////////////////////////////////////////////////////////////////
  // Game Loop Functionality
  /////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////
    /// @brief Updates this, and all objects in the Window.
    ///////////////////////////////////////////////////////////////////
    virtual void update(sf::Time& deltaTime) = 0;

    ///////////////////////////////////////////////////////////////////
    /// @brief Reacts to Input for this, and all objects in the Window.
    ///////////////////////////////////////////////////////////////////
    virtual void registerInput(sf::Event&) = 0;

	///////////////////////////////////////////////////////////////////
	///@brief Refreshes the Window so it is ready to draw again.
	///////////////////////////////////////////////////////////////////
	virtual void refresh(sf::RenderStates) = 0;


  /////////////////////////////////////////////////////////////////////
  // Close State
  /////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////
    /// @brief Sets Window State
    ///////////////////////////////////////////////////////////////////
    void close() { closed_ = true; };

    ///////////////////////////////////////////////////////////////////
    /// @brief Gets Window State
    ///////////////////////////////////////////////////////////////////
    bool isOpen() const { return !closed_; };


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


    private:

        bool closed_ = false;

};


};      //End namespace



#endif  //End WINDOW_INTERFACE_H
