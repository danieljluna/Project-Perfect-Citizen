#include "helios_sprobj.h"

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
SprObj::SprObj(const unsigned priority = 0) {

}

