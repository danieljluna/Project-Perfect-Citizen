#include "Entity.h"

using namespace ppc;


///////////////////////////////////////////////////////////////////////
// Constructors
///////////////////////////////////////////////////////////////////////

Entity::Entity() {
    //Initialize component array to nullptr
    for (size_t i = 0; i < maxComponentCount; ++i) {
        components[i] = nullptr;
    }
}




Entity::~Entity() {
    //Delete each Component in the component array
    for (size_t i = 0; i < maxComponentCount; ++i) {
        if (components[i] != nullptr) {
            delete components[i];
        }
    }
}




///////////////////////////////////////////////////////////////////////
// Component Management
///////////////////////////////////////////////////////////////////////

int Entity::addComponent(Component* cmpnt) {
    //Find the first - if any - nullptr in components
    size_t id = 0;
    while ((components[id] != nullptr) && (id < maxComponentCount)) {
        ++id;
    }

    //Test if we found a valid index / id
    if (id == maxComponentCount) {
        //If not, return -1
        return -1;
    } else {    //If we found a valid index
        //Store cmpnt and return the index
        components[id] = cmpnt;
        return int(id);
    }
}




///////////////////////////////////////////////////////////////////////
// Message System
///////////////////////////////////////////////////////////////////////

void Entity::broadcastMessage(unsigned int message) {
    //Tell each Entity to recieve the message
    for (size_t i = 0; i < maxComponentCount; ++i) {
        if (components[i] != nullptr) {
            components[i]->recieveMessage(message);
        }
    }
}


