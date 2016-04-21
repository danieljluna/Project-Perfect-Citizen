#include "TextBubbleRender.h"
#include "TextBubble.h"
#include "../Engine/event.h"
#include "FloppyInputComponent.h"

#include <vector>
#include <string.h>
#include "../Engine/debug.h"


ppc::TextBubbleRender::TextBubbleRender() {
	drawable_ = true;
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

void ppc::TextBubbleRender::setDrawable(bool flag = true) {
	drawable_ = flag;
}

void ppc::TextBubbleRender::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	if (drawable_ == true) {
		target.draw(*bubble_, states);
	}
}

void ppc::TextBubbleRender::recieveMessage(msgType code) {
}

void ppc::TextBubbleRender::recieveMessage(ppc::Event ev) {

	if (ev.type == ppc::Event::FloppyType) {
		
		unsigned int i = ev.floppy.sequence;
		unsigned int j = ev.floppy.frame;
		if (j == -1) {
			drawable_ = false;
		} else {
			std::string s = 
				FloppyInputComponent::floppyDictionary.at(i).at(j).first;
			DEBUGF("tb", s)
			bubble_->setText(s);
		}
		
	}

}
