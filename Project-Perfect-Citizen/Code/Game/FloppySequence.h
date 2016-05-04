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
    std::vector<FloppyFrame> frames = {};
    bool autoShift = true;
    bool needTrigger = true;
    Event Trigger;
};


};


