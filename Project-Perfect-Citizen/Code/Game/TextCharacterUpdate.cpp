#include "TextCharacterUpdate.h"

ppc::TextCharacterUpdate::TextCharacterUpdate() {
	content_ = "";
	tdrc_ = nullptr;
	isEnd = false;
}

ppc::TextCharacterUpdate::~TextCharacterUpdate() {
}

void ppc::TextCharacterUpdate::setTextDisplay(TextDisplayRenderComponent &td) {
	tdrc_ = &td;
}

void ppc::TextCharacterUpdate::setContent(std::string str) {
	content_ = str;
}

void ppc::TextCharacterUpdate::update(sf::Time& deltaTime) {

	if (isEnd) return;



}
