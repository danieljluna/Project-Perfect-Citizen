#ifndef COMPONENT_OBSVR_H
#define COMPONENT_OBSVR_H

#include "observer.h"

namespace ppc {

class InputComponent;

///////////////////////////////////////////////////////////////////////
/// @brief Observer used by InputComponents
///////////////////////////////////////////////////////////////////////
class ComponentObsvr : public BaseObserver {
public:
    
    //No Default Constructor
    ComponentObsvr() = delete;

    ComponentObsvr(InputComponent& iCmpnt);



    virtual void eventHandler(sf::Event& ev) override;

private:

    //Stores a pointer to the InputComponent to notify
    InputComponent& i_cmpnt_;


};


};  //End namespace ppc


#endif  //End COMPONENT_OBSVR_H
