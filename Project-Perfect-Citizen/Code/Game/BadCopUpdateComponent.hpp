
#pragma once

#include <SFML/Graphics.hpp>

#include "../Engine/updateComponent.h"
#include "BadCopRenderComponent.hpp"

namespace ppc {
    
    ///////////////////////////////////////////////////////////////////////
    /// @brief Designated Animator Component for the Bad Cop Logo
    /// @author Michael Lowe
    /// @details The Animator Component updates the frame for
    ///          Bad Cop Render Components that have more than two states
    ///////////////////////////////////////////////////////////////////////
    
    class BadCopUpdateComponent : public ppc::UpdateComponent {
        
    private:
        BadCopRenderComponent *render;
        float speed;
        sf::Time counter;
        sf::Time framePeriod;
    public:
        ////////////////////////////////////////////////////////////////////
        /// @brief Constructor for animatorComponent
        ////////////////////////////////////////////////////////////////////
        BadCopUpdateComponent();
        
        ////////////////////////////////////////////////////////////////////
        /// @brief Constructor for animatorComponent
        /// @param r is the render component we wish to animate
        /// @param s is the speed of the animate as a function of frame rate
        ////////////////////////////////////////////////////////////////////
        BadCopUpdateComponent(BadCopRenderComponent& r, float s);
        
        ////////////////////////////////////////////////////////////////////
        /// @brief Destructor for animatorComponent
        ////////////////////////////////////////////////////////////////////
        ~BadCopUpdateComponent();
        
        ////////////////////////////////////////////////////////////////////
        /// @brief update method for animatorComponent
        /// @param deltaTime is the time that has passed since the last
        ///        render update by the engine.
        ////////////////////////////////////////////////////////////////////
        void update(sf::Time& deltaTime) override;
        
    };
    
    
};

