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
	// Recieve the vector of pair<string,emotion> 
	// Parse it
	// Update the internal state of the input component
	// update floppy emotion 
}

void FloppyInputComponent::updateFloppyEmotion() {
	// Send an event to the render component
}

void FloppyInputComponent::updateTextBoxString() {
	// Send an event to the text box
}