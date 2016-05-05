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
#include "../Engine/World.h"
#include "../Engine/desktop.h"

#include "../Engine/FreeFunctionObserver.h"
#include "../Engine/Network.h"

using namespace ppc;

const std::string FLOPPY_DEBUG_CODE = "fl";

std::vector<FloppySequence> FloppyInputComponent::floppyDictionary = {};
bool FloppyInputComponent::initialized = false;

FloppyInputComponent::FloppyInputComponent() {

    if (!initialized) {
        initializeFloppyDict();
    }
}

FloppyInputComponent::~FloppyInputComponent() {

}

const std::array<std::string, 2> FLOPPY_SOURCES{
	"PipelineTutorial.txt",
	"DesktopTutorial.txt"
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
			FloppySequence sequence;
			while (std::getline(myfile, line)) {
				if (line.substr(0, 1).compare("-") == 0) {
					if (sequence.frames.empty()) {
                        size_t tokenIndex = line.find_first_of(':');
						label = line.substr(1, tokenIndex - 1);
                        if (line.substr(tokenIndex + 2, 1) == "F") 
                            sequence.autoShift = false;
						continue;
					}

					floppyDictionary.push_back(sequence);
                    size_t tokenIndex = line.find_first_of(':');
                    label = line.substr(1, tokenIndex - 1);
                    if (line.substr(tokenIndex + 2, 1) == "F") {
                        sequence.autoShift = false;
                    } else {
                        sequence.autoShift = true;
                    }
					sequence.frames.clear();
				}
				else {
					if (line.length() == 0) continue;
					std::string emotion = line.substr(0, line.find_first_of(':'));
					line = line.substr(line.find_first_of(':'));
					FloppyFrame newExpr;

					if (FLOPPY_EMOTION_MAP.find(emotion) != FLOPPY_EMOTION_MAP.end()) {
						newExpr.emotion = FLOPPY_EMOTION_MAP.at(emotion);
					}
					else newExpr.emotion = FLOPPY_EMOTION_MAP.at("Default");
					
					newExpr.text = line.substr(2);
					sequence.frames.push_back(newExpr);

				}
			}
			floppyDictionary.push_back(sequence);
		}
		else {
			DEBUGF(FLOPPY_DEBUG_CODE, filename + " could not be opened");
		}
		myfile.close();
	}

    initialized = true;
}

unsigned int ppc::FloppyInputComponent::getFrame() { return frame; }

unsigned int ppc::FloppyInputComponent::getSequence() { return sequence; }

void ppc::FloppyInputComponent::setFrame(unsigned int f) { 
    frame = f; 
    Event ev;

    if (floppyDictionary.at(sequence).frames.size() <= frame) {
        frame = -1;
        ev.type = Event::AbleType;
        ev.able.enable = false;
        getEntity()->broadcastMessage(ev);


        ev.type = ppc::Event::FloppyType;
        ev.floppy.sequence = sequence;
        ev.floppy.frame = -1;
        onSequenceEnd().sendEvent(ev);
    }

    ev.type = ppc::Event::FloppyType;
    ev.floppy.sequence = sequence;
    ev.floppy.frame = frame;
    getEntity()->broadcastMessage(ev);

    if (frame == floppyDictionary.at(sequence).frames.size() - 1) {
        setFloppyButton(!floppyDictionary.at(sequence).needTrigger);
    }
}

void ppc::FloppyInputComponent::setSequence(unsigned int s, unsigned int f) { 
    if (s < floppyDictionary.size()) {
        sequence = s;
    } else {
        sequence = -1;
    }
    setFrame(f);
}

void ppc::FloppyInputComponent::advanceFrame() { 
	setFrame(frame + 1);
}

void ppc::FloppyInputComponent::regressFrame() { 
    setFrame(frame - 1);
}

void ppc::FloppyInputComponent::advanceSequence() { 
    setSequence(sequence + 1);
}

void ppc::FloppyInputComponent::regressSequence() { 
    setSequence(sequence - 1);
}

bool ppc::FloppyInputComponent::registerInput(Event ev) { return true; }

void ppc::FloppyInputComponent::setFloppyButtonRenderCmpt(buttonRenderComponent * brc)
{
	floppyBtnRndr = brc;
}

void ppc::FloppyInputComponent::setFloppyButtonInputCmpt(mousePressButton * mpb)
{
	floppyBtnInpt = mpb;
}

void ppc::FloppyInputComponent::setFloppyTextRenderCmpt(TextDisplayRenderComponent * txt)
{
	floppyTxtRndr = txt;
}

