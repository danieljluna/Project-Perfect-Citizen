#include "../Engine/debug.h"
#include "explorerFileInputComponent.h"
#include <iostream>
#include <string>

#include "../Engine/FreeFunctionObserver.h"
#include "../Engine/BaseFileType.h"
#include "../Engine/SuspiciousFileHolder.h"
#include "ContextBuilder.h"
#include "../Engine/World.h"
#include "../Engine/SubjectObsvr.h"

using namespace ppc;


const std::string MOUSE_DOWN_CODE = "MDC";
const std::string MOUSE_RELEASED_CODE = "MRC";
const float DOUBLE_CLICK_TIME = 500.0f;


explorerFileInputComponent::explorerFileInputComponent(Desktop& dt, WindowInterface* cW,
	ppc::InputHandler& ih, NodeState& ns, sf::Image& bS, sf::FloatRect rect, std::string fN) :
	InputComponent(2), theDesktop_(dt), containingWindow_(cW),theFileTree_(ns), buttonSheet_(bS), 
	buttonRect(rect), fileName(fN) {

	//add a new subject that is tied to the event
	ih.addHandle(sf::Event::MouseButtonPressed);
	ih.addHandle(sf::Event::MouseButtonReleased);

	//add an observer to the subject we just added
	watch(ih, sf::Event::MouseButtonPressed);
	watch(ih, sf::Event::MouseButtonReleased);

}

void explorerFileInputComponent::clearObservers()
{
	for (size_t i = 0; i < observerCount_; ++i) {
		delete observerArray_[i];
	}
}


//void mousePressButton::addFunctionObserver(bool(*fnToAdd)(sf::Event &ev), mousePressButton* mpb, unsigned int placeToInsert)


explorerFileInputComponent::~explorerFileInputComponent() {

	//ignore(inputHandle, sf::Event::MouseButtonPressed);
	//ignore(inputHandle, sf::Event::MouseButtonReleased);
}

void explorerFileInputComponent::setInputHandle(ppc::InputHandler& ih) {

	ih.addHandle(sf::Event::MouseButtonPressed);
	ih.addHandle(sf::Event::MouseButtonReleased);

	watch(ih, sf::Event::MouseButtonPressed);
	watch(ih, sf::Event::MouseButtonReleased);

}

void explorerFileInputComponent::setFloatRect(sf::FloatRect rect) {
	buttonRect = rect;
}


bool explorerFileInputComponent::isCollision(sf::Vector2i mousePos) {
	//Gets the position as a Float Vector
	sf::Vector2f mouseFloatPos(float(mousePos.x), float(mousePos.y));

	//Returns if point is in foatRect
	return buttonRect.contains(mouseFloatPos);
}


bool explorerFileInputComponent::registerInput(Event ppcEv) {
    sf::Event ev(ppcEv);
	if (getEntity() != nullptr) {

		/* Case: Mouse Pressed Event*/
		if (ev.type == sf::Event::MouseButtonPressed) {
			if (ev.mouseButton.button == sf::Mouse::Left &&
				isCollision({ ev.mouseButton.x ,ev.mouseButton.y })) {

				/* Send the mouse down message regardless */
				getEntity()->broadcastMessage(MOUSE_DOWN_CODE);
				onPress_.sendEvent(ev);

				/* Handle Double Click Register */
				mouseTime = mouseClock.getElapsedTime().asMilliseconds();
				if (mouseTime > DOUBLE_CLICK_TIME) {
					mouseClock.restart();
				}
				else if (mouseTime < DOUBLE_CLICK_TIME) {
					openFile();
				}
			}
		}
		/* Case: Mouse Released Event*/
		else if (ev.type == sf::Event::MouseButtonReleased) {
		if (ev.mouseButton.button == sf::Mouse::Right &&
			isCollision({ ev.mouseButton.x ,ev.mouseButton.y })) {
	
			/* Begin Building Context List */
			ppc::WindowInterface* ContextMenu = nullptr;
			ContextMenu = new ppc::Window(200, 300, sf::Color(170, 170, 170));
			ContextBuilder builder;
			std::vector<ppc::Entity> listElements;
			float fontSize = 20.0f;
			float fontPadding = 2.0f;

			/* First Element: 'Open' */
			Entity listElement;
			builder.setContainingWindow(ContextMenu);
			builder.setInputHandle(ContextMenu->getInputHandler());
			builder.setLabelFont(World::getFont(World::Consola));
			builder.setLabelMessage("Open");
			builder.setLabelSize((int)fontSize);
			builder.setListElementPosition(0, 0);
			builder.setListElementSize({ ContextMenu->getBounds().width, fontSize + fontPadding });
			createWithEventFunc(builder, listElement, this, ppc::open_file);
			listElements.push_back(listElement);

			/* Second Element: 'Flag' */
			Entity listElement2;
			builder.setLabelMessage("Flag");
			builder.setListElementPosition(0, fontSize + fontPadding);
			builder.setLabelPosition({ 0.0f, fontSize + fontPadding });
			createWithEventFunc(builder, listElement2, this, ppc::flag_file);
			listElements.push_back(listElement2);

			/*Third Element: 'Scan'*/
			Entity listElementThree;
			builder.setLabelMessage("Scan");
			builder.setListElementPosition(0, (fontSize + fontPadding)* 2);
			builder.setLabelPosition({ 0.0f, (fontSize + fontPadding) * 2 });
			createWithEventFunc(builder, listElementThree, this, ppc::spawnPromptMessage);
			listElements.push_back(listElementThree);

			/* Completed: Make the Context Menu at the mouse position*/
			spawnContextMenu(ContextMenu, listElements, ev.mouseButton.x + containingWindow_->getPosition().x,
				ev.mouseButton.y + containingWindow_->getPosition().y);
			theDesktop_.addWindow(ContextMenu);

			}
		}
	}
	return true;
}

