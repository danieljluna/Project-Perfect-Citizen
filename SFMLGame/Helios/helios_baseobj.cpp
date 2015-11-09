#include "helios_baseobj.h"

#include "helios_room.h"

namespace helios {


/*********************************************************************\
* BaseObj Implementation                                              *
|*********************************************************************|
* AT ALL TIMES, a BaseObj MUST follow:                                *
*   a) _roomHandle will only point to a valid Room                    *
*                                                                     *
*                                                                     *
* Protected Data:                                                     *
*                                                                     *
*   unsigned int _priority -                                          *
*     Holds the priority for this object where the Room this object   *
*     is active in can check it to properly maintain update lists     *
*                                                                     *
*   bool _visible -                                                   *
*     A bool regulating whether or not this object should be drawn    *
*                                                                     *
*                                                                     *
* Private Data:                                                       *
*                                                                     *
*   Room* _roomHandle -                                               *
*     Points to the Room in charge of handling this object            *
*                                                                     *
\*********************************************************************/
//TODO: Comment BaseObj Implementation


///////////////////////////////////////////////////////////////////////
//  Constructors & Destructors
///////////////////////////////////////////////////////////////////////

BaseObj::BaseObj(const unsigned int priority) : 
    _roomHandle(nullptr),
    _visible(false), 
    _priority(priority) {}




BaseObj::~BaseObj() {}


///////////////////////////////////////////////////////////////////////
//  Accsessor Functions
///////////////////////////////////////////////////////////////////////

Room* BaseObj::get_room() const {
    return _roomHandle;
}




signed int BaseObj::get_priority() const {
    return _priority;
}




bool BaseObj::is_visible() const {
    return _visible; 
}




bool BaseObj::is_active() const {
    return (_roomHandle != nullptr);
}


///////////////////////////////////////////////////////////////////////
//  Mutator Functions
///////////////////////////////////////////////////////////////////////

void BaseObj::Activate(Room* roomPtr) {
    _roomHandle = roomPtr;
    _roomHandle->LinkObject(this);
}




void BaseObj::Deactivate() {
    _roomHandle->UnlinkObject(this);
    _roomHandle = nullptr;
}


///////////////////////////////////////////////////////////////////////
//  Draw Functions
///////////////////////////////////////////////////////////////////////

void BaseObj::draw(sf::RenderTarget &target, 
                   sf::RenderStates states) const {
    if (_visible) { render(target, states); }
}


}   //namespace helios

