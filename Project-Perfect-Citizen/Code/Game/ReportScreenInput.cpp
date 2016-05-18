#include "ReportScreenInput.h"
#include "TextCharacterUpdate.h"
#include "../Engine/event.h"
#include "../Engine/World.h"

ppc::ReportScreenInput::ReportScreenInput() {
	tcu_ = nullptr;
}

ppc::ReportScreenInput::ReportScreenInput(InputHandler &ih) {
	this->watch(ih, sf::Event::MouseButtonPressed);
	this->watch(ih, sf::Event::KeyPressed);
	tcu_ = nullptr;
}

ppc::ReportScreenInput::~ReportScreenInput() {
}

void ppc::ReportScreenInput::setTextCharacterUpdate(TextCharacterUpdate &tcu) {
	tcu_ = &tcu;
}

void ppc::ReportScreenInput::setInputHandle(InputHandler &ih) {
	this->watch(ih, sf::Event::MouseButtonPressed);
	this->watch(ih, sf::Event::KeyPressed);
}

bool ppc::ReportScreenInput::registerInput(ppc::Event ev) {
	if (tcu_->isEnded()) {
		if (ev.type == Event::sfEventType) {
			switch (ev.sfEvent.type) {
				case sf::Event::KeyPressed:
				case sf::Event::MouseButtonPressed:
					World::quitDesktop();
					break;
				default:
					break;
			}
		}
	}
	return true;
}
