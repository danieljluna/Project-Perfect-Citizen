#include "helios_sprobj.h"

#include <iostream>

#include <SFML\Graphics\RenderStates.hpp>
#include <SFML\Graphics\RenderTarget.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\Texture.hpp>
#include <SFML\Graphics\Rect.hpp>


namespace helios {



/*********************************************************************\
* SprObj Implementation                                               *
|*********************************************************************|
* AT ALL TIMES, a SprObj MUST follow:                                 *
*   a) all requirements of a BaseObj                                  *
*       i) _roomHandle will only point to a valid Room                *
*   b) (0 <= spriteIndex < spriteVector.size())                       *
*   c) (spriteVector.size() != 0)                                     *
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
// Public Methods
///////////////////////////////////////////////////////////////////////

SprObj::~SprObj() {}

void SprObj::set_visible(const bool vis) {
    if (vis || _spriteVector.size()) {
        _visible = vis;
    }
}
 

///////////////////////////////////////////////////////////////////////
//  Protected Functions
///////////////////////////////////////////////////////////////////////

SprObj::SprObj(const signed int priority) 
               : _spriteVector() {
    _priority = priority;
    _visible = false;
}




SprObj::SprObj(const std::vector<sf::Sprite> &sprVec,
               const signed int priority)
               : _spriteVector(sprVec) {
    _priority = priority;
}




void SprObj::set_sprite_index(const std::size_t index) {
    if ((index >= 0) && (index < _spriteVector.size())) {
        _spriteIndex = index;
    }
}




size_t SprObj::get_sprite_index() {
    return _spriteIndex;
}




void SprObj::render(sf::RenderTarget &target,
                    sf::RenderStates states) const {
    target.draw(_spriteVector[_spriteIndex], states);
}





}   //namespace helios


