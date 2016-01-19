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
/// @todo Implement.
///////////////////////////////////////////////////////////////////////
class InputComponent : public Component {
public:

    static std::vector<InputComponent*> inputVector;


    InputComponent();

    virtual ~InputComponent();

    virtual void getInput() = 0;


private:

    size_t id;

};


};

#endif  //End INPUT_COMPONENT_H
