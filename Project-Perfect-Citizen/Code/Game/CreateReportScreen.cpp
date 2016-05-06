#include "CreateReportScreen.h"

#include "TextDisplayBuilder.h"

#include <fstream>

using namespace ppc;

void ppc::createReportScreen(Desktop &d, World::ReportList report) {

	Entity reportEntity;

	std::ifstream reportFile(World::getReportFile(report));

	std::string content((std::istreambuf_iterator<char>(reportFile)),
						(std::istreambuf_iterator<char>()));

	TextDisplayBuilder reportText;
	reportText.setColor(sf::Color::Red);
	reportText.setFont(World::getFont(World::FontList::Consola));
	reportText.setPosition({ 10,10 });
	reportText.setSize(14);
	reportText.setString(content);

	reportText.create(reportEntity);

	d.getDesktopWindow()->addEntity(reportEntity);


}

