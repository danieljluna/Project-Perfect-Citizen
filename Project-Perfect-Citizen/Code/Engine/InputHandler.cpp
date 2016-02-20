#include "InputHandler.h"

using namespace ppc;

InputHandler::InputHandler() {}




InputHandler::~InputHandler() {}




void InputHandler::addHandle(sf::Event::EventType type) {
    inputMap.emplace(type, Subject{});
}




void InputHandler::registerEvent(sf::Event& ev) {
    auto it = inputMap.find(ev.type);
    if (it != inputMap.end()) {
        it->second.sendEvent(ev);
    }
}




bool InputHandler::addObserver(sf::Event::EventType type, 
                               BaseObserver* obsvr,
                               bool forceCreation) {
    bool result = true;
    
    auto it = inputMap.find(type);
    if (it != inputMap.end()) {
        it->second.addObserver(obsvr);
    } else if (forceCreation) {
        auto emplaceRet = inputMap.emplace(type, Subject{});
        if (emplaceRet.second) {
            emplaceRet.first->second.addObserver(obsvr);
        }
        result = emplaceRet.second;
    }

    return result;
}




void InputHandler::removeObserver(sf::Event::EventType type,
                                  BaseObserver* obsvr) {
    auto it = inputMap.find(type);

    if (it != inputMap.end()) {
        it->second.removeObserver(obsvr);
    }
}




void InputHandler::removeObserver(sf::Event::EventType type,
                                  unsigned int id,
                                  unsigned int range) {
    auto it = inputMap.find(type);

    if (it != inputMap.end()) {
        it->second.removeObserver(id, range);
    }
}
