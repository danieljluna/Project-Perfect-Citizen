
#include "DesktopLogger.h"

using namespace ppc;
using namespace std;

DesktopLogger::DesktopLogger(Desktop& d,ostream& o): 
	loggedDesktop(&d), out(o){}

DesktopLogger::~DesktopLogger() {
	loggedDesktop = nullptr;
}

void DesktopLogger::addWindow(WindowInterface* wi) {
	out << "DesktopLogger: Adding Window: " << wi << endl;

	loggedDesktop->addWindow(wi);

	out << "DesktopLogger: Finished Adding Window" << endl;
}

void DesktopLogger::destroyWindow(WindowInterface* wi) {
	out << "DesktopLogger: Destroy Window: " << wi << endl;

	loggedDesktop->destroyWindow(wi);

	out << "DesktopLogger: Finished Destroying Window" << endl;
}

void DesktopLogger::setStyle(OSStyle* oss) {
	out << "DesktopLogger: Setting Style" << endl;

	loggedDesktop->setStyle(oss);

	out << "DesktopLogger: Finished Setting Style" << endl;
}

FileState& DesktopLogger::getRoot() {
	out << "DesktopLogger: Getting Root" << endl;

	return loggedDesktop->getRoot();

	out << "DesktopLogger: Got Root" << endl;
}

void DesktopLogger::registerInput(sf::Event& ev) {
	out << "DesktopLogger: Registering Input Event: " << 
		ev.type << endl;

	loggedDesktop->registerInput(ev);

	out << "DesktopLogger: Finished Registering Input" << endl;
}

void DesktopLogger::update(sf::Time& deltaTime) {
	out << "DesktopLogger: Updating Window: "<< loggedDesktop << endl;

	loggedDesktop->update(deltaTime);

	out << "DesktopLogger: Finished Updating Window" << endl;
}

void DesktopLogger::refresh(sf::RenderStates states) {
	out << "DesktopLogger: Refreshing Window: " << 
		loggedDesktop << endl;

	loggedDesktop->refresh(states);

	out << "DesktopLogger: Finished Refreshing Window" << endl;
}