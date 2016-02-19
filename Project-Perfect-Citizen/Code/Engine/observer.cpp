#include "observer.h"
#include "../Engine/debug.h"
using namespace ppc;

unsigned int BaseObserver::id_counter_ = 0;

BaseObserver::BaseObserver() : id(++id_counter_) {
    next = prev = nullptr;
}


BaseObserver::~BaseObserver() {}


bool BaseObserver::isInUse() {
    return inUse;
}