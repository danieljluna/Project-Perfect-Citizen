#ifndef PPC_OBJECT_H
#define PPC_OBJECT_H

#include "ppc_object_component.h"


namespace ppc {
typedef int objMsg;


class Object {
    friend ObjectComponent;
public:
    //Constructors
    Object(InputComponent* input, 
           DynamicComponent* dynamic, 
           RenderComponent* render);

    //Message Broadcaster
    void send(objMsg message);

private:
    //Max Component Count
    static const int MAX_COMPONENTS = 3;
    //Current Component Count
    int componentCount_;
    //Component Reference Array
    ObjectComponent* components_[MAX_COMPONENTS];
};



}   //End namespace ppc


#endif  //End HELIOS_OBJECT_H

