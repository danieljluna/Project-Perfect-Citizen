
#pragma once

#include <SFML/Graphics.hpp>

#include "../Engine/updateComponent.h"
#include "buttonRenderComponent.h"

namespace ppc {

///////////////////////////////////////////////////////////////////////
/// @brief Designated Animator Component for an animated Button Renderer
/// @author Michael Lowe
/// @details The Animator Component updates the frame for
///          Button Render Components that have more than two states
///////////////////////////////////////////////////////////////////////

class animatorComponent : public ppc::UpdateComponent {
    
private:
    buttonRenderComponent *render;
    float speed;
    sf::Time counter;
    sf::Time framePeriod;
public:
    ////////////////////////////////////////////////////////////////////
    /// @brief Constructor for animatorComponent
    ////////////////////////////////////////////////////////////////////
    animatorComponent();
    
    ////////////////////////////////////////////////////////////////////
    /// @brief Constructor for animatorComponent
    /// @param r is the render component we wish to animate
    /// @param s is the speed of the animate as a function of frame rate
    ////////////////////////////////////////////////////////////////////
    animatorComponent(buttonRenderComponent& r, float s);
    
    ////////////////////////////////////////////////////////////////////
    /// @brief Destructor for animatorComponent
    ////////////////////////////////////////////////////////////////////
    ~animatorComponent();
    
    ////////////////////////////////////////////////////////////////////
    /// @brief update method for animatorComponent
    /// @param deltaTime is the time that has passed since the last
    ///        render update by the engine.
    ////////////////////////////////////////////////////////////////////
    void update(sf::Time& deltaTime) override;

};


};

