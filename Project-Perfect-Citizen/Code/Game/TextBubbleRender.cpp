#include "TextBubbleRender.h"
#include "TextBubble.h"
#include "../Engine/event.h"
#include "FloppyInputComponent.h"

ppc::TextBubbleRender::TextBubbleRender() {

}

ppc::TextBubbleRender::~TextBubbleRender() {
	bubble_ = nullptr;
}

void ppc::TextBubbleRender::setTextBubble(TextBubble &tb) {
	bubble_ = &tb;
}

ppc::TextBubble & ppc::TextBubbleRender::getTextBubble() {
	return *bubble_;
}

void ppc::TextBubbleRender::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	target.draw(*bubble_, states);
}

void ppc::TextBubbleRender::recieveMessage(msgType code) {
}

void ppc::TextBubbleRender::recieveMessage(ppc::Event ev) {

	if (ev.type == ppc::Event::FloppyType) {
		unsigned int i = ev.floppy.sequence;
		unsigned int j = ev.floppy.frame;
		std::string s = 
			FloppyInputComponent::floppyDictionary.at(i).at(j).first;

		bubble_->setText(s);
	}

}
