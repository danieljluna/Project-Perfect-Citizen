#include "../Engine/debug.h"
#include "FloppyInputComponent.h"
#include <iostream>
#include <string>

#include "../Engine/FreeFunctionObserver.h"
#include "../Engine/event.h"

using namespace ppc;

FloppyInputComponent::FloppyInputComponent() {

}

FloppyInputComponent::~FloppyInputComponent() {

}

void ppc::FloppyInputComponent::recieveEvent(ppc::Event ev) {
	if (ev.type == ev.FloppyType) {
		// Copy the vector & update component internal state
		currentSequenceIndex = 0;
	}

	// Recieve the vector of pair<string,emotion> 
	updateFloppyEmotion(ev);
	updateTextBoxString(ev);

}

void FloppyInputComponent::updateFloppyEmotion(sf::Event e) {
	
	// Construct a new event to send to the render component
	ppc::Event ppcEv(e);
	ppcEv.type = ppc::Event::EmotionType;
	
	// Copy the emotion from the current index's pair into the new event
	ppcEv.emotions = currentSequence.at(currentSequenceIndex).second;
	getEntity()->broadcastMessage(ppcEv);
}

void FloppyInputComponent::updateTextBoxString(sf::Event e) {

	//Construct a new event to send to the text box
	ppc::Event ppcEv(e);
	ppcEv.type = ppc::Event::MessageType;

	// Copy the string from the current index's pair into the new event
	// ppcEv.message = currentSequence.at(currentSequenceIndex).first;
	getEntity()->broadcastMessage(ppcEv);

}

void ppc::FloppyInputComponent::advanceSequence(sf::Event ev) {
	if (currentSequenceIndex + 1 < currentSequence.size()) {
		currentSequenceIndex++;
		ppc::Event ppcEv(ev);
		updateFloppyEmotion(ev);
		updateTextBoxString(ev);
	}
}

void ppc::FloppyInputComponent::regressSequence(sf::Event ev) { 
	if (currentSequenceIndex > 0) {
		currentSequenceIndex--;
		ppc::Event ppcEv(ev);
		updateFloppyEmotion(ppcEv);
		updateTextBoxString(ppcEv);
	}
}


