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
*   a) (0 <= animIndex < animations.size) || (!visible)               *
*   b) (0 <= spriteIndex < animations[animationFrame].size) ||        *
*             (!visible))                                             *
*   c) (spriteVector.size() != 0)                                     *
*                                                                     *
*                                                                     *
* Protected Data:                                                     *
*                                                                     *
*   vector<Animation> _animations -                                   *
*     Holds this object's copy of animations it will use to draw      *
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
* Private Data:                                                       *
*                                                                     *
*   size_t _animation -                                               *
*     Holds the index of the current animation we are interested in   *
*     drawing                                                         *
*                                                                     *
*   size_t _animationFrame -                                          *
*     Holds the index of the sprite in our current animation that we  *
*     are interested in drawing                                       *
*                                                                     *
*                                                                     *
\*********************************************************************/

///////////////////////////////////////////////////////////////////////
// Public Methods
///////////////////////////////////////////////////////////////////////

SprObj::~SprObj() {}

void SprObj::set_visible(const bool vis) {
    //Only let things be visible if they have a sprite to draw
    if (vis || _animations[0].size()) {
        _visible = vis;
    }
}




size_t SprObj::get_animation() {
    return _animation;
}




size_t SprObj::get_animationFrame() {
    return _animationFrame;
}




void SprObj::set_animation(const std::size_t index) {
    if ( (index >= 0) && (index < _animations.size()) &&
            (_animations[index].size()) ) {
        _animation = index;
    }
}




void SprObj::set_animationFrame(const std::size_t index) {
    if ((index >= 0) && (index < _animations[_animation].size())) {
        _animationFrame = index;
    }
}

 

///////////////////////////////////////////////////////////////////////
//  Protected Functions
///////////////////////////////////////////////////////////////////////

SprObj::SprObj(const signed int priority) 
               : _animations() {
    _priority = priority;
    _animation = 0;
    _animationFrame = 0;
    _visible = false;
}




SprObj::SprObj(const std::vector<helios::Animation> &animVec,
               const signed int priority)
               : _animations(animVec) {
    _priority = priority;
    _animation = 0;
    _animationFrame = 0;
    if ((_animations.size()) && (_animations[_animation].size())) {
        _visible = true;
    } else {
        _visible = false;
    }
}




void SprObj::render(sf::RenderTarget &target,
                    sf::RenderStates states) const {
    target.draw(_animations[_animation][_animationFrame], states);
}





}   //namespace helios


