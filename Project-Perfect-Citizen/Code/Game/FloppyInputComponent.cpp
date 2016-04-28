//Used to get XCODE working/////////////////////////////////

#ifdef WINDOWS_MARKER
#define resourcePath() std::string("Resources/")
#else
#include "ResourcePath.hpp"
#endif

///////////////////////////////////////////////////////////

#include "../Engine/debug.h"
#include "FloppyInputComponent.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include "../Engine/Entity.h"

#include "../Engine/FreeFunctionObserver.h"

using namespace ppc;

const std::string FLOPPY_DEBUG_CODE = "fl";

std::vector<std::vector<std::pair<std::string, unsigned int>>> FloppyInputComponent::floppyDictionary;
bool FloppyInputComponent::initialized = false;

std::map<std::string, unsigned int> FloppyInputComponent::Floppy_Sequence_Names;

FloppyInputComponent::FloppyInputComponent() {
    if (!initialized) {
        initializeFloppyDict();
    }
}

FloppyInputComponent::~FloppyInputComponent() {

}

const std::array<std::string, 1> FLOPPY_SOURCES{
	"PipelineTutorial.txt"
};

const std::map<std::string, int> FLOPPY_EMOTION_MAP{
	{"Default"   , 0},
    {"Angry"     , 1},
    {"Surprised" , 2},
    {"Peek"      , 3},
};


void ppc::FloppyInputComponent::initializeFloppyDict() {
	for (const auto& filename: FLOPPY_SOURCES) {
		std::ifstream myfile(resourcePath() + filename);
		if (myfile.is_open()) {
			std::string line;
			std::string label;
			std::vector<std::pair<std::string, unsigned int>> sequence;
			while (std::getline(myfile, line)) {
				if (line.substr(0, 1).compare("-") == 0) {
					if (sequence.empty()) {
						label = line.substr(1);
						continue;
					}
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
					std::string emotion = line.substr(0, line.find_first_of(':'));
					line = line.substr(line.find_first_of(':') + 2);
					if (FLOPPY_EMOTION_MAP.find(emotion) != FLOPPY_EMOTION_MAP.end()) {
						sequence.push_back(std::make_pair(line, FLOPPY_EMOTION_MAP.at(emotion)));
					}
				}
			}
			floppyDictionary.push_back(sequence);
			Floppy_Sequence_Names.insert(std::make_pair(label, floppyDictionary.size() - 1));
		}
		else {
			DEBUGF(FLOPPY_DEBUG_CODE, filename + " could not be opened");
		}
		myfile.close();
	}
    initialized = true;

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

void ppc::FloppyInputComponent::advanceFrame() { 
	frame++;
	if (floppyDictionary.at(sequence).size() <= frame) {
		frame = -1;
	}

}

void ppc::FloppyInputComponent::regressFrame() { frame--;}

void ppc::FloppyInputComponent::advanceSequence() { sequence++; }

void ppc::FloppyInputComponent::regressSequence() { sequence--; }

bool ppc::FloppyInputComponent::registerInput(Event ev) { return true; }

bool ppc::summonFloppyDialog(FloppyInputComponent* ptr, ppc::Event ev) {
    bool wasSummoned = false;

	switch (ev.type) {
    case ppc::Event::FloppyType:

        //If we just ended a frame
        if (ev.floppy.frame == -1) {
            //If we just ended the Welcome
            if (ev.floppy.sequence == FloppyInputComponent::Floppy_Sequence_Names.at("Welcome")) {
                wasSummoned = true;
                ev.floppy.sequence = FloppyInputComponent::Floppy_Sequence_Names.at("Connections");
                ev.floppy.frame = 0;
            } else if (ev.floppy.sequence == FloppyInputComponent::Floppy_Sequence_Names.at("Connections")) {
                wasSummoned = true;
                ev.floppy.sequence = FloppyInputComponent::Floppy_Sequence_Names.at("Edges");
                ev.floppy.frame = 0;
            }
        } else {
            wasSummoned = true;
        }


        break;
    case Event::OpenType:
        //If we are opening the pipeline:
        if (ev.open.winType == ev.open.Pipeline) {
            wasSummoned = true;
            ev.type = Event::FloppyType;
            ev.floppy.sequence = FloppyInputComponent::Floppy_Sequence_Names.at("Welcome");
            ev.floppy.frame = 0;
        }
        break;
	}

    if (wasSummoned) {
        /* Also let the textbox and button that
        they should spawn */
        ptr->setSequence(ev.floppy.sequence);
        ptr->setFrame(ev.floppy.frame);
        ptr->getEntity()->broadcastMessage(ev);

        ev.type = ppc::Event::AbleType;
        ev.able.enable = true;
        ptr->getEntity()->broadcastMessage(ev);
		ptr->onSequenceEnd().sendEvent(ev);
    }

	return true;
}


bool ppc::incrementFloppyDialog(FloppyInputComponent* ptr, ppc::Event ev) {

	/* Advance the frame state to be one more than
	the stored value */
	ptr->advanceFrame();

	/* Alert observers if beyond sequence length (return both -1)*/
	if (ptr->getFrame() == -1) {
		ppc::Event ppcEv;
		ppcEv.type = ppc::Event::FloppyType;
		ppcEv.floppy.sequence = ev.floppy.sequence;
		ppcEv.floppy.frame = -1;
		ptr->onSequenceEnd().sendEvent(ppcEv);
	}
	/* Create and send a new event to the entity
	with the updated frame */
	ppc::Event ppcEv(ev);
	ppcEv.type = ppc::Event::FloppyType;
	ppcEv.floppy.sequence = ptr->getSequence();
	ppcEv.floppy.frame = ptr->getFrame();
	ptr->getEntity()->broadcastMessage(ppcEv);
	return true;
}


