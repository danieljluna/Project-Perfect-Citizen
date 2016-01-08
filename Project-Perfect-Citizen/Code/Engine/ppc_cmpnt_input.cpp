#include "ppc_cmpnt_input.h"

using namespace ppc;

size_t InputComponent::InputArraySize = 0;

//InputComponent* InputArray[2] = { nullptr, nullptr };

InputComponent::InputComponent(Entity* entityPtr) {
    entity = entityPtr;
    //InputArray[InputArraySize] = this;
    ++InputArraySize;
};
