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
/// @brief THE BOUNDING BOX FOR THE PIPELINE GRAPH PART OF THE WINDOW
/// @author Alex Vincent
/// @details write this later
///////////////////////////////////////////////////////////////////////
class PipelineGraphRenderComponent : public ppc::RenderComponent {
private:

	////////////////////////////////////////////////////////////////////
	/// @brief The background of the Pipeline data box
	////////////////////////////////////////////////////////////////////
	sf::RectangleShape graphBoxBackground_;


public:

	PipelineGraphRenderComponent(int x, int y, int backgroundWidth, int backgroundHeight);

	~PipelineGraphRenderComponent();


	virtual void draw(sf::RenderTarget & target,
		sf::RenderStates states) const;

	//virtual void registerInput(sf::Event& ev) override;
	virtual void recieveMessage(msgType code) override;

};