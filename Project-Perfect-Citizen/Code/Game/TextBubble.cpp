#include "TextBubble.h"

ppc::TextBubble::TextBubble() {

}

ppc::TextBubble::~TextBubble() {

}

void ppc::TextBubble::draw(sf::RenderTarget & target, sf::RenderStates states) const {

	states.transform *= getTransform();
}
