#ifndef COMPONENT_OBSVR_H
#define COMPONENT_OBSVR_H

#include "observer.h"

namespace ppc {

class InputComponent;

///////////////////////////////////////////////////////////////////////
/// @brief Observer designed for use by InputComponents.
/// @author Daniel Luna
/// @details Since InputComponents have their own function to react to
///     events, this observer's job is merely to activate that Input
///     Component when an event is observed.
///////////////////////////////////////////////////////////////////////
class ComponentObsvr : public BaseObserver {
public:

  /////////////////////////////////////////////////////////////////////
  // Constructors & Destructor
  /////////////////////////////////////////////////////////////////////
    
    //No Default Constructor
    ComponentObsvr() = delete;

    ///////////////////////////////////////////////////////////////////
    /// @brief Constructor
    /// @details Creates a ComponentObserver tied to the given 
    ///     InputComponent.
    ///
    /// @param iCmpnt The InputComponent to tie this Observer to.
    ///////////////////////////////////////////////////////////////////
    ComponentObsvr(InputComponent& iCmpnt);


  /////////////////////////////////////////////////////////////////////
  // EventHandler Function
  /////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////
    /// @brief Virtaul eventHandler
    /// @details Merely call the registerEvent() function on the
    ///     InputComponent this Observer is tied to.
    ///
    /// @param event The event this Observer was notified of.
    /// @return Denotes whether this observer propogates the event.
    ///////////////////////////////////////////////////////////////////
    virtual bool eventHandler(Event ev) override;

private:

    //Stores a pointer to the InputComponent to notify
    InputComponent& i_cmpnt_;


};


};  //End namespace ppc


#endif  //End COMPONENT_OBSVR_H
