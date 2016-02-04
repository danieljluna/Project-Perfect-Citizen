#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H


#include "subject.h"
#include <SFML/Window/Event.hpp>
#include <map>

namespace ppc {


///////////////////////////////////////////////////////////////////////
/// @brief Class that maps sf::Events to Subjects.
/// @author Daniel Luna
///////////////////////////////////////////////////////////////////////
class InputHandler {
public:

  /////////////////////////////////////////////////////////////////////
  // Constructors and Destructor
  /////////////////////////////////////////////////////////////////////

    //Default Constructor
    InputHandler();

    //Destructor
    ~InputHandler();

  /////////////////////////////////////////////////////////////////////
  // Manipulating Subjects
  /////////////////////////////////////////////////////////////////////

    //Adds a Handle mapped to the given event if not already in
    void addHandle(sf::Event::EventType type);

    //Called to register a given event
    void registerEvent(sf::Event& ev);


  /////////////////////////////////////////////////////////////////////
  // Manipulating Observers
  /////////////////////////////////////////////////////////////////////

    //Attaches the observer to the EventType
    bool addObserver(sf::Event::EventType type,
                     BaseObserver* obsvr,
                     bool forceCreation = false);


private:

    //Map of Events to Subjects
    std::map<sf::Event::EventType, Subject> inputMap;


};


};


#endif //End INPUT_HANDLER_H
