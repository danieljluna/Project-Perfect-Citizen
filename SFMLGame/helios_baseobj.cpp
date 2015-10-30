#include "helios_baseobj.h"

#include "helios_room.h"

using namespace Helios;


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
/// Constructors & Destructors
///////////////////////////////////////////////////////////////////////

BaseObj::BaseObj(const unsigned int priority) : 
    _roomHandle(nullptr),
    _visible(false), 
    _priority(priority) {}

BaseObj::~BaseObj() {}


///////////////////////////////////////////////////////////////////////
/// Accsessor Functions
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
/// Mutator Functions
///////////////////////////////////////////////////////////////////////

void BaseObj::Activate(Room &roomHandle) {
    _roomHandle = &roomHandle;
    _roomHandle->LinkObject(this);
}

void BaseObj::Deactivate() {
    _roomHandle->UnlinkObject(this);
    _roomHandle = nullptr;
}

void BaseObj::set_priority(const unsigned int prior) {
    _priority = prior;
}

void BaseObj::set_visible(const bool vis) {
    _visible = vis;
}


///////////////////////////////////////////////////////////////////////
/// Draw Functions
///////////////////////////////////////////////////////////////////////

void BaseObj::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (_visible) render(target, states);
}
