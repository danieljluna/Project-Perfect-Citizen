#include "createTutorial.h"

#include "../Engine/Engine.h"
#include "IconBuilder.h"

void ppc::createTutorial(Desktop & dt) {

	Entity graphIcon;

	IconBuilder pipelineGraph;
	pipelineGraph.setDesktop(dt);
	pipelineGraph.setInbox(dt.getInbox());
	pipelineGraph.setButtonSheet(dt.getButtonSheet());
	pipelineGraph.setIconType("dataGraphIcon");
	pipelineGraph.setSpritebyIndicies(0, 4, 1, 2);
	pipelineGraph.setAnimSpeed(0.30f);
	pipelineGraph.setInputHandle(dt.getInputHandler());
	pipelineGraph.setPosition({ 500.f,300.f });
	pipelineGraph.setText("Graph", World::getFont(World::VT323Regular), sf::Color::Black);
	pipelineGraph.setSize(0.5f);
	//TODO: ADD FLOPPY FUNC TO CREATE
	pipelineGraph.create(graphIcon);

	dt.getDesktopWindow()->addEntity(graphIcon);

}
