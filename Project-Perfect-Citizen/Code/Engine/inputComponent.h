#ifndef INPUT_COMPONENT_H
#define INPUT_COMPONENT_H

#include <cstddef>

#include <SFML/Window/Event.hpp>

#include "Component.h"
#include "ComponentObsvr.h"


namespace ppc {

class InputHandler;

///////////////////////////////////////////////////////////////////////
/// @brief Base Class for all Components handling Input
/// @author Daniel Luna
/// @details InputComponents make use of ComponentObsvrs to react to
///     Input during the Input phase of the main loop. The reaction is
///     defined in registerInput(sf::Event&), which is passed the event
///     to react to by its observers. The observers managed by the
///     InputComponent use a reference to an InputHandler to link up
///     with the proper Subjects.
///////////////////////////////////////////////////////////////////////
class InputComponent : public Component {
public:

    virtual ~InputComponent();

    virtual void registerInput(sf::Event& ev) = 0;


protected:

    InputComponent(size_t observerCount = 1);

    ComponentObsvr* getObserver(size_t index = 0);

    bool watch(Subject& subject);

    bool watch(InputHandler& iHandler, sf::Event::EventType type);

    bool ignore(Subject& subject);

    bool ignore(InputHandler& iHandler, sf::Event::EventType type);


private:

    ComponentObsvr** observerArray_;

    size_t observerCount_;

};


};

#endif  //End INPUT_COMPONENT_H
