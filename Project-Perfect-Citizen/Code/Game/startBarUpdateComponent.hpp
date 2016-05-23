#pragma once

#include <SFML/Graphics.hpp>
#include "startBarRenderComponent.hpp"
#include "../Engine/updateComponent.h"


namespace ppc {
    
    ///////////////////////////////////////////////////////////////////////
    /// @brief Designated Update component for start bar
    /// @author Michael Lowe
    /// @details mainly used for system time
    ///////////////////////////////////////////////////////////////////////
    
    class startBarUpdateComponent : public ppc::UpdateComponent {
        
    private:
        startBarRenderComponent *render;
        float speed = 1.f;
        sf::Time counter;
        sf::Time framePeriod;
    public:
        ////////////////////////////////////////////////////////////////////
        /// @brief Constructor for animatorComponent
        ////////////////////////////////////////////////////////////////////
        startBarUpdateComponent();
        
        ////////////////////////////////////////////////////////////////////
        /// @brief Constructor for animatorComponent
        /// @param r is the render component we wish to animate
        /// @param s is the speed of the animate as a function of frame rate
        ////////////////////////////////////////////////////////////////////
        startBarUpdateComponent(startBarRenderComponent& r);
        
        ////////////////////////////////////////////////////////////////////
        /// @brief Destructor for animatorComponent
        ////////////////////////////////////////////////////////////////////
        ~startBarUpdateComponent();
        
        ////////////////////////////////////////////////////////////////////
        /// @brief update method for animatorComponent
        /// @param deltaTime is the time that has passed since the last
        ///        render update by the engine.
        ////////////////////////////////////////////////////////////////////
        void update(sf::Time& deltaTime) override;
        
    };
    
    
};

