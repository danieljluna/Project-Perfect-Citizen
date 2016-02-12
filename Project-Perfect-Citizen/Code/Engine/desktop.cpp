//desktop.cpp
// Nader Sleem

#include "desktop.h"

ppc::Desktop::Desktop(FileTree& ft) {
	style_ = nullptr;
	fileTree_ = &ft;
}

ppc::Desktop::Desktop(const Desktop& other) {
	this->style_ = other.style_;
	this->fileTree_ = other.fileTree_;
	this->windows_ = other.windows_;
}

ppc::Desktop::~Desktop() {
	if (style_ != nullptr) delete style_;
	//if (fileTree_ != nullptr) delete fileTree_;

	windows_.clear();

}


void ppc::Desktop::focusWindow(WindowInterface* wi) {
	for (auto it = windows_.begin(); it != windows_.end(); ++it) {
		if (*it == wi) {
			//keep swapping it w/ thing before until at front
			auto it2 = it;
			auto temp = it - 1;
			while (it2 != windows_.begin()) {
				auto tempWindow = *it2;
				*it2 = *temp;
				*temp = tempWindow;
				it2 = temp;
				--temp;
			}
			return;
		}
	}
}

void ppc::Desktop::draw(sf::RenderTarget& target, 
						sf::RenderStates states) const {
	//Using reverse itors
	for (auto it = windows_.rbegin(); it != windows_.rend(); ++it) {
		target.draw(*(*it), states);
	}
}


void ppc::Desktop::addWindow(WindowInterface* wi){
	if (wi == nullptr) return;
	//automatically put it at the front,
	//so the new window is focused
	windows_.insert(windows_.begin(), wi);
}

void ppc::Desktop::destroyWindow(WindowInterface* wi) {
	if (wi == nullptr) return;
	for (auto it = windows_.begin(); it != windows_.end(); ++it) {
		if (*it == wi) {
			windows_.erase(it);
			return;
		}
	}
}

void ppc::Desktop::setStyle(OSStyle* oss) {
	style_ = oss;
}

FileState& ppc::Desktop::getRoot() {
	//it is bad to return a reference to a 
	// variable about to go out of scope,
	//but this is only temporary until
	// FileTree and FileState are completed
	float temp = 0.0f;
	return temp;
}

void ppc::Desktop::registerInput(sf::Event& ev){
	//No reverse itors needed
	for (auto it = windows_.begin(); it != windows_.end(); ++it) {
		(*it)->registerInput(ev);
	}
}

void ppc::Desktop::update(sf::Time& deltaTime){
	//No reverse itors needed
	for (auto it = windows_.begin(); it != windows_.end(); ++it) {
		(*it)->update(deltaTime);
	}
}
//ask why we need draw if refresh already calls draw when it is called
void ppc::Desktop::refresh(sf::RenderStates states) {
	//Reverse itors needed
	for (auto it = windows_.rbegin(); it != windows_.rend(); ++it) {
		(*it)->refresh(states);
	}
}