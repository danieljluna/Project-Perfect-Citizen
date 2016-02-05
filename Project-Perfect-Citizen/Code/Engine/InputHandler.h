#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H


#include "subject.h"
#include <SFML/Window/Event.hpp>
#include <map>

namespace ppc {


///////////////////////////////////////////////////////////////////////
/// @brief Class that maps sf::Events to Subjects.
/// @author Daniel Luna
/// @details 
///////////////////////////////////////////////////////////////////////
class InputHandler {
public:

  /////////////////////////////////////////////////////////////////////
  // Constructors and Destructor
  /////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////
    /// @brief Default Constructor
    ///////////////////////////////////////////////////////////////////
    InputHandler();

    ///////////////////////////////////////////////////////////////////
    /// @brief Destructor
    ///////////////////////////////////////////////////////////////////
    ~InputHandler();

  /////////////////////////////////////////////////////////////////////
  // Manipulating Subjects
  /////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////
    /// @brief Adds a handle for the given event.
    /// @details If there is already a handle for the given EventType, 
    ///     then it is not duplicated.
    ///
    /// @param type The type of sf::Event to create a handle for.
    ///////////////////////////////////////////////////////////////////
    void addHandle(sf::Event::EventType type);

    ///////////////////////////////////////////////////////////////////
    /// @brief Called to register a given event.
    /// @details Finds the correct handle for the given event based on
    ///     its type, and then notifies the interested parties.
    ///
    /// @param ev The Event to handle.
    ///////////////////////////////////////////////////////////////////
    void registerEvent(sf::Event& ev);


  /////////////////////////////////////////////////////////////////////
  // Manipulating Observers
  /////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////
    /// @brief Attaches the observer to the EventType.
    /// @details 
    /// 
    /// @param type The EventType the Observer is interested in.
    /// @param obsvr A pointer to the Observer to add.
    /// @param forceCreation Whether or not the InputHandler should 
    ///     create a new handle for the given EventType if it doesn not
    ///     exist already.
    /// @return A bool denoting whether the Observer was mapped
    ///     successfully to a handle.
    ///////////////////////////////////////////////////////////////////
    bool addObserver(sf::Event::EventType type,
                     BaseObserver* obsvr,
                     bool forceCreation = false);

    ///////////////////////////////////////////////////////////////////
    /// @brief Removes the observer from the given handle.
    /// 
    /// @param type The EventType that the observer should be 
    ///     disconnected from.
    /// @param obsvr A pointer to the Observer to remove.
    ///////////////////////////////////////////////////////////////////
    void removeObserver(sf::Event::EventType type,
                        BaseObserver* obsvr);

    ///////////////////////////////////////////////////////////////////
    /// @brief Removes Observers by id
    /// @details Removes all Observers attached to this Subject with
    ///     the id given. If a range is specified, this function will
    ///     remove any Observers with ids in the range of 
    ///     [obsvr_id, obsvr_id + range)
    ///
    /// @param type The EventType that the observer should be 
    ///     disconnected from.
    /// @param obsvr_id The id to remove. If a range is specified, it
    ///     marks the low end of the range.
    /// @param range The number of ids in the range to remove. i.e. if
    ///     range is 2, then obsvr_id and obsvr_id + 1 will be removed
    ///     if found.
    ///////////////////////////////////////////////////////////////////
    void removeObserver(sf::Event::EventType type,
                        unsigned int id,
                        unsigned int range = 1);


private:

    //Map of Events to Subjects
    std::map<sf::Event::EventType, Subject> inputMap;


};


};  //End namespace ppc


#endif //End INPUT_HANDLER_H
