//
//  endingAnimationRender.hpp
//  Project-Perfect-Citizen
//
//  Created by Michael Lowe on 3/10/16.
//  Copyright © 2016 Hyperfocus Games. All rights reserved.
//

#ifndef endingAnimationRender_hpp
#define endingAnimationRender_hpp

#include <stdio.h>


//
//  bootLoadingAnimationRender.hpp
//  Project-Perfect-Citizen
//
//  Created by Michael Lowe on 3/7/16.
//  Copyright © 2016 Hyperfocus Games. All rights reserved.
//
#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include "../Engine/renderComponent.h"
#include <SFML/Graphics/Rect.hpp>

namespace sf {
	class Sprite;
	class Texture;
	class Image;
	class RenderTarget;
	//class IntRect;
};

namespace ppc {

	///////////////////////////////////////////////////////////////////////
	/// @brief Designated Render Component for a generic window 'X' button
	/// @author Michael Lowe
	/// @details The buttonRenderComponent is a basic packaged subclass
	///     extension of RenderComponent, make specifically to handle
	///     all generic "X" button related drawing/animating parts that
	///     also broadcast and recieve messages from an input handler.
	///		Stick this onto an entity to give it this functionality.
	///////////////////////////////////////////////////////////////////////
	class endingAnimationRender : public ppc::RenderComponent {
	private:

		sf::Sprite* sprite;
		sf::Sprite* comingSoon;
		sf::Texture* texture;
		sf::Texture* comingSoonTexture;
		sf::Image& image;
		sf::IntRect* rectSourceSprite;

		std::vector<int> y_vals;

		float loadX;
		int frame = 0;
		const int size = 128;


	public:

		////////////////////////////////////////////////////////////////////
		/// @brief Constructor for buttonRenderComponent
		/// @param imag is the sf::Image to be used
		////////////////////////////////////////////////////////////////////
		endingAnimationRender(sf::Image& img);
		~endingAnimationRender();

		////////////////////////////////////////////////////////////////////
		/// @brief called by the update component.
		////////////////////////////////////////////////////////////////////
		void animate();

		virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;


	};

};

#endif /* endingAnimationRender_hpp */
