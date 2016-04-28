#pragma once

#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../Engine/renderComponent.h"
#include "../Game/Database.h"
#include <string>
#include <stack>

using namespace std;

///////////////////////////////////////////////////////////////////////
/// @brief The bounding box for the graph component of the PE
/// @author Alex Vincent
/// @details A drawable rect inside the window to designate the border.
///////////////////////////////////////////////////////////////////////
class PipelineGraphRenderComponent : public ppc::RenderComponent {
private:

	////////////////////////////////////////////////////////////////////
	/// @brief The background of the Pipeline data box
	////////////////////////////////////////////////////////////////////
	sf::RectangleShape graphBoxBackground_;


public:
	////////////////////////////////////////////////////////////////////
	/// @brief Constructor
	/// @param x is the x position of the box to be rendered
	/// @param y is the y position of the box to be rendered
	/// @param backgroundWidth is the width of the box to be rendered
	/// @param backgroundHeight is the height of the box to be rendered
	////////////////////////////////////////////////////////////////////
	PipelineGraphRenderComponent(float x, float y, float backgroundWidth, float backgroundHeight);

	sf::FloatRect getLocalBounds();

	////////////////////////////////////////////////////////////////////
	/// @brief Destructor
	////////////////////////////////////////////////////////////////////
	~PipelineGraphRenderComponent();

	////////////////////////////////////////////////////////////////////
	/// @brief Inherited draw function of render component
	////////////////////////////////////////////////////////////////////
	virtual void draw(sf::RenderTarget & target,
		sf::RenderStates states) const;

	////////////////////////////////////////////////////////////////////
	/// @brief Inherited recieveMessage function of render component
	////////////////////////////////////////////////////////////////////
	virtual void recieveMessage(msgType code) override;

};