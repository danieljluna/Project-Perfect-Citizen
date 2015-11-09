#include "aoe_unit.h"

namespace aoe {

/*********************************************************************\
* Unit Implementation                                                 *
|*********************************************************************|
* AT ALL TIMES, a Unit MUST follow:                                   *
*   a) all requirements of a SprObj                                   *
*       iii (spriteVector.size() != 0)                                *
*                                                                     *
*                                                                     *
\*********************************************************************/

///////////////////////////////////////////////////////////////////////
// Constructors and Destructors
///////////////////////////////////////////////////////////////////////

Unit::Unit(const signed int _priority) 
           : SprObj(_priority) {
    _animations = defaultAnimations;
    if ((defaultAnimations.size()) && (defaultAnimations[0].size())) {
        set_visible(true);
    }
}




Unit::Unit(const std::vector<helios::Animation> &sprVec,
           const signed int _priority) 
           : SprObj(sprVec, _priority) {}




Unit::~Unit() {}


///////////////////////////////////////////////////////////////////////
// Step and Update Functions:
///////////////////////////////////////////////////////////////////////

void Unit::Update() {}


///////////////////////////////////////////////////////////////////////
// Initialization of Static Members:
///////////////////////////////////////////////////////////////////////

std::vector<helios::Animation> Unit::defaultAnimations{};

enum anim_ref {
    ANIM_BASIC = 0
};

}   //namespace aoe
