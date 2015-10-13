#include "helios_main.h"
using namespace Helios;
 /*******************************************************************\
 *  BaseObj Implementation                                           *
 \*******************************************************************/
//TODO: Implement BaseObject Class

///////////////////////////////////////////////////////////////////////
/// Constructors & Destructors
///////////////////////////////////////////////////////////////////////

BaseObj::BaseObj() : _sprite(), _roomHandle(nullptr), _visible(false) {}

BaseObj::~BaseObj() {}


///////////////////////////////////////////////////////////////////////
/// Accsessor Functions
///////////////////////////////////////////////////////////////////////

bool BaseObj::visible() const { 
    return _visible; 
}

bool BaseObj::active() const {
    return _roomHandle != nullptr;
}


///////////////////////////////////////////////////////////////////////
/// Mutator Functions
///////////////////////////////////////////////////////////////////////

void BaseObj::set_visible(const bool vis) {
    _visible = vis;
}

void BaseObj::Activate(Room &roomHandle) {
    _roomHandle = &roomHandle;
    _roomHandle->LinkObject(//TODO: Fill in);
}

void BaseObj::Deactivate() {

}

//End-BaseObj--------------------------------------------------------


/*******************************************************************\
*  Room Implementation                                              *
\*******************************************************************/
//TODO: Implement Room Class
