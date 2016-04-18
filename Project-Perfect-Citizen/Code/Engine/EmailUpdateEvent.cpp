#include "EmailUpdateEvent.h"
#include "World.h"
#include "desktop.h"

using namespace ppc;


EmailUpdate::EmailUpdate() {
    int size = World::getCurrDesktop().getInbox()->getInboxSize();
    newEmailArray = new bool[size];
}

bool& EmailUpdate::operator[](size_t index) {
    return newEmailArray[index];
};

const bool EmailUpdate::operator[](size_t index) const {
    return newEmailArray[index];
};