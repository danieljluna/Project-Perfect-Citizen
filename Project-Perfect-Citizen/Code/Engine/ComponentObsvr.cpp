#include "ComponentObsvr.h"
#include "inputComponent.h"
#include "../Engine/debug.h"
using namespace ppc;

ComponentObsvr::ComponentObsvr(InputComponent& iCmpnt) : 
    i_cmpnt_(iCmpnt) {}




bool ComponentObsvr::eventHandler(sf::Event& ev) {
    return (i_cmpnt_.registerInput(ev));
}