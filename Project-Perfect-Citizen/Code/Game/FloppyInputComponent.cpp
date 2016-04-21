#include "../Engine/debug.h"
#include "FloppyInputComponent.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>

#include "../Engine/FreeFunctionObserver.h"
#include "../Engine/event.h"

using namespace ppc;

const std::string FLOPPY_DEBUG_CODE = "FL";

std::vector<std::vector<std::pair<std::string, unsigned int>>> FloppyInputComponent::floppyDictionary;

FloppyInputComponent::FloppyInputComponent() {
	initializeFloppyDict();
}

FloppyInputComponent::~FloppyInputComponent() {

}

const std::array<std::string, 1> FLOPPY_SOURCES{
	"PipelineTutorial.txt"
};

const std::map<std::string, int> FLOPPY_EMOTION_MAP{
	{"Default", 0}
};


void ppc::FloppyInputComponent::initializeFloppyDict() {
	for (const auto& filename: FLOPPY_SOURCES) {
		std::ifstream myfile(filename);
		if (myfile.is_open()) {
			std::string line;
			std::string label;
			std::vector<std::pair<std::string, unsigned int>> sequence;
			while (std::getline(myfile, line)) {
				if (line.substr(0, 1).compare("-") == 0) {
					if (sequence.empty()) continue;
					//auto pos = Floppy_Sequence_Names.find(label);
					//if (pos == Floppy_Sequence_Names.end()) {
					//	DEBUGF(FLOPPY_DEBUG_CODE, label);
					//}
					//else {
						floppyDictionary.push_back(sequence);
						Floppy_Sequence_Names.insert(std::make_pair(label, floppyDictionary.size() - 1));
					//}
					sequence.clear();
					label = line.substr(1);
				}
				else {
					std::string emotion = line.substr(0, line.find_first_of(':') - 1);
					line = line.substr(line.find_first_of(':') + 2);
					if (FLOPPY_EMOTION_MAP.find(emotion) != FLOPPY_EMOTION_MAP.end()) {
						sequence.push_back(std::make_pair(emotion, FLOPPY_EMOTION_MAP.at(emotion)));
					}
				}
			}
			floppyDictionary.push_back(sequence);
			Floppy_Sequence_Names.insert(std::make_pair(label, floppyDictionary.size() - 1));
		}
		else {
			DEBUGF(FLOPPY_DEBUG_CODE, filename + " could not be opened");
		}
	}


	//std::vector<std::pair<std::string, unsigned int>> sequence1;
	//std::pair<std::string, unsigned int> sequence1frame1;
	//std::pair<std::string, unsigned int> sequence1frame2;

	//sequence1frame1 = std::make_pair("BAD COP NADER", 0);
	//sequence1frame2 = std::make_pair("MACK DADDY", 1);
	//sequence1.push_back(sequence1frame1);
	//sequence1.push_back(sequence1frame2);

	//floppyDictionary.push_back(sequence1);
}

unsigned int ppc::FloppyInputComponent::getFrame() { return frame; }

unsigned int ppc::FloppyInputComponent::getSequence() { return sequence; }

void ppc::FloppyInputComponent::setFrame(unsigned int f) { frame = f; }

void ppc::FloppyInputComponent::setSequence(unsigned int s) { sequence = s; }

void ppc::FloppyInputComponent::advanceFrame() { frame++; }

void ppc::FloppyInputComponent::regressFrame() { frame--;}

void ppc::FloppyInputComponent::advanceSequence() { sequence++; }

void ppc::FloppyInputComponent::regressSequence() { sequence--; }


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


bool incrementFloppyDialog(FloppyInputComponent* ptr, ppc::Event ev) {
	if (ev.type == ppc::Event::ButtonType) {
		if (ev.buttons.isReleased) {

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
		}
	}
	return true;
}


