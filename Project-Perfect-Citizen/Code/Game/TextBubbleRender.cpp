#include "TextBubbleRender.h"

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
