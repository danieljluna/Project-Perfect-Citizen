#include "inputComponent.h"

#include "InputHandler.h"

using namespace ppc;

InputComponent::InputComponent(size_t observerCount) {

    observerArray_ = new BaseObserver* [observerCount];
    for (size_t index = 0; index < observerCount; ++index) {
        observerArray_[index] = new ComponentObsvr(*this);
    }
    observerCount_ = observerCount;
};




InputComponent::~InputComponent() {
    for (size_t i = 0; i < observerCount_; ++i) {
        if (observerArray_[i] != nullptr) {
            delete observerArray_[i];
        }
    }
    delete[] observerArray_;
}




BaseObserver* InputComponent::getObserver(size_t index) {
    if (index < observerCount_) {
        return observerArray_[index];
    } else { return nullptr; }
}




bool InputComponent::watch(Subject& subject) {
    size_t i = findNextObserver();

    if (i < observerCount_) {
        subject.addObserver(observerArray_[i]);
        return true;
    } else {
        return false;
    }
}




bool InputComponent::watch(InputHandler& iHandler, 
                           sf::Event::EventType type) {
    size_t i = findNextObserver();

    if (i < observerCount_) {
        iHandler.addObserver(type, observerArray_[i], true);
        return true;
    } else {
        return false;
    }
}




void InputComponent::ignore(Subject& subject) {
    subject.removeObserver(observerArray_[0]->id, observerCount_);
}




void InputComponent::ignore(InputHandler& iHandler,
                            sf::Event::EventType type) {
    iHandler.removeObserver(type, observerArray_[0]->id, observerCount_);
}




//Finds the next available Observer for assignemnt
size_t InputComponent::findNextObserver() {
    size_t i = 0;
    while ((i < observerCount_) && (observerArray_[i]->isInUse())) {
        ++i;
    }

    return i;
}
