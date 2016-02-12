//desktop.cpp
// Nader Sleem

#include "desktop.h"

ppc::Desktop::Desktop(NodeState& n) {
	style_ = nullptr;
	nodeState_ = &n;
}

ppc::Desktop::Desktop(const Desktop& other) {
	this->style_ = other.style_;
	this->nodeState_ = other.nodeState_;
	this->windows_ = other.windows_;
}

ppc::Desktop::~Desktop() {
	if (style_ != nullptr) delete style_;
	if (nodeState_ != nullptr) delete nodeState_;

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

ppc::NodeState& ppc::Desktop::getNodeState() {

	return *nodeState_;
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

void ppc::Desktop::refresh(sf::RenderStates states) {
	//Reverse itors needed
	for (auto it = windows_.rbegin(); it != windows_.rend(); ++it) {
		(*it)->refresh(states);
	}
}