#include "inputComponent.h"

using namespace ppc;

std::vector<InputComponent*> InputComponent::inputVector = {};



InputComponent::InputComponent() {
    id = inputVector.size();
    inputVector.push_back(this);
}




InputComponent::~InputComponent() {
    for (size_t i = id + 1; i < inputVector.size(); ++i) {
        --(inputVector[i]->id);
    }
    inputVector.erase(inputVector.begin() + id);
}

