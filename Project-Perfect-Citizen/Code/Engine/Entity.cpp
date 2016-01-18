#include "entity.h"
#include "component.h"

#include <stdexcept>

using namespace ppc;


///////////////////////////////////////////////////////////////////////
// Constructors
///////////////////////////////////////////////////////////////////////

Entity::Entity() {
    //Initialize component array to nullptr
    for (size_t i = 0; i < maxComponentCount; ++i) {
        components_[i] = nullptr;
    }
}




Entity::~Entity() {
    //Delete each Component in the component array
    for (size_t i = 0; i < maxComponentCount; ++i) {
        if (components_[i] != nullptr) {
            components_[i]->entity = nullptr;
            delete components_[i];
        }
    }
}




///////////////////////////////////////////////////////////////////////
// Getters
///////////////////////////////////////////////////////////////////////

size_t Entity::cmpntCount() {
    return componentCount_;
}




Component* Entity::getComponent(size_t index) {
    return components_[index];
}




int Entity::getIndex(Component* cmpnt) {
    //Assume we won't find it
    int result = -1;

    //Search through the Components_
    for (size_t i = 0; i < componentCount_; ++i) {
        //If we find the cmpnt specified
        if (components_[i] == cmpnt) {
            //Overwrite the result
            result = i;
            break;
        }
    }

    return result;
}




///////////////////////////////////////////////////////////////////////
// Component Management
///////////////////////////////////////////////////////////////////////

int Entity::addComponent(Component* cmpnt) {
    //Test if we have room for the cmpnt
    if (componentCount_ < maxComponentCount) {
        //Store cmpnt and return the index it was stored at
        components_[componentCount_] = cmpnt;
        cmpnt->entity = this;
        return componentCount_++;
    } else {
        //If there is no room, return -1
        return -1;
    }
}




void Entity::removeComponent(Component* cmpnt) {
    //Search through the Components_
    for (size_t i = 0; i < componentCount_; ++i) {
        //If we find the cmpnt specified
        if (components_[i] == cmpnt) {
            //Inform the Component we no longer want it (Bloody Orphan)
            components_[i]->entity = nullptr;

            //Swap it around the array to retain continuity
            //Also, decrement componentCount
            components_[i] = components_[--componentCount_];
            components_[componentCount_] = nullptr;
            break;
        }
    }
}




void Entity::removeComponent(size_t index) {
    if (index < componentCount_) {
        //Inform the Component we no longer want it (Bloody Orphan)
        components_[index]->entity = nullptr;

        //Swap it around the array to retain continuity
        //Also, decrement componentCount
        components_[index] = components_[--componentCount_];
        components_[componentCount_] = nullptr;
    } else {
        throw std::out_of_range("Entity: Removal using an invalid index.");
    }
}




///////////////////////////////////////////////////////////////////////
// Message System
///////////////////////////////////////////////////////////////////////

void Entity::broadcastMessage(msgType message) {
    //Tell each Entity to recieve the message
    for (size_t i = 0; i < componentCount_; ++i) {
        if (components_[i] != nullptr) {
            components_[i]->recieveMessage(message);
        }
    }
}


