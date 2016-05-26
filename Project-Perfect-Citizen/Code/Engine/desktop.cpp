//desktop.cpp
// Nader Sleem

#ifdef WINDOWS_MARKER
#define resourcePath() std::string("Resources/")
#else
#include "ResourcePath.hpp"
#endif

#include <string>
#include <fstream>

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Event.hpp>

#include "Window.h"
#include "BorderDecorator.h"
#include "World.h"
#include "Network.h"

#include "desktop.h"
#include "debug.h"

#include "../Game/WindowBkgndRenderCmpnt.h"
#include "../Game/Inbox.h"
#include "../Game/Email.h"
#include "../Game/emailExtraction.hpp"
#include "../Game/desktopExtractionComponent.hpp"
#include "../Game/PipelineLevelBuilder.h"

#include "frontTopObserver.h"

using namespace ppc;


ppc::Desktop::Desktop() {
	nodeState_.setUp();
	iconSheet_ = sf::Image();
	buttonSheet_ = sf::Image();
	inbox_ = ppc::Inbox();
	background_ = sf::Sprite();
	backgndTexture_ = sf::Texture();
	frontTop_ = nullptr;

	desktopWindow_ = new Window(1800, 1000);
	windows_.push_back(desktopWindow_);
	focused_ = desktopWindow_;

}

