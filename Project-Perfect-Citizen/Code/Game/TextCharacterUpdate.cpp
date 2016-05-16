#include "TextCharacterUpdate.h"
#include "TextDisplayRenderComponent.h"

ppc::TextCharacterUpdate::TextCharacterUpdate() {
	content_ = "";
	strItor_ = content_.begin();
	tdrc_ = nullptr;
	isEnd = false;
	accumulator_ = sf::milliseconds(sf::Int32(0.f));
}

ppc::TextCharacterUpdate::~TextCharacterUpdate() {
}

void ppc::TextCharacterUpdate::setTextDisplay(TextDisplayRenderComponent &td) {
	tdrc_ = &td;
}

void ppc::TextCharacterUpdate::setContent(std::string str) {
	content_ = str;
	strItor_ = content_.begin();
}

void ppc::TextCharacterUpdate::setDisplayRate(sf::Time t) {
	displayRate_ = t;
}

void ppc::TextCharacterUpdate::update(sf::Time& deltaTime) {
	
	if (isEnd || (tdrc_ == nullptr)) return;
	accumulator_ += deltaTime;
	
	if (accumulator_ >= displayRate_) {

		if (strItor_ == content_.end()) {
			isEnd = true;
			accumulator_ = sf::milliseconds(sf::Int32(0.f));
			return;
		}
		std::string updatedString = tdrc_->getString() + *strItor_;
		tdrc_->updateString(updatedString);
		++strItor_;

		accumulator_ = sf::milliseconds(sf::Int32(0.f));
	}


}
