#include "helios_room.h"

#include "helios_baseobj.h"

using namespace Helios;


/*********************************************************************\
* Room Implementation                                                 *
|*********************************************************************|
* AT ALL TIMES, a BaseObj MUST follow:                                *
*   a)                                                                *
*                                                                     *
*                                                                     *
\*********************************************************************/
//TODO: Implement Room Class

///////////////////////////////////////////////////////////////////////
/// Constructors & Destructors:
///////////////////////////////////////////////////////////////////////

Room::Room(sf::Vector2u roomSize) :
    _size(roomSize) {}

//Destructor
Room::~Room() {}


//Step & Frame Functions:

sf::Time Room::Update() {

    for (auto it = _updateList.begin();
        it != _updateList.end();
        ++it) {
        //If object priority needs to increase, do so before updating
        //in order to avoid double updates.
        if (it->first < it->second->get_priority()) {
            UpdateObjectPriority(it);
        }
        it->second->Update();
        //If object priority needs to decrease, do so after updating in
        //order to avoid skipping updates.
        if (it->first > it->second->get_priority()) {
            UpdateObjectPriority(it);
        }
    }
}


//Object Management Functions:

//Adds object to appropriate management lists
void Room::LinkObject(BaseObj *objPtr) {
    //Link the Object to the update list
    _updateList.emplace(objPtr->_priority, objPtr);
}

//Removes object from all management lists
void Room::UnlinkObject(BaseObj *objPtr) {
    //Search for object in updateList
    auto searchRange = _updateList.equal_range(objPtr->_priority);
    auto it = searchRange.first;
    while ((it != searchRange.second) || (it->second != objPtr)) {
        ++it;
    }   //while loop

    //If we find the object node, erase it
    if (it != searchRange.second) {
        _updateList.erase(it);
    }
}


//Private Methods

void Room::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (auto it = _updateList.begin();
        it != _updateList.end();
        ++it)
    {
        it->second->draw(target, states);
    }
}


void Room::UpdateObjectPriority(mmapIntObj::iterator objItor) {
    //Make sure priority of object needs updating
    if (objItor->first != objItor->second->_priority) {
        //Replace outdated priority node with correct key value
        _updateList.emplace(
            objItor->second->_priority,
            objItor->second
            );
        _updateList.erase(objItor);
    }
}

//End-Room-------------------------------------------------------------
