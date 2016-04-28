#include "ComponentObsvr.h"
#include "inputComponent.h"
#include "debug.h"
#include "event.h"


using namespace ppc;

ComponentObsvr::ComponentObsvr(InputComponent& iCmpnt) : 
    i_cmpnt_(iCmpnt) {}



bool ComponentObsvr::eventHandler(Event ev) {
    return (i_cmpnt_.registerInput(ev));
}