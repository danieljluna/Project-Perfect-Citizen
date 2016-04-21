#include "../Engine/debug.h"
#include "FloppyInputComponent.h"
#include <iostream>
#include <string>
#include <utility>
#include "../Engine/Entity.h"
#include "../Engine/debug.h"



using namespace ppc;

std::vector<std::vector<std::pair<std::string, unsigned int>>> FloppyInputComponent::floppyDictionary;

FloppyInputComponent::FloppyInputComponent() {
	initializeFloppyDict();
}

FloppyInputComponent::~FloppyInputComponent() {

}



void ppc::FloppyInputComponent::initializeFloppyDict() {
	
	std::vector<std::pair<std::string, unsigned int>> sequence1;
	std::pair<std::string, unsigned int> sequence1frame1;
	std::pair<std::string, unsigned int> sequence1frame2;

	sequence1frame1 = std::make_pair("BAD COP NADER", 0);
	sequence1frame2 = std::make_pair("MACK DADDY", 3);
	sequence1.push_back(sequence1frame1);
	sequence1.push_back(sequence1frame2);

	floppyDictionary.push_back(sequence1);
}

unsigned int ppc::FloppyInputComponent::getFrame() { return frame; }

unsigned int ppc::FloppyInputComponent::getSequence() { return sequence; }

void ppc::FloppyInputComponent::setFrame(unsigned int f) { frame = f; }

void ppc::FloppyInputComponent::setSequence(unsigned int s) { sequence = s; }

void ppc::FloppyInputComponent::advanceFrame() { frame++; }

void ppc::FloppyInputComponent::regressFrame() { frame--;}

void ppc::FloppyInputComponent::advanceSequence() { sequence++; }

void ppc::FloppyInputComponent::regressSequence() { sequence--; }

bool ppc::FloppyInputComponent::registerInput(sf::Event ev) { return true; }


bool ppc::summonFloppyDialog(FloppyInputComponent* ptr, ppc::Event ev) {
	if (ev.type == ppc::Event::FloppyType) {

		/* Save the Sequence and Event for future iteration */
		ptr->setSequence(ev.floppy.sequence);
		ptr->setFrame(ev.floppy.frame);

		/* Pass the event to the entity 
		This isn't necessary, but keeping in case we want
		to modify these values */
		ppc::Event ppcEv(ev);
		ppcEv.type = ppc::Event::FloppyType;
		ppcEv.floppy.sequence = ev.floppy.sequence;
		ppcEv.floppy.frame = ev.floppy.frame;
		ptr->getEntity()->broadcastMessage(ppcEv);
	}
	return true;
}


bool ppc::incrementFloppyDialog(FloppyInputComponent* ptr, ppc::Event ev) {

	/* Advance the frame state to be one more than
	the stored value */
	ptr->advanceFrame();

	/* Create and send a new event to the entity
	with the updated frame */
	ppc::Event ppcEv(ev);
	ppcEv.type = ppc::Event::FloppyType;
	ppcEv.floppy.sequence = ptr->getSequence();
	ppcEv.floppy.frame = ptr->getFrame();
	ptr->getEntity()->broadcastMessage(ppcEv);

	return true;
}


