#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>


namespace sf {
    class Time;
    class Texture;
};

namespace ppc {

///////////////////////////////////////////////////////////////////////
/// @brief Transition Class defines fade from one image to another
/// @details Different Transitions should subclass this class.
///////////////////////////////////////////////////////////////////////
class Transition : sf::Drawable {
public:

  /////////////////////////////////////////////////////////////////////
  // Constructors / Destructors
  /////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////
    /// @brief Default Constructor
    /// @details Creates a transition between two blank sprites.
    ///////////////////////////////////////////////////////////////////
    Transition();

    ///Virtual Destructor
    virtual ~Transition();


  /////////////////////////////////////////////////////////////////////
  // Set Up
  /////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////
    /// @brief Sets the starting and ending image by Texture.
    /// @param start Desired Texture for the start of the Transition.
    /// @param end Desired Texture for the end of the Transition.
    ///////////////////////////////////////////////////////////////////
    void setTextures(sf::Texture& start, sf::Texture& end);

    ///////////////////////////////////////////////////////////////////
    /// @brief Sets the Rectangle up to fit in the bounds of the given
    ///     sf::FloatRect.
    ///////////////////////////////////////////////////////////////////
    void setBounds(sf::FloatRect bounds);
    

  /////////////////////////////////////////////////////////////////////
  // Transition Functionality
  /////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////
    /// @brief Returns the current position of the transition.
    ///////////////////////////////////////////////////////////////////
    float getTransitionPoint() const;
    
    ///////////////////////////////////////////////////////////////////
    /// @brief Jumps to a position in the transition.
    /// @details The position will clip to the bounds [0, 1].
    /// @param position The position in the transition to move to 
    ///     described as a percentage.
    ///////////////////////////////////////////////////////////////////
    void setTransitionPoint(float position);

    ///////////////////////////////////////////////////////////////////
    /// @brief Moves the transition forward.
    /// @param delta Percentage to move forward by.
    ///////////////////////////////////////////////////////////////////
    void incrementTransition(float delta);

    ///////////////////////////////////////////////////////////////////
    /// @brief Moves the transition backwards.
    /// @param delta Percentage to move backwards by.
    ///////////////////////////////////////////////////////////////////
    void decrementTransition(float delta);

    ///////////////////////////////////////////////////////////////////
    /// @brief Draws the Transition
    /// @details The default version of this function simply draws the 
    ///     Transition RectangleShape as it currently is. This function
    ///     may be overwritten to provide more interesting 
    ///     functionality.
    ///////////////////////////////////////////////////////////////////
    virtual void draw(sf::RenderTarget&, sf::RenderStates) const;


protected:

  /////////////////////////////////////////////////////////////////////
  // Protected Functionality
  /////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////
    /// @brief Called when the transition is advanced in any way.
    /// @details Override this function if you want to manipulate the
    ///     Transition immediately after transitionPoint is called.
    ///////////////////////////////////////////////////////////////////
    virtual void onAdvance() {};


  /////////////////////////////////////////////////////////////////////
  // Protected Data
  /////////////////////////////////////////////////////////////////////

    //Starting Texture
    sf::Texture* start_;

    //Ending Texture
    sf::Texture* end_;

    //Rectangle the transition is projected on
    sf::RectangleShape transitionShape_;


private:

  /////////////////////////////////////////////////////////////////////
  // Private Data
  /////////////////////////////////////////////////////////////////////

    //Denotes where in the Transition we are. 0.0 is start, 1.0 is end.
    float transitionPoint_ = 0.0f;
    
  /////////////////////////////////////////////////////////////////////
  // Helper Functions
  /////////////////////////////////////////////////////////////////////

    //Force transitionPoint_ into [0, 1]
    void clipTransitionPoint();

};



};  //End namespace ppc