void ppc::FloppyInputComponent::setFloppyButton(bool able)
{
	ppc::Event ppcEv;
	ppcEv.type = ppc::Event::EventTypes::AbleType;
	ppcEv.able.enable = able;
	floppyBtnInpt->recieveMessage(ppcEv);
	floppyBtnRndr->recieveMessage(ppcEv);
	floppyTxtRndr->recieveMessage(ppcEv);
}

bool ppc::summonFloppyDialog(FloppyInputComponent* ptr, ppc::Event ev) {
    bool wasSummoned = false;
    unsigned int frame = 0, sequence = 0;

	switch (ev.type) {
    case ppc::Event::FloppyType:

        //If we just ended a frame
        if (ev.floppy.frame == -1) {
            //If we just ended the Welcome
            if (ev.floppy.sequence == 2) {
                World::getCurrDesktop().incrementNetVecIndex();
            } 
            if (FloppyInputComponent::floppyDictionary.at(ev.floppy.sequence).autoShift) {
                wasSummoned = true;
                ev.floppy.frame = 0;
                ++ev.floppy.sequence;
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
            ev.floppy.frame = 0;
            switch (World::getCurrDesktop().getNetVecIndex()) {
            case 0:
				ev.floppy.sequence = FloppyInputComponent::Welcome;
                break;
            case 1:
				ev.floppy.sequence = FloppyInputComponent::Goal;
                break;
            }
        }
        break;
	}

    if (wasSummoned) {
        /* Also let the textbox and button that
        they should spawn */
        ptr->setSequence(ev.floppy.sequence, ev.floppy.frame);
        ptr->getEntity()->broadcastMessage(ev);

        ev.type = ppc::Event::AbleType;
        ev.able.enable = true;
        ptr->getEntity()->broadcastMessage(ev);
    }

	return true;
}


bool ppc::incrementFloppyDialog(FloppyInputComponent* ptr, ppc::Event ev) {

	/* Advance the frame state to be one more than
	the stored value */
    if (ptr->getFrame() != -1) {
        ptr->advanceFrame();
    }

	return true;
}




bool ppc::enableFloppyDialog(FloppyInputComponent* ptr, ppc::Event ev) {
    bool enable = false;

    //Switch controls what event needs to be read to move on
    switch (ptr->getSequence()) {
	case FloppyInputComponent::Welcome:
		enable = ((ev.type == ev.NetworkType) &&
            (ev.network.type == ev.network.Selected) &&
            (ev.network.v == -1));
        break;
	case FloppyInputComponent::Connections:
        enable = ((ev.type == ev.NetworkType) &&
            (ev.network.type == ev.network.Created) &&
            (ev.network.v != -1));
        break;
	case FloppyInputComponent::Edges:
        enable = ((ev.type == ev.NetworkType) &&
            (ev.network.type == ev.network.Removed) &&
            (ev.network.v != -1));
        break;
	case FloppyInputComponent::TempFix:
		enable = true;
		break;
	case FloppyInputComponent::Goal:
        enable = (ev.type == ev.NetworkType);
        if (enable) {
            enable = ev.network.net->checkColorlessEdgeEquality(*World::getCurrDesktop().getSolVec()[1]) == 1.0f;
        }
        break;
	case FloppyInputComponent::Suspicion:
        enable = (ev.type == ev.NetworkType);
        if (enable) {
            enable = ev.network.net->checkEdgeEquality(*World::getCurrDesktop().getSolVec()[1]) == 1.0f;
        }
        break;
	case FloppyInputComponent::Center:
        enable = ((ev.type == ev.NetworkType) &&
                  (ev.network.type == ev.network.Center));
        if (enable) {
            ev.network.net->checkCenterEquality(*World::getCurrDesktop().getSolVec()[1]);
        }
        break;
	case FloppyInputComponent::Submission:
		enable = true;
		break;
	case FloppyInputComponent::Feedback:
        enable = true;
        break;
	case FloppyInputComponent::DesktopStart:
        enable = ((ev.type == ev.OpenType) &&
            (ev.open.winType == ev.open.Email));
        break;
	case FloppyInputComponent::Email:
        enable = ((ev.type == ev.OpenType) &&
            (ev.open.winType == ev.open.Explorer));
        break;
	case FloppyInputComponent::Explorer:
        enable = ((ev.type == ev.OpenType) && 
                  (ev.open.winType == ev.open.File));
        break;
	case FloppyInputComponent::Passwords:
	case FloppyInputComponent::SuspFolder:
	case FloppyInputComponent::Scanning:
	case FloppyInputComponent::DeskSubmission:
	case FloppyInputComponent::Wrapup:
        enable = true;
        break;
    default:
        break;
    }

    if (enable)
        ptr->setFloppyButton(enable);

    return true;
}

