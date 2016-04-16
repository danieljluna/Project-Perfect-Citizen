#include "TextBubbleRender.h"

ppc::TextBubbleRender::TextBubbleRender() {
	textBubble = nullptr;
}

ppc::TextBubbleRender::~TextBubbleRender() {

}

void ppc::TextBubbleRender::setTextBubble(TextBubble &tb) {
	textBubble = &tb;
}

void ppc::TextBubbleRender::draw(sf::RenderTarget & target, 
	sf::RenderStates states) const {
	if (textBubble == nullptr) return;

	target.draw(*textBubble, states);
}

void ppc::TextBubbleRender::recieveMessage(msgType code) {
}
