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


void ppc::TextBubbleRender::setRenderable(bool r) {
	renderable_ = r;
}

void ppc::TextBubbleRender::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	if(renderable_)target.draw(*bubble_, states);

}

void ppc::TextBubbleRender::recieveMessage(msgType code) {
}

void ppc::TextBubbleRender::recieveMessage(ppc::Event ev) {

	if (ev.type == ppc::Event::FloppyType) {
		
		unsigned int i = ev.floppy.sequence;
		unsigned int j = ev.floppy.frame;

		if (j == -1) {
			renderable_ = false;
		} else {
			renderable_ = true;
			std::string s = 
				FloppyInputComponent::floppyDictionary.at(i).at(j).text;
			DEBUGF("tb", s)
			bubble_->setText(s);
		}
		
	}

	if (ev.type == ppc::Event::AbleType) {
		setRenderable(ev.able.enable);
	}

}
