#ifndef HELIOS_OBJECT_H
#define HELIOS_OBJECT_H

#include "hls_object_component.h"

namespace hls {

class Object {
    friend ObjectComponent;
    typedef int msgType;
public:
    //Constructors
    Object(InputComponent* input, 
           DynamicComponent* dynamic, 
           RenderComponent* render);

    //Message Broadcaster
    void send(msgType message);

private:
    //Max Component Count
    static const int MAX_COMPONENTS = 3;
    //Current Component Count
    int componentCount_;
    //Component Reference Array
    ObjectComponent* components_[MAX_COMPONENTS];
};

}   //End namespace hls


#endif  //End HELIOS_OBJECT_H

