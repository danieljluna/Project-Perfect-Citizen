#include "../Engine/debug.h"
#include "iconInputComponent.h"
#include <iostream>
#include <string>
#include "../Engine/desktop.h"
#include "../Game/emailExtraction.hpp"
#include "../Engine/Audio/AudioQueue.h"


using namespace ppc;

iconInputComponent::iconInputComponent(Desktop& dT, Database* dB, Inbox& ib, sf::Image& bS, sf::Image& iS, IconType type)
	: theDesktop_(dT), theDatabase_(dB), theInbox_(ib), buttonSheet_(bS), iconSheet_(iS), que(5), type_(type) {
        

}



void iconInputComponent::recieveMessage(msgType msg) {
    
}

void ppc::iconInputComponent::recieveMessage(ppc::Event ev) {
    //If out button was clicked
    if (Event::ButtonType == ev.type) {

        if (ev.buttons.activation == ev.buttons.RightMouse) {

            std::vector<std::string> elementNames;
            std::vector<bool(*)(Desktop*, Event ev)> elementFunctions;
            elementNames.push_back("Open");
            ppc::WindowInterface* ContextMenu = nullptr;
            ContextMenu = new ppc::Window(200, 300, sf::Color(170, 170, 170));
         //   elementFunctions.push_back(&(ppc::make_icon_window));

            switch (type_) {
			case Event::OpenEv::Email:
				spawnContextMenu(theDesktop_, ContextMenu, ContextMenu->getInputHandler(), elementNames,
					elementFunctions, ev.buttons.mousePos.x, ev.buttons.mousePos.y);
				break;
            case Event::OpenEv::Browser:
                spawnContextMenu(theDesktop_, ContextMenu, ContextMenu->getInputHandler(), elementNames,
                    elementFunctions, ev.buttons.mousePos.x, ev.buttons.mousePos.y);
                break;
            case Event::OpenEv::HardDrive:
                spawnContextMenu(theDesktop_, ContextMenu, ContextMenu->getInputHandler(), elementNames,
                    elementFunctions, ev.buttons.mousePos.x, ev.buttons.mousePos.y);
                break;
            case Event::OpenEv::Help:
                spawnContextMenu(theDesktop_, ContextMenu, ContextMenu->getInputHandler(), elementNames,
                    elementFunctions, ev.buttons.mousePos.x, ev.buttons.mousePos.y);
                break;
            case Event::OpenEv::Pipeline:
                spawnContextMenu(theDesktop_, ContextMenu, ContextMenu->getInputHandler(), elementNames,
                    elementFunctions, ev.buttons.mousePos.x, ev.buttons.mousePos.y);
                break;
            case Event::OpenEv::Search:
                spawnContextMenu(theDesktop_, ContextMenu, ContextMenu->getInputHandler(), elementNames,
                    elementFunctions, ev.buttons.mousePos.x, ev.buttons.mousePos.y);
                break;
            case Event::OpenEv::Chat:
                spawnContextMenu(theDesktop_, ContextMenu, ContextMenu->getInputHandler(), elementNames,
                    elementFunctions, ev.buttons.mousePos.x, ev.buttons.mousePos.y);
                break;
            case Event::OpenEv::Settings:
                spawnContextMenu(theDesktop_, ContextMenu, ContextMenu->getInputHandler(), elementNames,
                    elementFunctions, ev.buttons.mousePos.x, ev.buttons.mousePos.y);
                break;
            case Event::OpenEv::Folder:
                spawnContextMenu(theDesktop_, ContextMenu, ContextMenu->getInputHandler(), elementNames,
                    elementFunctions, ev.buttons.mousePos.x, ev.buttons.mousePos.y);
                break;
            case Event::OpenEv::Console:
                spawnContextMenu(theDesktop_, ContextMenu, ContextMenu->getInputHandler(), elementNames,
                    elementFunctions, ev.buttons.mousePos.x, ev.buttons.mousePos.y);
                break;
            }

            theDesktop_.addWindow(ContextMenu);

        } else if (ev.buttons.activation == ev.buttons.LeftMouse &&
                   ev.buttons.state == Event::ButtonsEv::DblClicked) {

            WindowInterface* tempWin = nullptr;

            switch (type_) {
                // Case: Double Clicked Console Icon
            case IconType::Console:
                if (openedWindow != nullptr && theDesktop_.isWindow(openedWindow)) {
                    theDesktop_.focusWindow(openedWindow);
                } else {
                    tempWin = new Window(500, 2000, sf::Color(0, 0, 0));
                    spawnConsole(theDesktop_, tempWin, tempWin->getInputHandler(),
                        *theDesktop_.getNodeState(), buttonSheet_, 200, 200);
                    theDesktop_.addWindow(tempWin);
                    openedWindow = tempWin;
                }
                break;

            case IconType::File :  //Originally File....Not in use?
                if (openedWindow != nullptr && theDesktop_.isWindow(openedWindow)) {
                    theDesktop_.focusWindow(openedWindow);
                } else {
                    tempWin = new ppc::Window(500, 500, sf::Color(255, 255, 255));
                    spawnFile(tempWin, tempWin->getInputHandler(),
                        *theDesktop_.getNodeState(), buttonSheet_, 100, 200, "CHANGE_ME.JPG", "DesktopContent/Desktop1/3-29-12-184.jpg");
                    theDesktop_.addWindow(tempWin);
                    openedWindow = tempWin;
                }
                break;
            case IconType::Settings:
                if (openedWindow != nullptr && theDesktop_.isWindow(openedWindow)) {
                    theDesktop_.focusWindow(openedWindow);
                } else {
                    tempWin = new ppc::Window(500, 150, sf::Color(170, 170, 170));
                    spawnErrorMessage(tempWin, tempWin->getInputHandler(), buttonSheet_, 100, 200, "Error: Invalid permissions level.");
                    theDesktop_.addWindow(tempWin);
                    openedWindow = tempWin;
                }
                break;
            case IconType::Chat:
                if (openedWindow != nullptr && theDesktop_.isWindow(openedWindow)) {
                    theDesktop_.focusWindow(openedWindow);
                } else {
                    tempWin = new ppc::Window(500, 150, sf::Color(170, 170, 170));
                    spawnErrorMessage(tempWin, tempWin->getInputHandler(), buttonSheet_, 100, 200, "Error: Invalid permissions level.");
                    theDesktop_.addWindow(tempWin);
                    openedWindow = tempWin;
                }
                break;
            case IconType::Search:
                if (openedWindow != nullptr && theDesktop_.isWindow(openedWindow)) {
                    theDesktop_.focusWindow(openedWindow);
                } else {
                    tempWin = new Window(800, 600, sf::Color(200, 200, 200));
                    spawnDatabase(tempWin, tempWin->getInputHandler(), theDatabase_, buttonSheet_, 100, 200);
                    theDesktop_.addWindow(tempWin);
                    openedWindow = tempWin;
                }
                break;
            case IconType::Pipeline:
                if (openedWindow != nullptr && theDesktop_.isWindow(openedWindow)) {
                    theDesktop_.focusWindow(openedWindow);
                } else {
                    tempWin = new ppc::Window(800, 600, sf::Color(200, 200, 200));
                    ppc::spawnPipeline(tempWin, tempWin->getInputHandler(), theDatabase_, buttonSheet_, 100, 200);
                    theDesktop_.addWindow(tempWin);
                    openedWindow = tempWin;
                }
                break;
            case IconType::Help:
                tempWin = new ppc::Window(600, 700, sf::Color(200, 200, 200));
                spawnHelp(tempWin, tempWin->getInputHandler(), buttonSheet_, 100, 100);
                theDesktop_.addWindow(tempWin);
                openedWindow = tempWin;
                break;
            case IconType::Browser:
                if (openedWindow != nullptr && theDesktop_.isWindow(openedWindow)) {
                    theDesktop_.focusWindow(openedWindow);
                } else {
                    tempWin = new ppc::Window(500, 150, sf::Color(170, 170, 170));
                    spawnPromptMessage(tempWin, tempWin->getInputHandler(), buttonSheet_, 100, 200, "Prompt: please enter password");
                    que.addSound("prompt", "Notification_Prompt.wav");
                    que.playSound(0);
                    que.popAndPlay();
                    theDesktop_.addWindow(tempWin);
                    openedWindow = tempWin;
                }
                break;
            case IconType::HardDrive: //Was Explorer
                //if (openedWindow != nullptr && theDesktop_.isWindow(openedWindow)) {
                //theDesktop_.focusWindow(openedWindow);
                //}
                //else {
                tempWin = new ppc::Window(600, 350, sf::Color(255, 255, 255));
                spawnExplorer(theDesktop_, tempWin, tempWin->getInputHandler(), *theDesktop_.getNodeState(), buttonSheet_, iconSheet_, 100, 200);
                theDesktop_.addWindow(tempWin);
                openedWindow = tempWin;
                //}
                break;
            case IconType::Email:
                if (openedWindow != nullptr && theDesktop_.isWindow(openedWindow)) {
                    theDesktop_.focusWindow(openedWindow);
                } else {
                    tempWin = new ppc::Window(600, 400, sf::Color(200, 200, 200));
                    ppc::spawnInbox(theDesktop_, tempWin, tempWin->getInputHandler(), buttonSheet_, 100, 200, theDesktop_.getInbox());
                    theDesktop_.addWindow(tempWin);
                    openedWindow = tempWin;
                }
                break;
            }

            ev.type = Event::OpenType;
            ev.open.window = tempWin;
            ev.open.winType = type_;
            onOpen_.sendEvent(ev);

        }

	}
	
}


iconInputComponent::~iconInputComponent() {

}

bool iconInputComponent::registerInput(Event ev) {
	return true;
}

bool ppc::make_icon_window(Desktop* ptr, ppc::Event ev) {
    
    std::cout << "A Context Menu was clicked" << std::endl;

	return true;
}