ppc::Desktop::Desktop(WindowInterface* bkgndWin, NodeState n) :
          Desktop() {

	windows_.clear(); //these 3 steps must be done because of default Ctor
	desktopWindow_ = nullptr;
	focused_ = nullptr;

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
        if (*it != nullptr)
            delete *it;
	}

	for (auto it = solVec_.begin(); it != solVec_.end(); ++it) {
        if (*it != nullptr)
            delete *it;
	}
	for (auto it = playVec_.begin(); it != playVec_.end(); ++it) {
		if (*it != nullptr)
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
        if ((*it)->getNotifWindow() != nullptr) {
            target.draw(*(*it)->getNotifWindow(), states);
        }
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

void ppc::Desktop::setFrontTop(WindowInterface* front, bool prop) {

    frontTopObsvr* ftObsvr = new frontTopObsvr(*this, prop);

    mousePressButton *mpb = new mousePressButton();
    mpb->setFloatRect(front->getBounds());
    mpb->setInputHandle(front->getInputHandler());
	mpb->onClick().addObserverToBack(ftObsvr);
	mpb->onHover().addObserverToBack(ftObsvr);
	mpb->onRelease().addObserverToBack(ftObsvr);
    mpb->onAll().addObserverToBack(ftObsvr);

	if (frontTop_) {
		nextFrontTop_ = front;
		nextFrontTop_->addInputComponent(mpb);
	} else {
		frontTop_ = front;
		frontTop_->addInputComponent(mpb);
	}
}

WindowInterface* ppc::Desktop::getFrontTop() {
	return frontTop_;
}

void ppc::Desktop::deleteFrontTop() {
	if (frontTop_) {
		delete frontTop_;
		frontTop_ = nullptr;
	}
}

void ppc::Desktop::registerInput(Event ppcEv) {
    
	if ((frontTop_ != nullptr) && (ppcEv.type == Event::sfEventType) &&
		(ppcEv.sfEvent.type == sf::Event::MouseButtonPressed || 
			ppcEv.sfEvent.type == sf::Event::MouseButtonReleased)) {
		frontTop_->registerInput(ppcEv);
		if (nextFrontTop_ != nullptr) {
			delete frontTop_;
			frontTop_ = nextFrontTop_;
			nextFrontTop_ = nullptr;
		}
	} else {
		registerInputFocused(ppcEv);
	}

}

void ppc::Desktop::registerInputFocused(Event ppcEv) {
//first check if the mouse clicked in the focused window.
//if the window clicked in a window that wasnt focused,
//then focus that window.
//for any mouse event

	if (ppcEv.type == Event::sfEventType) {
		if (ppcEv.sfEvent.type == sf::Event::MouseButtonPressed) {
			for (auto it = windows_.begin(); it != windows_.end(); ++it) {
                sf::FloatRect winBounds;
                if ((*it)->getNotifWindow() != nullptr) {
                    winBounds = (*it)->getNotifWindow()->getBounds();
                    if (winBounds.contains(
                        float(ppcEv.sfEvent.mouseButton.x),
                        float(ppcEv.sfEvent.mouseButton.y))) {
                        focusWindow(*it);
                        break;
                    }
                }
                winBounds = (*it)->getBounds();
                if (winBounds.contains(
                        float(ppcEv.sfEvent.mouseButton.x),
                        float(ppcEv.sfEvent.mouseButton.y))) {
                    focusWindow(*it);
                    break;
                }
			}
		}
		if (ppcEv.sfEvent.type == sf::Event::MouseMoved) {
            if (focused_->getNotifWindow() == nullptr) {
                ppcEv.sfEvent.mouseMove.x -= int(focused_->getPosition().x);
                ppcEv.sfEvent.mouseMove.y -= int(focused_->getPosition().y);
            } else {
                ppcEv.sfEvent.mouseMove.x -= int(focused_->getNotifWindow()->getPosition().x);
                ppcEv.sfEvent.mouseMove.y -= int(focused_->getNotifWindow()->getPosition().y);
            }
		} else if ((ppcEv.sfEvent.type == sf::Event::MouseButtonPressed) || 
			(ppcEv.sfEvent.type == sf::Event::MouseButtonReleased)) {

            if (focused_->getNotifWindow() == nullptr) {
                ppcEv.sfEvent.mouseButton.x -= int(focused_->getPosition().x);
                ppcEv.sfEvent.mouseButton.y -= int(focused_->getPosition().y);
            } else {
                ppcEv.sfEvent.mouseButton.x -= int(focused_->getNotifWindow()->getPosition().x);
                ppcEv.sfEvent.mouseButton.y -= int(focused_->getNotifWindow()->getPosition().y);
            }
		}
	}
	

    if ((ppcEv.type == Event::sfEventType) &&
        (ppcEv.sfEvent.type == sf::Event::MouseButtonReleased)) {

        auto winCopy(windows_);
        
        for (auto it: winCopy) {
            it->registerInput(ppcEv);
            if (it->getNotifWindow() != nullptr) {
                it->getNotifWindow()->registerInput(ppcEv);
            }
        }

    } else {
        if (focused_->getNotifWindow() == nullptr) {
            focused_->registerInput(ppcEv);
        } else {
            focused_->getNotifWindow()->registerInput(ppcEv);
        }
    }
}

void ppc::Desktop::update(sf::Time& deltaTime){
	//No reverse itors needed
	for (size_t i = 0; i < windows_.size(); ) {
		windows_.at(i)->update(deltaTime);
        if ((windows_.at(i)->getNotifWindow() != nullptr) &&
            (!windows_.at(i)->getNotifWindow()->isOpen())) {
            windows_.at(i)->createNotifWindow(nullptr, true);
            focusWindow(windows_.at(i));
        }
		if (!windows_.at(i)->isOpen()) {
			delete windows_.at(i);
			windows_.erase(windows_.begin() + i);
			focusWindow(desktopWindow_);
		}
		else {
			++i;
		}
		//dont increment if you delete it
	}

    if (frontTop_ != nullptr) {
         frontTop_->update(deltaTime);
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
	if (frontTop_) delete frontTop_;
	frontTop_ = nullptr;

	for (auto it = windows_.begin(); it != windows_.end(); ++it) {
		if (*it != nullptr)
			delete *it;
	}

	for (auto it = solVec_.begin(); it != solVec_.end(); ++it) {
		if (*it != nullptr)
			delete *it;
	}
	for (auto it = playVec_.begin(); it != playVec_.end(); ++it) {
		if (*it != nullptr)
			delete *it;
	}

	windows_.clear();
	solVec_.clear();
	playVec_.clear();
	netVecIndex_ = 0;
}


std::ifstream& ppc::operator>>(std::ifstream& in, ppc::Desktop& desktop) {
	std::string line;

	ppc::Desktop* importDesktop = &desktop;
	importDesktop->clearDesktop();
	ppc::Window* bkgndWindow = 
		new Window(1800, 1000, sf::Color(0, 0, 0));
	importDesktop->addBkgndWindow(bkgndWindow);

	auto streamPos = in.tellg();
	in.seekg(0, in.end);
	auto end = in.tellg();
	in.seekg(streamPos);

	int lineCount = 0;
	while (std::getline(in, line)) {
		streamPos = in.tellg();
		size_t pos = line.find_first_of(":");
		if (pos == std::string::npos) continue;
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
				desktopFiles.parseDesktopAsJson(file, "Desktop");
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
			desktop.netVecIndex_ = 0;
			int levelnum;
			if (PipelineLevelBuilder::LEVEL_MAP.find(file) != PipelineLevelBuilder::LEVEL_MAP.end()) {
				levelnum = PipelineLevelBuilder::LEVEL_MAP.at(file);
			} 
			else {
				DEBUGF("wc", key << " " << file);
				levelnum = -2;
			}

			
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
				case 2:
					solNet = PipelineLevelBuilder::buildLevelTwoANetworkSolution();
					break;
				case 3:
					solNet = PipelineLevelBuilder::buildLevelTwoBNetworkSolution();
					break;
				case 4:
					solNet = PipelineLevelBuilder::buildLevelThreeNetworkSolution();
					break;
				default:
					solNet = PipelineLevelBuilder::buildDefaultNetwork();
					DEBUGF("wc", levelnum);
					break;
			}
			desktop.solVec_.push_back(solNet);
			Network* playNet = solNet->copyNetworkByVerts();
			desktop.playVec_.push_back(playNet);
		}
		//num of parsed line / total # of lines 
		World::setLoading((float)(1 - ((float)(end - streamPos) / (float)end)));

	}

	return in;
}