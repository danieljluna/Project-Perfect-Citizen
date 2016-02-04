#include "inputComponent.h"

#include "InputHandler.h"

using namespace ppc;

InputComponent::InputComponent(size_t observerCount) {
    observerArray_ = new ComponentObsvr*[observerCount];
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

}




bool InputComponent::watch(InputHandler& iHandler, 
                           sf::Event::EventType type) {

}




bool InputComponent::ignore(Subject& subject) {

}




bool InputComponent::ignore(InputHandler& iHandler,
                            sf::Event::EventType type) {

}
