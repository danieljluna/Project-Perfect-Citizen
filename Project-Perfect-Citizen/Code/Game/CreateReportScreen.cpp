#include "CreateReportScreen.h"

#include "TextDisplayBuilder.h"
#include "TextCharacterUpdate.h"
#include <fstream>

using namespace ppc;

void ppc::createReportScreen(Desktop &d) {
	
	
	//will be a front top
	ppc::Window* reportScreen = new Window(1800, 1000);

	Entity reportEntity;
	std::string filename = World::getReportFile();
	std::ifstream reportFile(filename);

	std::string content((std::istreambuf_iterator<char>(reportFile)),
						(std::istreambuf_iterator<char>()));

	TextDisplayBuilder reportText;
	reportText.setColor(sf::Color::Red);
	reportText.setFont(World::getFont(World::FontList::Consola));
	reportText.setPosition({ 100,100 });
	reportText.setSize(25);
	reportText.setString("");

	reportText.create(reportEntity);
	

	//next, make/add components to end report screen
	TextCharacterUpdate* tcu = new TextCharacterUpdate();
	TextDisplayRenderComponent* tdrc = dynamic_cast<TextDisplayRenderComponent*>(reportEntity.getComponent(0));
	tcu->setTextDisplay(*tdrc);
	tcu->setContent(content);

	reportEntity.addComponent(tcu);

	reportScreen->addEntity(reportEntity);
	d.setFrontTop(reportScreen, false);


}

