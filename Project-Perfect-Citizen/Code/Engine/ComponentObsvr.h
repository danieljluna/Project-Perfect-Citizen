#ifndef COMPONENT_OBSVR_H
#define COMPONENT_OBSVR_H

#include "observer.h"

namespace ppc {

class InputComponent;

///////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////
class ComponentObsvr : public BaseObserver {
public:
    
    //No Default Constructor
    ComponentObsvr() = delete;

    ComponentObsvr(InputComponent& input);



    virtual void eventHandler(sf::Event& ev) override;

private:

    //Stores a pointer to the InputComponent to notify
    InputComponent* i_cmpnt_;


};

};


#endif  //End COMPONENT_OBSVR_H
