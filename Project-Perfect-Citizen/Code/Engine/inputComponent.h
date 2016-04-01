#ifndef INPUT_COMPONENT_H
#define INPUT_COMPONENT_H

#include <cstddef>

#include <SFML/Window/Event.hpp>

#include "Component.h"
#include "observer.h"


namespace ppc {

class InputHandler;
class Subject;

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

    ///////////////////////////////////////////////////////////////////
    /// @brief Virtual Destructor
    ///////////////////////////////////////////////////////////////////
    virtual ~InputComponent();

    ///////////////////////////////////////////////////////////////////
    /// @brief Reaction Function
    /// @details Override this function to define how this Component
    ///     reacts to the Events passed to it.
    ///
    /// @param ev The sf::Event passed to this Component when it an
    ///     Observer calls this Component.
    /// @return Denotes whether this observer propogates the event.
    ///////////////////////////////////////////////////////////////////
    virtual bool registerInput(sf::Event& ev) = 0;

    ///////////////////////////////////////////////////////////////////
    /// @brief Returns the index-th observer 
    ///
    /// @pre (index < observerCount_)
    /// @param index The index of the Observer Array you wish to 
    ///     manipulate.
    /// @return A pointer to the Observer desired. Returns nullptr if
    ///     the precondition fails.
    ///////////////////////////////////////////////////////////////////
    BaseObserver* getObserver(size_t index = 0);

    ///////////////////////////////////////////////////////////////////
    /// @brief Sets up an Observer to watch the Subject.
    ///
    /// @pre There is an Observer not currently in use.
    /// @return Whether or not there was an Observer available to 
    ///     assign to the Subject given.
    ///////////////////////////////////////////////////////////////////
    virtual bool watch(Subject& subject);

    ///////////////////////////////////////////////////////////////////
    /// @brief Sets up an Observer to watch for an sf::Event.
    ///
    /// @pre There is an Observer not currently in use.
    /// @return Whether or not there was an Observer available to 
    ///     assign to the InputHandler given.
    ///////////////////////////////////////////////////////////////////
    virtual bool watch(InputHandler& iHandler, sf::Event::EventType type);

    ///////////////////////////////////////////////////////////////////
    /// @brief Detatches Observers connected to this subject.
    /// @details This will detach all Observers related to this 
    ///     InputComponent from the given Subject.
    ///////////////////////////////////////////////////////////////////
    virtual void ignore(Subject& subject);

    ///////////////////////////////////////////////////////////////////
    /// @brief Detatches Observers connected to this subject.
    /// @details This will detach all Observers related to this 
    ///     InputComponent from the given handle in the InputHandler.
    ///////////////////////////////////////////////////////////////////
    virtual void ignore(InputHandler& iHandler, sf::Event::EventType type);


protected:

    ///////////////////////////////////////////////////////////////////
    /// @brief Constructor
    /// @details Creates an InputComponent with the given number of
    ///     Observers to watch events with.
    ///
    /// @param observerCount The number of desired Observers for this
    ///     InputComponent.
    ///////////////////////////////////////////////////////////////////
    InputComponent(size_t observerCount = 1);
	BaseObserver** observerArray_;
	size_t observerCount_;

private:

    size_t findNextObserver();

};


};

#endif  //End INPUT_COMPONENT_H
