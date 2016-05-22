//
//  endAnimationUpdateComponent.hpp
//  Project-Perfect-Citizen
//
//  Created by Michael Lowe on 3/10/16.
//  Copyright © 2016 Hyperfocus Games. All rights reserved.
//

#ifndef endAnimationUpdateComponent_hpp
#define endAnimationUpdateComponent_hpp

#include <stdio.h>
#include "../Engine/updateComponent.h"
#include <SFML/System/Time.hpp>


namespace ppc {

	class endingAnimationRender;
	///////////////////////////////////////////////////////////////////////
	/// @brief Designated Animator Update Component for Boot Loading Screen
	/// @author Michael Lowe
	/// @details The Animator Component updates the frame for
	///          Boot Loading Animation Render
	///////////////////////////////////////////////////////////////////////
	class endAnimationUpdateComponent : public ppc::UpdateComponent {

	private:
		endingAnimationRender *render;
		float speed;
		sf::Time counter;
		sf::Time framePeriod;
	public:
		////////////////////////////////////////////////////////////////////
		/// @brief Constructor for bootLoadingUpdateComponent
		////////////////////////////////////////////////////////////////////
		endAnimationUpdateComponent(endingAnimationRender& r, float s);


		////////////////////////////////////////////////////////////////////
		/// @brief Destructor for bootLoadingUpdateComponent
		////////////////////////////////////////////////////////////////////
		~endAnimationUpdateComponent();



		////////////////////////////////////////////////////////////////////
		/// @brief update method for bootLoadingUpdateComponent
		/// @param deltaTime is the time that has passed since the last
		///        render update by the engine.
		////////////////////////////////////////////////////////////////////
		void update(sf::Time& deltaTime) override;

	};

};


#endif /* endAnimationUpdateComponent_hpp */
