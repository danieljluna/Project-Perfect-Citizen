#include "event.h"

using namespace ppc;


Event::Event() {
    type = Count;
}


Event::Event(sf::Event ev) {
    type = sfEventType;
    sfEvent = ev;
}


Event::operator sf::Event&() {
    if (type != sfEventType) {
        //Set return type to bogus event type
        sfEvent.type = sf::Event::Count;
    }

    return sfEvent;
}



bool Event::operator==(const ppc::Event& other) const {
    bool result = false;

    if (type == other.type) {

        switch (type) {
        case ButtonType:
            result = (buttons.state == other.buttons.state)
                && (buttons.activation == other.buttons.activation);
            break;
        case OpenType:
            result = (open.winType == other.open.winType);
            break;
        case NetworkType:
            result = (network.type == other.network.type);
            break;
        case TimerType:
            result = (timer.action == other.timer.action);
            break;
        case SubmissionType:
            result = (submission.type == other.submission.type);
            break;
        case sfEventType:
        case AbleType:
        case FloppyType:
        case NotificationType:
            result = true;
        case Count:
            break;
        }
    }

    return result;
}


