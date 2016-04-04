#include "event.h"

using namespace ppc;


Event::Event(sf::Event ev) {
    type = sfEventType;
    sfEvent = ev;
}

Event::operator sf::Event() const {
    sf::Event ev;
    if (type == sfEventType) {
        ev = sfEvent;
    } else {
        //Set return type to bogus event type
        ev.type = sf::Event::Count;
    }

    return ev;
}