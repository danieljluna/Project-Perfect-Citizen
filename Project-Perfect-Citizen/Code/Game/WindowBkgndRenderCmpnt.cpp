#include "../Engine/debug.h"
#include "WindowBkgndRenderCmpnt.h"

using namespace ppc;

WindowBkgndRenderCmpnt::WindowBkgndRenderCmpnt(sf::Sprite s) {
	sprt = s;
}


WindowBkgndRenderCmpnt::~WindowBkgndRenderCmpnt() {
}


void WindowBkgndRenderCmpnt::draw(sf::RenderTarget& target,
	sf::RenderStates states) const {

	target.draw(sprt, states);
}

void WindowBkgndRenderCmpnt::recieveMessage(msgType code) {
}