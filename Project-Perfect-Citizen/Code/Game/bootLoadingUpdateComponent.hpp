//
//  bootLoadingUpdateComponent.hpp
//  Project-Perfect-Citizen
//
//  Created by Michael Lowe on 3/7/16.
//  Copyright © 2016 Hyperfocus Games. All rights reserved.
//

#pragma once
#include <stdio.h>

#include "../Engine/updateComponent.h"
#include <SFML/System/Time.hpp>


namespace ppc {
	class bootLoadingAnimationRender;

	///////////////////////////////////////////////////////////////////////
	/// @brief Designated Animator Update Component for Boot Loading Screen
	/// @author Michael Lowe
	/// @details The Animator Component updates the frame for
	///          Boot Loading Animation Render
	///////////////////////////////////////////////////////////////////////
	class bootLoadingUpdateComponent : public ppc::UpdateComponent {

	private:
		bootLoadingAnimationRender *render;
		float speed;
		sf::Time counter;
		sf::Time framePeriod;
	public:
		////////////////////////////////////////////////////////////////////
		/// @brief Constructor for bootLoadingUpdateComponent
		////////////////////////////////////////////////////////////////////
		bootLoadingUpdateComponent(bootLoadingAnimationRender& r, float s);


		////////////////////////////////////////////////////////////////////
		/// @brief Destructor for bootLoadingUpdateComponent
		////////////////////////////////////////////////////////////////////
		~bootLoadingUpdateComponent();



		////////////////////////////////////////////////////////////////////
		/// @brief update method for bootLoadingUpdateComponent
		/// @param deltaTime is the time that has passed since the last
		///        render update by the engine.
		////////////////////////////////////////////////////////////////////
		void update(sf::Time& deltaTime) override;

	};

};


