#ifndef HELIOS_OBJECT_H
#define HELIOS_OBJECT_H

#include "hls_object_component.h"

namespace hls {

class Object {
public:
    //Message Broadcaster
    void send(int message) {
        //Broadcast to ith components
    }

    //Constructors
    Object(InputComponent &input, DynamicComponent &dynamic, RenderComponent &render);

private:
    //Component Array
    Component* components_[]
};

}   //End namespace hls


#endif  //End HELIOS_OBJECT_H

