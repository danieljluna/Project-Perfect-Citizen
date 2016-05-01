//desktop.cpp
// Nader Sleem

#ifdef WINDOWS_MARKER
#define resourcePath() std::string("Resources/")
#else
#include "ResourcePath.hpp"
#endif


#include "Window.h"
#include "BorderDecorator.h"

#include <string>

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Event.hpp>

#include "desktop.h"
#include "debug.h"

#include "../Game/WindowBkgndRenderCmpnt.h"
#include "../Game/Inbox.h"
#include "../Game/Email.h"
#include "../Game/emailExtraction.hpp"
#include "../Game/desktopExtractionComponent.hpp"
#include "../Game/PipelineLevelBuilder.h"

#include "frontTopObserver.h"


ppc::Desktop::Desktop() {
	nodeState_.setUp();
	iconSheet_ = sf::Image();
	buttonSheet_ = sf::Image();
	inbox_ = ppc::Inbox();
	background_ = sf::Sprite();
	backgndTexture_ = sf::Texture();
	desktopWindow_ = nullptr;
	focused_ = nullptr;
	frontTop_ = nullptr;


}

ppc::Desktop::Desktop(WindowInterface* bkgndWin, NodeState n) :
          Desktop() {
	nodeState_ = n;
	windows_.push_back(bkgndWin);
	desktopWindow_ = bkgndWin;
	focused_ = desktopWindow_;
	
}

ppc::Desktop::Desktop(const Desktop& other) {
	this->nodeState_ = other.nodeState_;
	this->windows_ = other.windows_;
	this->desktopWindow_ = other.desktopWindow_;
	this->frontTop_ = other.frontTop_;
	this->focused_ = other.focused_;
	this->iconSheet_ = other.iconSheet_;
	this->buttonSheet_ = other.buttonSheet_;
	this->inbox_ = other.inbox_;
}

ppc::Desktop::~Desktop() {
	for (auto it = windows_.begin(); it != windows_.end(); ++it) {
			delete *it;
	}

	for (auto it = solVec_.begin(); it != solVec_.end(); ++it) {
		delete *it;
	}
	for (auto it = playVec_.begin(); it != playVec_.end(); ++it) {
		delete *it;
	}

	if(frontTop_) delete frontTop_;
	frontTop_ = nullptr;
	focused_ = nullptr;
	desktopWindow_ = nullptr;
	windows_.clear();

}


bool ppc::Desktop::focusWindow(WindowInterface* wi) {
	DEBUGF("df", wi);
	//Keep desktopWindow_ in the back of the vector
	if (wi == this->desktopWindow_ || wi == nullptr) {
		this->focused_ = this->desktopWindow_;
		return false;
	}
	//while the itor is not desktopWindow_
	for (auto it = windows_.begin(); it != windows_.end(); ++it) {
		//if we find the window to be focused
			//if it is not at the beginning, we have to put it there.
		if (*it == wi && it != windows_.begin()) {
			//keep swapping it w/ thing before until at front
			auto it2 = it;
			auto temp = it - 1;
			while (it2 != windows_.begin()) {
				auto tempWindow = *it2;
				*it2 = *temp;
				*temp = tempWindow;
				it2 = temp;
				if(temp != windows_.begin()) --temp;
			}
			this->focused_ = windows_.front();
			return true;
			//if it is already at the beginning, then focus it and 
			//stop looping.
		} else if(*it == wi && it == windows_.begin()) {
			this->focused_ = windows_.front();
			return true;
		}
	}
	return false;
}

void ppc::Desktop::draw(sf::RenderTarget& target, 
						sf::RenderStates states) const {

	//Draw the background image here first.
	//then:
	//Using reverse itors
	
	for (auto it = windows_.rbegin(); it != windows_.rend(); ++it) {
		target.draw(*(*it), states);
	}

	if (frontTop_) target.draw(*frontTop_, states);
	
}


void ppc::Desktop::addWindow(WindowInterface* wi){
	if (wi == nullptr || wi == this->desktopWindow_) return;

	//If the Window is already in the Desktop, we merely need
	//to focus it.
    if (!isWindow(wi)) {
        //Otherwise, if wi is not a window in the desktop,
        //automatically put it at the front,
        //and focused is set to what was added
        BorderDecorator* borderOfWi = dynamic_cast<BorderDecorator*>(wi);
        if (borderOfWi != nullptr) {
            //The following creates bounds for dragging Windows.
            sf::FloatRect desktopBounds = desktopWindow_->getBounds();
            sf::FloatRect wiBounds = wi->getBounds();
            sf::FloatRect bounds(desktopBounds);
            bounds.left += 5;
            bounds.top += 34;
            bounds.width -= wiBounds.width;
            bounds.height -= wiBounds.height;
            borderOfWi->setClampBounds(bounds);
        }

        focused_ = *(windows_.insert(windows_.begin(), wi));
    }
}

