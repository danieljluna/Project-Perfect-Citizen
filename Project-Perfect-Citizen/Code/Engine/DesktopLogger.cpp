
#include "DesktopLogger.h"

using namespace ppc;
using namespace std;

DesktopLogger::DesktopLogger(Desktop& d,ostream& o): 
	loggedDesktop_(&d), out_(o){}

DesktopLogger::~DesktopLogger() {
	loggedDesktop_ = nullptr;
}

void DesktopLogger::addWindow(WindowInterface* wi) {
	out_ << "DesktopLogger: Adding Window: " << wi << endl;

	loggedDesktop_->addWindow(wi);

	out_ << "DesktopLogger: Finished Adding Window" << endl;
}

void DesktopLogger::destroyWindow(WindowInterface* wi) {
	out_ << "DesktopLogger: Destroy Window: " << wi << endl;

	loggedDesktop_->destroyWindow(wi);

	out_ << "DesktopLogger: Finished Destroying Window" << endl;
}

void DesktopLogger::setStyle(OSStyle* oss) {
	out_ << "DesktopLogger: Setting Style" << endl;

	loggedDesktop_->setStyle(oss);

	out_ << "DesktopLogger: Finished Setting Style" << endl;
}

FileState& DesktopLogger::getRoot() {
	out_ << "DesktopLogger: Getting Root" << endl;

	return loggedDesktop_->getRoot();

	out_ << "DesktopLogger: Got Root" << endl;
}

void DesktopLogger::registerInput(sf::Event& ev) {
	out_ << "DesktopLogger: Registering Input Event: " <<
		ev.type << endl;

	loggedDesktop_->registerInput(ev);

	out_ << "DesktopLogger: Finished Registering Input" << endl;
}

void DesktopLogger::update(sf::Time& deltaTime) {
	out_ << "DesktopLogger: Updating Window: "<< loggedDesktop_ << endl;

	loggedDesktop_->update(deltaTime);

	out_ << "DesktopLogger: Finished Updating Window" << endl;
}

void DesktopLogger::refresh(sf::RenderStates states) {
	out_ << "DesktopLogger: Refreshing Window: " <<
		loggedDesktop_ << endl;

	loggedDesktop_->refresh(states);

	out_ << "DesktopLogger: Finished Refreshing Window" << endl;
}