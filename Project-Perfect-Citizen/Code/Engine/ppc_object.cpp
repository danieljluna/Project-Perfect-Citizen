#include "ppc_object.h"

#include "ppc_object_component.h"
#include "ppc_object_event.h"


using namespace ppc;




Object::Object(InputComponent* input, 
               DynamicComponent* dynamic, 
               RenderComponent* render) {
    //Link Components
    
};




void Object::send(objMsg message) {
    for (int i = 0; i < MAX_COMPONENTS; ++i) {
        //Broadcast to ith components
        components_[i]->recieve(message);
    }
}
