#include "hls_object.h"

using namespace hls;




Object::Object(InputComponent* input, 
               DynamicComponent* dynamic, 
               RenderComponent* render) {
    //Link Components
    
};




void Object::send(Object::msgType message) {
    for (int i = 0; i < MAX_COMPONENTS; ++i) {
        //Broadcast to ith components
        components_[i]->recieve(message);
    }
}
