#include "debug.h"
#include "entity.h"
#include "component.h"
#include "event.h"

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
    componentCount_ = 0;
}



Entity::Entity(const Entity& other) noexcept {
    for (size_t i = 0; i < maxComponentCount; ++i) {
        components_[i] = (other.components_[i]);
        if (components_[i] != nullptr)
            components_[i]->entity = this;
    }
    componentCount_ = other.componentCount_;
}



Entity& Entity::operator=(const Entity& other) {
    for (size_t i = 0; i < maxComponentCount; ++i) {
        components_[i] = (other.components_[i]);
        if (components_[i] != nullptr)
            components_[i]->entity = this;
    }
    componentCount_ = other.componentCount_;

    return *this;
}




Entity::Entity(Entity&& other) noexcept {
    for (size_t i = 0; i < maxComponentCount; ++i) {
        components_[i] = other.components_[i];
        if (components_[i] != nullptr)
            components_[i]->entity = this;
    }
    componentCount_ = other.componentCount_;
}




Entity::~Entity() {
    //Delete each Component in the component array
    for (size_t i = 0; i < maxComponentCount; ++i) {
        if (components_[i] != nullptr) {
            if (components_[i]->getEntity() == this) {
                components_[i]->setEntity(nullptr);
            }
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
    if (index < maxComponentCount) {
        return components_[index];
    } else {
        std::string msg = "Entity: getComponent used invalid index!";
        throw std::out_of_range(msg);
    }
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




sf::Vector2f& Entity::getPosition() {
    return position_;
}




///////////////////////////////////////////////////////////////////////
// Component Management
///////////////////////////////////////////////////////////////////////

int Entity::addComponent(Component* cmpnt) {
    //Test if we have room for the cmpnt
    if (componentCount_ < maxComponentCount) {
        //Find next open slot
        size_t index = 0;
        while (components_[index] != nullptr) { ++index; }
        components_[index] = cmpnt;
        cmpnt->setEntity(this);
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
            components_[i]->setEntity(nullptr);

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
		components_[index]->setEntity(nullptr); 

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


void Entity::broadcastMessage(ppc::Event message) {
    //Tell each Entity to recieve the message
    for (size_t i = 0; i < componentCount_; ++i) {
        if (components_[i] != nullptr) {
            components_[i]->recieveMessage(message);
        }
    }
}

