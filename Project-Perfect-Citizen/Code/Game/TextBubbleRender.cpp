#include "TextBubbleRender.h"
#include "TextBubble.h"
#include "../Engine/debug.h"


ppc::TextBubbleRender::TextBubbleRender() {
	textBubble_ = nullptr;
}

ppc::TextBubbleRender::~TextBubbleRender() {

}

void ppc::TextBubbleRender::setTextBubble(TextBubble &tb) {
	textBubble_ = &tb;
}

void ppc::TextBubbleRender::draw(sf::RenderTarget & target,
	sf::RenderStates states) const {

	if (textBubble_ == nullptr) return;

	target.draw(*textBubble_, states);
}

void ppc::TextBubbleRender::recieveMessage(msgType code) {
}
