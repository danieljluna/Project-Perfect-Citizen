#include "flaggedFileInputComponent.h"
#include "../Engine/SuspiciousFileHolder.h"
#include "../Game/createWindow.h"
#include "../Game/ContextBuilder.h"
#include "../Engine/World.h"
#include "../Engine/Window.h"

using namespace ppc;

ppc::flaggedFileInputComponent::~flaggedFileInputComponent()
{
}

ppc::flaggedFileInputComponent::flaggedFileInputComponent(Desktop * dt, ppc::WindowInterface* cW, ppc::InputHandler & ih, std::string fN) :
	InputComponent(2), theDesktop_(dt), containingWindow(cW), fileName(fN) {

}

Desktop* ppc::flaggedFileInputComponent::getDesktop()
{
	return theDesktop_;
}

std::string ppc::flaggedFileInputComponent::getFileName()
{
	return fileName;
}

bool ppc::flaggedFileInputComponent::registerInput(Event ev)
{
	return false;
}

void ppc::flaggedFileInputComponent::recieveMessage(Event ev)
{
	switch (ev.type) {
	case Event::EventTypes::ButtonType:
		if ((ev.buttons.state == ev.buttons.Release) &&
			ev.buttons.activation == ev.buttons.RightMouse) {

			/* Begin Building Context List */
			ppc::WindowInterface* ContextMenu = nullptr;
			ContextMenu = new ppc::Window(200, 300, sf::Color(170, 170, 170));
			ContextBuilder builder;
			std::vector<ppc::Entity> listElements;
			float fontSize = 20.0f;
			float fontPadding = 2.0f;

			Entity listElement;
			builder.setContainingWindow(ContextMenu);
			builder.setInputHandle(ContextMenu->getInputHandler());
			builder.setLabelFont(World::getFont(World::Consola));
			builder.setLabelMessage("Unflag");
			builder.setLabelSize((int)fontSize);
			builder.setListElementPosition(0, 0);
			builder.setListElementSize({ ContextMenu->getBounds().width, fontSize + fontPadding });
			createWithEventFunc(builder, listElement, this, ppc::unflag_file);
			listElements.push_back(listElement);

			/* Completed: Make the Context Menu at the mouse position*/
			spawnContextMenu(ContextMenu, listElements, ev.buttons.mousePos.x + containingWindow->getPosition().x,
				ev.buttons.mousePos.y + containingWindow->getPosition().y);
			theDesktop_->addWindow(ContextMenu);
		}
		break;
	default:
		break;
	}

}

bool ppc::unflag_file(flaggedFileInputComponent * ptr, ppc::Event)
{
	ppc::SuspiciousFileHolder::clearFile(ptr->getFileName());
	WindowInterface* fileTracker = new Window(450, 100, sf::Color::Transparent);
	spawnFileTracker(*(ptr->getDesktop()), fileTracker, fileTracker->getInputHandler(), 250, 50);
	ptr->getDesktop()->addWindow(fileTracker);
	SuspiciousFileHolder::setWindow(fileTracker);
	return true;
}

bool ppc::clear_flagged_files(Desktop* ptr, ppc::Event)
{
	ppc::SuspiciousFileHolder::clearFiles();
	WindowInterface* fileTracker = new Window(450, 100, sf::Color::Transparent);
	spawnFileTracker(*ptr, fileTracker, fileTracker->getInputHandler(), 250, 50);
	ptr->addWindow(fileTracker);
	SuspiciousFileHolder::setWindow(fileTracker);
	return true;
}
