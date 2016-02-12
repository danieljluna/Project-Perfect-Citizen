
#include "DesktopLogger.h"

using namespace ppc;


DesktopLogger::DesktopLogger(Desktop& d,ostream& o): 
	loggedDesktop_(&d), out_(o){}

DesktopLogger::~DesktopLogger() {
	loggedDesktop_ = nullptr;
}

void DesktopLogger::addWindow(WindowInterface* wi) {
	out_ << "DesktopLogger: Adding Window: " << wi << std::endl;

	loggedDesktop_->addWindow(wi);

	out_ << "DesktopLogger: Finished Adding Window" << std::endl;
}

void DesktopLogger::destroyWindow(WindowInterface* wi) {
	out_ << "DesktopLogger: Destroy Window: " << wi << std::endl;

	loggedDesktop_->destroyWindow(wi);

	out_ << "DesktopLogger: Finished Destroying Window" << std::endl;
}

void DesktopLogger::setStyle(OSStyle* oss) {
	out_ << "DesktopLogger: Setting Style" << std::endl;

	loggedDesktop_->setStyle(oss);

	out_ << "DesktopLogger: Finished Setting Style" << std::endl;
}

const BaseFileType& DesktopLogger::getRoot() {
	out_ << "DesktopLogger: Getting Root" << std::endl;

	return loggedDesktop_->getRoot();

	out_ << "DesktopLogger: Got Root" << std::endl;
}

void DesktopLogger::registerInput(sf::Event& ev) {
	out_ << "DesktopLogger: Registering Input Event: " <<
		ev.type << std::endl;

	loggedDesktop_->registerInput(ev);

	out_ << "DesktopLogger: Finished Registering Input" << std::endl;
}

void DesktopLogger::update(sf::Time& deltaTime) {
	out_ << "DesktopLogger: Updating Window: "<< 
		loggedDesktop_ << std::endl;

	loggedDesktop_->update(deltaTime);

	out_ << "DesktopLogger: Finished Updating Window" << std::endl;
}

void DesktopLogger::refresh(sf::RenderStates states) {
	out_ << "DesktopLogger: Refreshing Window: " <<
		loggedDesktop_ << std::endl;

	loggedDesktop_->refresh(states);

	out_ << "DesktopLogger: Finished Refreshing Window" << std::endl;
}