bool ppc::Desktop::isWindow(WindowInterface* wi) {
    return (std::find(windows_.cbegin(), windows_.cend(), wi) != windows_.cend());
}

void ppc::Desktop::destroyWindow(WindowInterface* wi) {
	if (wi == nullptr || wi == desktopWindow_) return;
	for (auto it = windows_.begin(); it != windows_.end(); ++it) {
		if (*it == wi) {
			delete *it;
			windows_.erase(it);
			focusWindow(desktopWindow_);
			return;
		}
	}
}

void ppc::Desktop::addBkgndWindow(WindowInterface* bkgndWin) {
	windows_.push_back(bkgndWin);
	desktopWindow_ = bkgndWin;
	focused_ = desktopWindow_;
}

void ppc::Desktop::setIconSheet(sf::Image sheet) {
	this->iconSheet_ = sheet;
}

sf::Image& ppc::Desktop::getIconSheet() {
	return iconSheet_;
}

void ppc::Desktop::setButtonSheet(sf::Image sheet) {

	this->buttonSheet_ = sheet;
}

sf::Image& ppc::Desktop::getButtonSheet() {
	return buttonSheet_;
}

ppc::NodeState* ppc::Desktop::getNodeState() {
	return &nodeState_;
}

std::vector<Network*> ppc::Desktop::getSolVec() {
	return solVec_;
}

std::vector<Network*> ppc::Desktop::getPlayVec() {
	return playVec_;
}

int ppc::Desktop::getNetVecIndex() {
	return netVecIndex_;
}

void ppc::Desktop::incrementNetVecIndex() {
	netVecIndex_++;
}

void ppc::Desktop::setNodeState(NodeState n) {
	nodeState_ = n;
}

void ppc::Desktop::setBackgrond(sf::Sprite s) {
	background_ = s;
	if (desktopWindow_ == nullptr) return;
	WindowBkgndRenderCmpnt* wBRC = new WindowBkgndRenderCmpnt(background_);
	desktopWindow_->addRenderComponent(wBRC);
	
}

ppc::InputHandler& ppc::Desktop::getInputHandler() {
	return desktopWindow_->getInputHandler();
}

ppc::WindowInterface* ppc::Desktop::getDesktopWindow() {
	return desktopWindow_;
}

void ppc::Desktop::setInbox(Inbox i) {
	inbox_ = i;
}

ppc::Inbox& ppc::Desktop::getInbox() {
	return inbox_;
}

void ppc::Desktop::setFrontTop(WindowInterface* front) {
	frontTop_ = front;

    frontTopObsvr* ftObsvr = new frontTopObsvr(*this);

    mousePressButton *mpb = new mousePressButton();
    mpb->setFloatRect(frontTop_->getBounds());
    mpb->setInputHandle(frontTop_->getInputHandler());
	mpb->onClick().addObserverToBack(ftObsvr);
	mpb->onHover().addObserverToBack(ftObsvr);
	mpb->onRelease().addObserverToBack(ftObsvr);
    mpb->onAll().addObserverToBack(ftObsvr);

    frontTop_->addInputComponent(mpb);
}

void ppc::Desktop::deleteFrontTop() {
	if (frontTop_) {
		delete frontTop_;
		frontTop_ = nullptr;
	}
}

void ppc::Desktop::registerInput(Event ppcEv) {
    sf::Event ev(ppcEv);
	if ((frontTop_ != nullptr) && 
		(ev.type == sf::Event::MouseButtonPressed || 
			ev.type == sf::Event::MouseButtonReleased)) {
		frontTop_->registerInput(ev);
	} else {
		registerInputFocused(ev);
	}

}

void ppc::Desktop::registerInputFocused(Event ppcEv) {
//first check if the mouse clicked in the focused window.
//if the window clicked in a window that wasnt focused,
//then focus that window.
//for any mouse event
    sf::Event ev(ppcEv);
	if (ev.type == sf::Event::MouseButtonPressed) {
		for (auto it = windows_.begin(); it != windows_.end(); ++it) {
			sf::FloatRect winBounds = (*it)->getBounds();
			if (winBounds.contains(float(ev.mouseButton.x), float(ev.mouseButton.y))) {
				focusWindow(*it);
				break;
			}
		}
	}

	if (ev.type == sf::Event::MouseMoved) {
		ev.mouseMove.x -= int(focused_->getPosition().x);
		ev.mouseMove.y -= int(focused_->getPosition().y);
	} else if ((ev.type == sf::Event::MouseButtonPressed) || (ev.type == sf::Event::MouseButtonReleased)) {
		ev.mouseButton.x -= int(focused_->getPosition().x);
		ev.mouseButton.y -= int(focused_->getPosition().y);
	}

	focused_->registerInput(ev);
}

