#include "inputComponent.h"

#include "InputHandler.h"

using namespace ppc;

InputComponent::InputComponent(size_t observerCount) {
    observerArray_ = new ComponentObsvr* [observerCount];
    for (size_t index = 0; index < observerCount_; ++index) {
        observerArray_[index] = new ComponentObsvr(*this);
    }
    observerCount_ = observerCount;
};




InputComponent::~InputComponent() {
    delete[] observerArray_;
}




ComponentObsvr* InputComponent::getObserver(size_t index) {
    if (index < observerCount_) {
        return observerArray_[index];
    } else { return nullptr; }
}




bool InputComponent::watch(Subject& subject) {
    return false;
}




bool InputComponent::watch(InputHandler& iHandler, 
                           sf::Event::EventType type) {
    return false;
}




bool InputComponent::ignore(Subject& subject) {
    return false;
}




bool InputComponent::ignore(InputHandler& iHandler,
                            sf::Event::EventType type) {
    return false;
}
