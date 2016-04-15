#ifndef SCROLLBAR_DECO_H
#define SCROLLBAR_DECO_H

#include "WindowDecorator.h"
#include "Entity.h"
#include "FreeFunctionObserver.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace sf {
    class Image;
    class Sprite;
};

namespace ppc {

class DraggableInput;
class mousePressButton;
class buttonRenderComponent;

///////////////////////////////////////////////////////////////////////
/// @brief Scroll Bar Decorator for Windows
/// @details Creates a horizontal and vertical scrollbar for easy 
///     manipulation of the view for the given Window. The scrollbars
///     are draggable and have arrow keys for manipulation.
///
/// @todo Add mouse wheel input functionality
///////////////////////////////////////////////////////////////////////
class ScrollBarDecorator : public ppc::WindowDecorator {
public:

  /////////////////////////////////////////////////////////////////////
  // Constructors & Destructor
  /////////////////////////////////////////////////////////////////////

    ScrollBarDecorator() = delete;

    ///////////////////////////////////////////////////////////////////
    /// @brief Constructor
    /// @details Creates a new ScrollBarDecorator wrapping the given
    ///     window. The view is assumed to be the entire Window.
    ///
    /// @param win The given WindowInterface to decorate.
    /// @param img The Image to get the buttons from. Use layout 
    ///     matching Windows_UI.png for now.
    ///////////////////////////////////////////////////////////////////
    ScrollBarDecorator(WindowInterface& win, sf::Image& img);

    ///////////////////////////////////////////////////////////////////
    /// @brief Constructor
    /// @details Creates a new ScrollBarDecorator wrapping the given
    ///     window. The view is passed in as well.
    ///
    /// @param win The given WindowInterface to decorate.
    /// @param img The Image to get the buttons from. Use layout 
    ///     matching Windows_UI.png for now.
    /// @param view The desired inital view for the ScrollBarDecorator.
    ///////////////////////////////////////////////////////////////////
    ScrollBarDecorator(WindowInterface& win, sf::Image& img, 
                       const sf::View& view);

    ///////////////////////////////////////////////////////////////////
    /// @brief Virtual Destructor
    ///////////////////////////////////////////////////////////////////
    virtual ~ScrollBarDecorator();


  /////////////////////////////////////////////////////////////////////
  // Window Overrides
  /////////////////////////////////////////////////////////////////////

    sf::Vector2u getSize() const override;

    void setSize(unsigned int x, unsigned int y) override;

    sf::FloatRect getBounds() const override;

    void setPosition(float x, float y) override;

    void move(float dx, float dy) override;

    void setView(const sf::View& view) override;

    

  /////////////////////////////////////////////////////////////////////
  // View Manipulation
  /////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////
    /// @brief Sets the width of the bars.
    /// @details UNTESTED.
    ///
    /// @todo IMPLEMENT.
    ///////////////////////////////////////////////////////////////////
    void setBarSize(float barSize);


protected:

    void draw(sf::RenderTarget& target, sf::RenderStates) const override;


private:

  /////////////////////////////////////////////////////////////////////
  // Helper Functions
  /////////////////////////////////////////////////////////////////////

    //Repositions the Sliders based on the new position
    void repositionSliders();

    //Updates the button inputs
    void updateButtons();

    //Updates the Draggabe inputs
    void updateDraggable();
    
    //Updates the Bars based on the View position
    void updateSliders();

    //Updates the View based on the bars position
    void updateView();

    void initialize(sf::Image img);

    friend bool onSliderDrag(ScrollBarDecorator*, Event);
    friend bool onButtonUp(ScrollBarDecorator*, Event);
    friend bool onButtonDown(ScrollBarDecorator*, Event);
    friend bool onButtonLeft(ScrollBarDecorator*, Event);
    friend bool onButtonRight(ScrollBarDecorator*, Event);


  /////////////////////////////////////////////////////////////////////
  // Private Variables
  /////////////////////////////////////////////////////////////////////

    float barSize_ = 20.0f;

    //Array of ScrollBar Rectangles
    sf::RectangleShape scrollBars_[2];
    //Stores the input Component that allows the Window to be dragged 
    //  via the BorderDecorator.
    DraggableInput* draggableInputs_[2];
    //Array of ScrollBar Backgrounds
    sf::RectangleShape scrollBackgrounds_[2];
    //Function Observers for ScrollBars
    FreeFunctionObserver<ScrollBarDecorator> *obsvrs_[6];
    


    //Array of buttonRenderComponents
    buttonRenderComponent* buttonRenders_[4];
    //Array of buttonInputComponents
    mousePressButton* buttonInputs_[4];
    //Array of button Entities
    Entity buttonEntities_[4];


};



bool onSliderDrag(ScrollBarDecorator*, Event);

bool onButtonUp(ScrollBarDecorator*, Event);

bool onButtonDown(ScrollBarDecorator*, Event);

bool onButtonLeft(ScrollBarDecorator*, Event);

bool onButtonRight(ScrollBarDecorator*, Event);









};


#endif  //End Scrollbar Deco
