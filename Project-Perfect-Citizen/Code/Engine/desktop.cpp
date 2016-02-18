//desktop.cpp
// Nader Sleem

#include "desktop.h"
#include "debug.h"

ppc::Desktop::Desktop(WindowInterface& bkgndWin, NodeState& n) {
	style_ = nullptr;
	nodeState_ = &n;

	windows_.push_back(&bkgndWin);
	desktopWindow_ = &bkgndWin;
	focused_ = desktopWindow_;
	
}

ppc::Desktop::Desktop(const Desktop& other) {
	this->style_ = other.style_;
	this->nodeState_ = other.nodeState_;
	this->windows_ = other.windows_;
	this->desktopWindow_ = other.desktopWindow_;
	this->focused_ = other.focused_;

}

ppc::Desktop::~Desktop() {
	if (style_ != nullptr) delete style_;
	if (nodeState_ != nullptr) delete nodeState_;
	for (auto it = windows_.begin(); it != windows_.end(); ++it) {
		delete *it;
	}
	focused_ = nullptr;
	desktopWindow_ = nullptr;
	windows_.clear();
}


void ppc::Desktop::focusWindow(WindowInterface* wi) {
	DEBUGF("df", wi);
	//Keep desktopWindow_ in the back of the vector
	if (wi == this->desktopWindow_ || wi == nullptr) {
		this->focused_ = this->desktopWindow_;
		return;
	}
	//while the itor is not desktopWindow_
	for (auto it = windows_.begin(); it != windows_.end(); ++it) {
		//if we find the window to be focused
		if (*it == wi && it != windows_.begin()) {
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
			this->focused_ = *it;
			return;
		}
	}
}

void ppc::Desktop::draw(sf::RenderTarget& target, 
						sf::RenderStates states) const {

	//Draw the background image here first.
	//then:
	//Using reverse itors
	for (auto it = windows_.rbegin(); it != windows_.rend(); ++it) {
		target.draw(*(*it), states);
	}
}


void ppc::Desktop::addWindow(WindowInterface* wi){
	if (wi == nullptr || wi == this->desktopWindow_) return;
	//automatically put it at the front,
	//and focused is set to what was added
	focused_ = *(windows_.insert(windows_.begin(), wi));
}

void ppc::Desktop::destroyWindow(WindowInterface* wi) {
	if (wi == nullptr|| wi == desktopWindow_) return;
	for (auto it = windows_.begin(); it != windows_.end(); ++it) {
		if (*it == wi) {
			windows_.erase(it);
			focusWindow(desktopWindow_);
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

void ppc::Desktop::addBackgroundCmpnt(WindowInterface* wi, sf::Sprite& s) {
	WindowBkgndRenderCmpnt* wBRC = new WindowBkgndRenderCmpnt(s);
	wi->addRenderComponent(wBRC);
}

void ppc::Desktop::registerInput(sf::Event& ev){
	//first check if the mouse clicked in the focused window.
	//if the window clicked in a window that wasnt focused,
	//then focus that window.
	
	if (ev.type == sf::Event::MouseButtonPressed) {
		sf::Vector2i pos(ev.mouseButton.x, ev.mouseButton.y);
		for (auto it = windows_.begin(); it != windows_.end(); ++it) {
			if (isMouseCollision(*it, pos)) {
				focusWindow(*it);
				break;
			}
		}
	}

	focused_->registerInput(ev);

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

bool ppc::Desktop::isMouseCollision(WindowInterface* wi,
	sf::Vector2i pos) {
	
	bool result = false;
	sf::Vector2f windowPos = wi->getPosition();
	sf::Vector2u windowDim = wi->getSize();
	
	if (pos.x >= windowPos.x && pos.x <= windowPos.x + windowDim.x) {
		if (pos.y >= windowPos.y && pos.y <= windowPos.y + windowDim.y) {
			result = true;
		}
	}

	return result;
}