bool ppc::explorerFileInputComponent::andy_flag_file(Desktop* ptr, ppc::Event ev)
{
	ppc::BaseFileType* fileToAdd = this->theFileTree_.getCwd()->findElement(this->fileName);
	ppc::SuspiciousFileHolder::flagFile(fileToAdd);
	return true;

}

void ppc::explorerFileInputComponent::openFile()
{
	theFileTree_.readFile(fileName);
}

NodeState ppc::explorerFileInputComponent::getFileNodeState()
{
	return theFileTree_;
}

string ppc::explorerFileInputComponent::getFileName()
{
	return fileName;
}

Desktop* ppc::explorerFileInputComponent::getFileDesktop()
{
	return &theDesktop_;
}

bool ppc::open_file(explorerFileInputComponent* ptr, ppc::Event ev) {
	ptr->openFile();
	return true;
}

bool ppc::flag_file(explorerFileInputComponent* ptr, ppc::Event ev) {
	ppc::BaseFileType* tempBFT = ptr->getFileNodeState().getCwd()->findElement(ptr->getFileName());
	if (tempBFT != nullptr) {
		std::vector<string> firstFlagCommand;
		firstFlagCommand.push_back("flag");
		firstFlagCommand.push_back(ptr->getFileName());
		commandFn firstLs = findFunction("flag");
        ppc::NodeState temp = ptr->getFileNodeState();
		firstLs(temp, firstFlagCommand);
	}
	else {
		cout << "SHOW ERROR MESSAGE" << endl;
	}

	WindowInterface* fileTracker = new Window(450, 100, sf::Color::Transparent);
	spawnFileTracker(*(ptr->getFileDesktop()), fileTracker, fileTracker->getInputHandler(), 250, 50);
	ptr->getFileDesktop()->addWindow(fileTracker);
	SuspiciousFileHolder::setWindow(fileTracker);
	return true;
}

bool ppc::submitFiles(ppc::Desktop * ptr, ppc::Event ev)
{
	std::cout << "inside submit files" << std::endl;
	ppc::SuspiciousFileHolder::submitFiles();
	return true;
}

bool ppc::spawnPromptMessage(ppc::explorerFileInputComponent * ptr, ppc::Event)
{
	ppc::WindowInterface* newWindow = new ppc::Window(300, 150, sf::Color(170, 170, 170));
 	ppc::BaseFileType* tempBFT = ptr->getFileNodeState().getCwd()->findElement(ptr->getFileName());

    Event ev;
    ev.type = ev.SubmissionType;
    ev.submission.type = ev.submission.Scan;
    ev.submission.file = tempBFT;
    SuspiciousFileHolder::onChange.sendEvent(ev);

	spawnErrorMessage(newWindow, newWindow->getInputHandler(), ptr->getFileDesktop()->getButtonSheet(), 100.f, 100.f,
		"File '" + tempBFT->getName() + "'\n has a suspicion index of: " + std::to_string(tempBFT->getSuspicionLevel()), "Scan Results");
	ptr->getFileDesktop()->addWindow(newWindow);
	//ppc::spawnErrorMessage()
	return true;
}

