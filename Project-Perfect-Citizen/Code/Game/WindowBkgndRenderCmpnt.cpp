#include "WindowBkgndRenderCmpnt.h"
#include "../Engine/debug.h"


WindowBkgndRenderCmpnt::WindowBkgndRenderCmpnt(sf::Sprite& s):
	sprt(&s) {
}


WindowBkgndRenderCmpnt::~WindowBkgndRenderCmpnt() {
	delete sprt;
}


void WindowBkgndRenderCmpnt::draw(sf::RenderTarget& target,
	sf::RenderStates states) const {

	target.draw(*(this->sprt), states);
}

void WindowBkgndRenderCmpnt::recieveMessage(msgType code) {
}