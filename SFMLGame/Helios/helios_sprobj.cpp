#include "helios_sprobj.h"

#include "SFML\Graphics\Sprite.hpp"
#include "SFML\Graphics\RenderTarget.hpp"
#include "SFML\Graphics\RenderStates.hpp"

using namespace Helios;

/*********************************************************************\
* SprObj Implementation                                               *
|*********************************************************************|
* AT ALL TIMES, a SprObj MUST follow:                                 *
*   a) all requirements of a BaseObj                                  *
*       i) _roomHandle will only point to a valid Room                *
*   b) (0 <= spriteIndex < sprVector.size()) || (spriteIndex = -1)    *
*                                                                     *
*                                                                     *
* Inherited Protected Data:                                           *
*                                                                     *
*   unsigned int _priority -                                          *
*     Holds the priority for this object where the Room this object   *
*     is active in can check it to properly maintain update lists     *
*                                                                     *
*   bool _visible -                                                   *
*     A bool regulating whether or not this object should be drawn    *
*                                                                     *
*                                                                     *
\*********************************************************************/

///////////////////////////////////////////////////////////////////////
//  Protected Functions
///////////////////////////////////////////////////////////////////////

SprObj::SprObj(const unsigned priority) {
    _priority = priority;
}

void SprObj::render(sf::RenderTarget &target, sf::RenderStates states)  const {
    target.draw(_sprite, states);
}
