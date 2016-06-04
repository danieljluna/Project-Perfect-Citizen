#include "../Engine/debug.h"
#include "iconInputComponent.h"


#include <iostream>
#include <string>

#include "../Engine/desktop.h"
#include "../Engine/World.h"
#include "../Engine/Window.h"

#include "TreeCommands.h"
#include "ContextBuilder.h"
#include "emailExtraction.hpp"
#include "createWindow.h"
#include "explorerFileInputComponent.h"
#include "createWindow.h"
#include "../Engine/SuspiciousFileHolder.h"

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
            
            //que.addSound("click", "Mouse_Down.wav");
            //que.playSound(0);
            //que.popAndPlay();
          

			/* Begin Building Context List */
			ppc::WindowInterface* ContextMenu = nullptr;
			ContextMenu = new ppc::Window(200, 300, sf::Color(170, 170, 170));
			ContextBuilder builder;
			std::vector<ppc::Entity> listElements;
			Entity listElement;
			float fontSize = 20.0f;
			float fontPadding = 2.0f;

			/* First Element: 'Open' */
			builder.setContainingWindow(ContextMenu);
			builder.setInputHandle(ContextMenu->getInputHandler());
			builder.setLabelFont(World::getFont(World::Consola));
			builder.setLabelMessage("Open");
			builder.setLabelSize((int) fontSize);
			builder.setListElementPosition(0, 0);
			builder.setListElementSize({ ContextMenu->getBounds().width, fontSize + fontPadding });

            switch (type_) {
			case Event::OpenEv::Email:
				createWithEventFunc(builder, listElement, this, ppc::make_icon_window);
				listElements.push_back(listElement);
				spawnContextMenu(ContextMenu, listElements, static_cast<float>(ev.buttons.mousePos.x), static_cast<float>(ev.buttons.mousePos.y));
				break;
            case Event::OpenEv::Browser:
				createWithEventFunc(builder, listElement, this, ppc::make_icon_window);
				listElements.push_back(listElement);
				spawnContextMenu(ContextMenu, listElements, static_cast<float>(ev.buttons.mousePos.x), static_cast<float>(ev.buttons.mousePos.y));
                break;
            case Event::OpenEv::HardDrive:
				createWithEventFunc(builder, listElement, this, ppc::make_icon_window);
				listElements.push_back(listElement);
				spawnContextMenu(ContextMenu, listElements, static_cast<float>(ev.buttons.mousePos.x), static_cast<float>(ev.buttons.mousePos.y));
                break;
            case Event::OpenEv::Help:
				createWithEventFunc(builder, listElement, this, ppc::make_icon_window);
				listElements.push_back(listElement);
				spawnContextMenu(ContextMenu, listElements, static_cast<float>(ev.buttons.mousePos.x), static_cast<float>(ev.buttons.mousePos.y));
                break;
            case Event::OpenEv::Pipeline:
				createWithEventFunc(builder, listElement, this, ppc::make_icon_window);
				listElements.push_back(listElement);
				spawnContextMenu(ContextMenu, listElements, static_cast<float>(ev.buttons.mousePos.x), static_cast<float>(ev.buttons.mousePos.y));
                break;
            case Event::OpenEv::Search:
				createWithEventFunc(builder, listElement, this, ppc::make_icon_window);
				listElements.push_back(listElement);
				spawnContextMenu(ContextMenu, listElements, static_cast<float>(ev.buttons.mousePos.x), static_cast<float>(ev.buttons.mousePos.y));
                break;
            case Event::OpenEv::Chat:
				createWithEventFunc(builder, listElement, this, ppc::make_icon_window);
				listElements.push_back(listElement);
				spawnContextMenu(ContextMenu, listElements, static_cast<float>(ev.buttons.mousePos.x), static_cast<float>(ev.buttons.mousePos.y));
                break;
            case Event::OpenEv::Settings:
				createWithEventFunc(builder, listElement, this, ppc::make_icon_window);
				listElements.push_back(listElement);
				spawnContextMenu(ContextMenu, listElements, static_cast<float>(ev.buttons.mousePos.x), static_cast<float>(ev.buttons.mousePos.y));
                break;
            case Event::OpenEv::Folder:
				createWithEventFunc(builder, listElement, this, ppc::make_icon_window);
				listElements.push_back(listElement);
				spawnContextMenu(ContextMenu, listElements, static_cast<float>(ev.buttons.mousePos.x), static_cast<float>(ev.buttons.mousePos.y));
                break;
            case Event::OpenEv::Console:
				createWithEventFunc(builder, listElement, this, ppc::make_icon_window);
				listElements.push_back(listElement);
				spawnContextMenu(ContextMenu, listElements, static_cast<float>(ev.buttons.mousePos.x), static_cast<float>(ev.buttons.mousePos.y));
                break;
			case Event::OpenEv::File:
				createWithEventFunc(builder, listElement, this, ppc::make_icon_window);
				listElements.push_back(listElement);

				Entity listElement2;
				builder.setLabelMessage("Scan");
				builder.setListElementPosition(0, fontSize + fontPadding);
				builder.setLabelPosition({ 0.0f, fontSize + fontPadding });
				createWithEventFunc(builder, listElement2, this, ppc::spawn_desktop_prompt_msg);
				listElements.push_back(listElement2);

				Entity listElement3;
				builder.setLabelMessage("Flag");
				builder.setListElementPosition(0, (fontSize + fontPadding) * 2);
				builder.setLabelPosition({ 0.0f, (fontSize + fontPadding) * 2 });
				createWithEventFunc(builder, listElement3, this, ppc::flag_desktop_file);
				listElements.push_back(listElement3);

				spawnContextMenu(ContextMenu, listElements, static_cast<float>(ev.buttons.mousePos.x), static_cast<float>(ev.buttons.mousePos.y));
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
					theDesktop_.getNodeState()->readFile(labelName);
                }
                break;
            case IconType::Settings:
                if (openedWindow != nullptr && theDesktop_.isWindow(openedWindow)) {
                    theDesktop_.focusWindow(openedWindow);
                } else {
                    tempWin = new ppc::Window(500, 150, sf::Color(170, 170, 170));
                    spawnErrorMessage(tempWin, tempWin->getInputHandler(), buttonSheet_, 100, 200, "Error: Invalid permissions level.", "Invalid Permissions");
                    theDesktop_.addWindow(tempWin);
                    openedWindow = tempWin;
                }
                break;
            case IconType::Chat:
                if (openedWindow != nullptr && theDesktop_.isWindow(openedWindow)) {
                    theDesktop_.focusWindow(openedWindow);
                } else {
                    tempWin = new ppc::Window(500, 150, sf::Color(170, 170, 170));
                    spawnErrorMessage(tempWin, tempWin->getInputHandler(), buttonSheet_, 100, 200, "Error: Invalid permissions level.", "Invalid Permissions");
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
                tempWin = new ppc::Window(600, 900, sf::Color(200, 200, 200));
                spawnHelp(tempWin, tempWin->getInputHandler(), buttonSheet_, 100, 100);
                theDesktop_.addWindow(tempWin);
                openedWindow = tempWin;
                break;
            case IconType::Browser:
                if (openedWindow != nullptr && theDesktop_.isWindow(openedWindow)) {
                    theDesktop_.focusWindow(openedWindow);
                } else {

					tempWin = new ppc::Window(500, 150, sf::Color(170, 170, 170));
					spawnErrorMessage(tempWin, tempWin->getInputHandler(), buttonSheet_, 100, 200, "Error: Invalid permissions level.", "Invalid Permissions");
					que.addSound("prompt", "Notification_Prompt.wav");
					que.playSound(0);
					que.popAndPlay();
					theDesktop_.addWindow(tempWin);
					openedWindow = tempWin;
                }
                break;
            case IconType::HardDrive: //Was Explorer
                tempWin = new ppc::Window(600, 350, sf::Color(255, 255, 255));
                spawnExplorer(theDesktop_, tempWin, tempWin->getInputHandler(), theDesktop_.getNodeState(), buttonSheet_, iconSheet_, 100, 200);
                theDesktop_.addWindow(tempWin);
                openedWindow = tempWin;
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
			case IconType::Folder: //Was Explorer
				if (openedWindow != nullptr && theDesktop_.isWindow(openedWindow)) {
					theDesktop_.focusWindow(openedWindow);
				}
				else {
					tempWin = new ppc::Window(600, 350, sf::Color(255, 255, 255));
					NodeState tempNS = *theDesktop_.getNodeState();
					
					/* Check to make sure the folder is not password protected */
					if (tempNS.getCwd()->findElement(labelName)->isPasswordProtected() &&
						labelName.compare("..") != 0) {
						ppc::WindowInterface* ErrorMsgWindow =
							new ppc::Window(500, 150, sf::Color(170, 170, 170));
						spawnErrorMessage(ErrorMsgWindow, ErrorMsgWindow->getInputHandler(), buttonSheet_,
							250,
							250,
							"Error: " + labelName + " is protected. \nHint: " + tempNS.getCwd()->findElement(labelName)->getHint(), "Directory is locked");
						theDesktop_.addWindow(ErrorMsgWindow);
					}
					else {
						std::vector<std::string> cdCommand;
						std::string cd = "cd";
						cdCommand.push_back(cd);
						cdCommand.push_back(labelName);
						commandFn newCD = findFunction(cd);
						newCD(tempNS, cdCommand);
						spawnExplorer(theDesktop_, tempWin, tempWin->getInputHandler(), &tempNS, buttonSheet_, iconSheet_, 100, 200);
						theDesktop_.addWindow(tempWin);
						openedWindow = tempWin;
					}
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


void ppc::iconInputComponent::setIconLabelName(std::string s)
{
	labelName = s;
}

std::string ppc::iconInputComponent::getLabelName()
{
	return labelName;
}

iconInputComponent::~iconInputComponent() {

}

bool iconInputComponent::registerInput(Event ev) {
	return true;
}

bool ppc::make_icon_window(iconInputComponent* ptr, ppc::Event ev) {
    
	Event ppcEv;
	ppcEv.type = Event::ButtonType;
	ppcEv.buttons.activation = ev.buttons.LeftMouse;
	ppcEv.buttons.state = Event::ButtonsEv::DblClicked;
	ptr->recieveMessage(ppcEv);

	return true;
}

bool ppc::flag_desktop_file(iconInputComponent* ptr, ppc::Event ev) {
	ppc::NodeState* tempNS = World::getCurrDesktop().getNodeState();
	ppc::BaseFileType* tempBFT = tempNS->getCwd()->findElement(ptr->getLabelName());
	
	if (tempBFT != nullptr) {
		std::vector<std::string> firstFlagCommand;
		firstFlagCommand.push_back("flag");
		firstFlagCommand.push_back(ptr->getLabelName());
		commandFn firstLs = findFunction("flag");
		firstLs(*tempNS, firstFlagCommand);
	}
	else {
		std::cout << "SHOW ERROR MESSAGE" << std::endl;
	}
	WindowInterface* oldWindow = SuspiciousFileHolder::getWindow();
	WindowInterface* fileTracker = new Window(450, 100, sf::Color::Transparent);
	spawnFileTracker(World::getCurrDesktop(), fileTracker, fileTracker->getInputHandler(), 250, 50);
	fileTracker->setPosition(sf::Vector2f(oldWindow->getPosition().x, oldWindow->getPosition().y));
	World::getCurrDesktop().addWindow(fileTracker);
	oldWindow->close();
	SuspiciousFileHolder::setWindow(fileTracker);
	return true;
}

bool ppc::spawn_desktop_prompt_msg(iconInputComponent * ptr, ppc::Event)
{
	ppc::WindowInterface* newWindow = new ppc::Window(300, 150, sf::Color(170, 170, 170));
	ppc::BaseFileType* tempBFT = World::getCurrDesktop().getNodeState()->getCwd()->findElement(ptr->getLabelName());

	Event ev;
	ev.type = ev.SubmissionType;
	ev.submission.type = ev.submission.Scan;
	ev.submission.file = tempBFT;
	SuspiciousFileHolder::onChange.sendEvent(ev);

	spawnErrorMessage(newWindow, newWindow->getInputHandler(), World::getCurrDesktop().getButtonSheet(), 100.f, 100.f,
		"File '" + tempBFT->getName() + "'\n has a suspicion index of: " + std::to_string(tempBFT->getSuspicionLevel()), "Scan Results");
	World::getCurrDesktop().addWindow(newWindow);
	return true;
}
