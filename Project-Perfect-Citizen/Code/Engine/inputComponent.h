#ifndef INPUT_COMPONENT_H
#define INPUT_COMPONENT_H

#include <vector>
#include <cstddef>

#include "Component.h"


namespace ppc {

///////////////////////////////////////////////////////////////////////
/// @brief Base Class for all Components handling Input
/// @details Currently not actually functional. Waiting on the 
///     implementation of Observers and Subjects. Not for use yet.
/// 
/// @todo Implement. Requires updated Observer
///////////////////////////////////////////////////////////////////////
class InputComponent : public Component {
public:

    virtual ~InputComponent() {};


    virtual void registerInput() = 0;


protected:

    InputComponent() {};

};


};

#endif  //End INPUT_COMPONENT_H
