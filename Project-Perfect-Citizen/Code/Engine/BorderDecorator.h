#ifndef BORDER_DECORATOR_H
#define BORDER_DECORATOR_H

#include "WindowDecorator.h"
#include "DraggableInput.h"
#include "../Game/buttonRenderComponent.h"
#include "Entity.h"
#include "../Game/mousePressButton.h"
#include "../Game/TextDisplayRenderComponent.h"

namespace ppc {

class BorderDecorator : public WindowDecorator {
public:

  /////////////////////////////////////////////////////////////////////
  // Constructors & Destructor
  /////////////////////////////////////////////////////////////////////

    //No default Constructor
    BorderDecorator() = delete;

    ///////////////////////////////////////////////////////////////////
    /// @brief Constructor
    /// @details Defines what Window the BorderDecorator is decorating.
    ///     The constructor's optional arguments define the width of 
    ///     the border around the decorated Window.
    ///
    /// @param win A reference to the WindowInterface to be decorated
    ///     by this BorderDecorator.
    /// @param majorBorder Defines the width of the border at the top
    ///     of the Window where the caption and buttons will be drawn.
    /// @param minorBorder Defines the width of the border around the
    ///     rest of the Window, and is simply used to outline the 
    ///     Window.
    ///////////////////////////////////////////////////////////////////
    BorderDecorator(WindowInterface& win,
                    unsigned int majorBorder = 34, 
                    unsigned int minorBorder = 5);

    ///////////////////////////////////////////////////////////////////
    /// @brief Virtual Destructor.
    ///////////////////////////////////////////////////////////////////
    virtual ~BorderDecorator();


  /////////////////////////////////////////////////////////////////////
  // Draggable Manipulation
  /////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////
    /// @brief Sets the clamp on this Window's Draggable.
    /// @details See DraggableInput.h
    ///
    /// @param clamp The area in Desktop space to clamp to.
    ///////////////////////////////////////////////////////////////////
    void setClampBounds(const sf::FloatRect& clamp);
    
  /////////////////////////////////////////////////////////////////////
  // Button Manipulation
  /////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////
    /// @brief Adds a button to the Border of this Window.
    /// 
    /// @param buttonImage The desired image for the button.
    /// @param buttonFn The desired action when the button is pressed.
    ///////////////////////////////////////////////////////////////////
    void addButton(sf::Image& buttonImage, 
                   bool (*buttonFn)(WindowInterface*, Event));

    friend bool closeWindow(WindowInterface* winInterface, Event ev);


  /////////////////////////////////////////////////////////////////////
  // Caption Functionality
  /////////////////////////////////////////////////////////////////////

    void setCaption(std::string text);

    void setCaptionFont(sf::Font font, unsigned int size = 20);

    void setCaptionColor(sf::Color col);


  /////////////////////////////////////////////////////////////////////
  // Decorated Functionality
  /////////////////////////////////////////////////////////////////////

    virtual sf::Vector2u getSize() const override;

    virtual void setSize(unsigned int x, unsigned int y) override;

    virtual void setView(const sf::View& view) override;

    virtual void setPosition(float x, float y) override;

    virtual void move(float x, float y) override;

    virtual sf::FloatRect getBounds() const override;


protected:

    virtual void draw(sf::RenderTarget& target,
                      sf::RenderStates states) const override;


private:

    //Updates the bounds
    void updateBounds();

    //Updates the ith Button's position
    void updateButton(size_t i);

    //Updates the borderRect
    void updateBorder();


  /////////////////////////////////////////////////////////////////////
  // Private Variables 
  /////////////////////////////////////////////////////////////////////

    //Stores the vector from the top left of the Window to the top left
    //  of the border.
    sf::Vector2u borderTopLeft_;

    //Stores the vector from the bottom right of the Window to the
    //  bottom right of the border.
    sf::Vector2u borderBottomRight_;

    //Stores the rectangle that is used to display the border.
    sf::RectangleShape borderShape_;

   
    //Stores the input Component that allows the Window to be dragged
    //  via the BorderDecorator.
    DraggableInput draggableInput_;

    //Holds the window caption.
    TextDisplayRenderComponent caption_;

    //Array of buttonRenderComponents
	buttonRenderComponent** buttonRenders_;
    //Array of buttonInputComponents
	mousePressButton** buttonInputs_;
    //Array of button Entities
    Entity** buttonEntities_;

    //Holds number of buttons in this WindowBorder
    unsigned int buttonCount_;
    const unsigned int maxButtons_;


};


    ///////////////////////////////////////////////////////////////////
    /// @brief Closes the passed window.
    /// @details Fits the format for function observers, but doesn't
    ///     make sue of the sf::Event as of now.
    ///////////////////////////////////////////////////////////////////
    bool closeWindow(WindowInterface* winInterface, Event ev);

};      //End namespace ppc


#endif  //BORDER_DECORATOR_H
