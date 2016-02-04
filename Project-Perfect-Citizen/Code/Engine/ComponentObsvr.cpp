#include "ComponentObsvr.h"
#include "inputComponent.h"

using namespace ppc;

ComponentObsvr::ComponentObsvr(InputComponent& iCmpnt) : 
    i_cmpnt_(iCmpnt) {}




void ComponentObsvr::eventHandler(sf::Event& ev) {
    i_cmpnt_.registerInput(ev);
}