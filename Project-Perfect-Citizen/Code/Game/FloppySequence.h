#pragma once

#include <string>
#include <vector>
#include "../Engine/event.h"

namespace ppc {

struct FloppyFrame {
    std::string text = "";
    unsigned int emotion = 0;
};


struct FloppySequence {
    //Frames in the sequence
    std::vector<FloppyFrame> frames = {};
    //Whether or not it automatically goes to the next seq on finish
    bool autoShift = true;
    //Whether or not it needs a trigger to finish
    bool needTrigger = true;
    //The aforementioned trigger
    Event Trigger;
};


};