void ppc::Desktop::update(sf::Time& deltaTime){
	//No reverse itors needed
	for (size_t i = 0; i < windows_.size(); ) {
		windows_.at(i)->update(deltaTime);
		if (!windows_.at(i)->isOpen()) {
			delete windows_.at(i);
			windows_.erase(windows_.begin() + i);
			focusWindow(desktopWindow_);
		} else {
			++i;
		}
		//dont increment if you delete it
	}
}

void ppc::Desktop::refresh(sf::RenderStates states) {
	//Reverse itors needed
	for (auto it = windows_.rbegin(); it != windows_.rend(); ++it) {
		(*it)->refresh(states);
	}

	if (frontTop_) frontTop_->refresh(states);
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

void ppc::Desktop::clearDesktop() {
	nodeState_ = ppc::NodeState();
	nodeState_.setUp();
	iconSheet_ = sf::Image();
	buttonSheet_ = sf::Image();
	inbox_ = ppc::Inbox();
	background_ = sf::Sprite();
	backgndTexture_ = sf::Texture();
	desktopWindow_ = nullptr;
	focused_ = nullptr;
	windows_.clear();
	if (frontTop_) delete frontTop_;
	frontTop_ = nullptr;

}


std::istream& ppc::operator>>(std::istream& in, ppc::Desktop& desktop) {
	std::string line;

	ppc::Desktop* importDesktop = &desktop;
	importDesktop->clearDesktop();
	ppc::Window* bkgndWindow = 
		new Window(1800, 1000, sf::Color(0, 0, 0));
	importDesktop->addBkgndWindow(bkgndWindow);

	while (std::getline(in, line)) {
		size_t pos = line.find_first_of(":");
		std::string key = line.substr(0, pos);
		std::string file = line.substr(pos + 2);
		//DEBUGF("wc", key << " " << file)
		if (key == "Icons") {
			importDesktop->iconSheet_.loadFromFile(resourcePath() + file);

		} else if (key == "Buttons") {
			importDesktop->buttonSheet_.loadFromFile(resourcePath() + file);

		} else if (key == "Background") {
			importDesktop->backgndTexture_.loadFromFile(resourcePath() + file);
			importDesktop->background_.setScale(0.7f, 0.7f);
			importDesktop->background_.setPosition(0.f, 0.f);
			importDesktop->background_.setTexture(importDesktop->backgndTexture_);
			WindowBkgndRenderCmpnt* wBRC = 
				new WindowBkgndRenderCmpnt(importDesktop->background_);
			importDesktop->desktopWindow_->addRenderComponent(wBRC);

		} else if (key == "Filetree") {
			ppc::desktopExtractionComponent desktopFiles(importDesktop->nodeState_);
			Json::Value parsed =
				desktopFiles.parseDesktopAsJson(resourcePath() + file, "Desktop");
		} else if (key == "Emails") {
			ppc::emailExtraction* inbox = new emailExtraction();
			inbox->parseEmailAsJson(file);
			
			for (unsigned int i = 0; i < inbox->getSubject().size(); i++) {
				ppc::Email* testEmail1 = new Email(inbox->getTo().at(i),
					inbox->getFrom().at(i),
					inbox->getSubject().at(i),
					inbox->getBody().at(i),
                    inbox->getVisible().at(i),
					"image.jpg");
				importDesktop->getInbox().addEmailToList(testEmail1);
			}
			delete inbox;
		} else if (key == "Pipeline") {
			if (PipelineLevelBuilder::LEVEL_MAP.find(file) ==
				PipelineLevelBuilder::LEVEL_MAP.end()) {
				DEBUGF("wc", key << " " << file);
				continue;
			}
			desktop.netVecIndex_ = 0;
			int levelnum = PipelineLevelBuilder::LEVEL_MAP.at(file);
			Network* solNet;
			switch (levelnum) {
				case -1:
					solNet = PipelineLevelBuilder::buildTutorialOne();
					break;
				case 0:
					solNet = PipelineLevelBuilder::buildTutorialTwo();
					break;
				case 1:
					solNet = PipelineLevelBuilder::buildLevelOneNetworkSolution();
					break;
				default:
					DEBUGF("wc", levelnum);
					break;
			}
			desktop.solVec_.push_back(solNet);
			desktop.playVec_.push_back(solNet->copyNetworkByVerts());
		}
	}

	return in;
}