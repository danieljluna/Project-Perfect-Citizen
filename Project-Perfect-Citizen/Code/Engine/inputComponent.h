#ifndef INPUT_COMPONENT_H
#define INPUT_COMPONENT_H

#include <vector>
#include <cstddef>

#include <SFML/Window/Event.hpp>

#include "Component.h"
#include "ComponentObsvr.h"


namespace ppc {
//HACK: This whole class is defunct for now. Will be updated soon
///////////////////////////////////////////////////////////////////////
/// @brief Base Class for all Components handling Input
/// @author Daniel Luna
/// @details Currently not actually functional. Waiting on the 
///     implementation of Observers and Subjects. Not for use yet.
/// 
/// @todo Implement. Requires updated Observer. Currently is more or 
///     less another updateComponent.
///////////////////////////////////////////////////////////////////////
class InputComponent : public Component {
public:

    virtual ~InputComponent() { delete [] observerArray_; };

    virtual void registerInput(sf::Event& ev) = 0;


protected:

    InputComponent(size_t observerCount = 1) {
        observerArray_ = new ComponentObsvr* [observerCount];
        observerCount_ = observerCount;
    };

    ComponentObsvr* getObserver(size_t index = 0) {
        if (index < observerCount_) {
            return observerArray_[index];
        } else { return nullptr; }
    }

private:

    ComponentObsvr** observerArray_;

    size_t observerCount_;

};


};

#endif  //End INPUT_COMPONENT_H
