#ifndef BORDER_DECORATOR_H
#define BORDER_DECORATOR_H

#ifdef WINDOWS_MARKER
#define resourcePath() string("Resources/")
#else
#include "ResourcePath.hpp"
#endif

#include "WindowDecorator.h"
#include "DraggableInput.h"
#include "../Game/buttonRenderComponent.h"
#include "Entity.h"
#include "../Game/mousePressButton.h"

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
  // Decorated Functionality
  /////////////////////////////////////////////////////////////////////

    virtual sf::Vector2u getSize() override;

    virtual void setSize(unsigned int x, unsigned int y) override;

    virtual void setPosition(float x, float y) override;

    virtual void move(float x, float y) override;

    virtual sf::FloatRect getBounds() override;


protected:

    virtual void draw(sf::RenderTarget& target,
                      sf::RenderStates states) const override;


private:

    void updateBounds();


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

	sf::RectangleShape closeButtonArea_;
	buttonRenderComponent* closeRC_;
	mousePressButton* bIC_;
	Entity closeButton_;


};
    

};      //End namespace ppc


#endif  //BORDER_DECORATOR_H
