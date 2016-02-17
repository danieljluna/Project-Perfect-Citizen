#include "windowBkgndRenderCmpnt.h"



windowBkgndRenderCmpnt::windowBkgndRenderCmpnt(sf::Sprite& s): 
	sprt(&s) {
}


windowBkgndRenderCmpnt::~windowBkgndRenderCmpnt() {
	delete sprt;
}


void windowBkgndRenderCmpnt::draw(sf::RenderTarget& target,
	sf::RenderStates states) const {

	target.draw(*(this->sprt), states);
}

void windowBkgndRenderCmpnt::recieveMessage(msgType code) {
}