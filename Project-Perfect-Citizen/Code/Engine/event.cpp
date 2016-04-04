#include "event.h"

using namespace ppc;


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