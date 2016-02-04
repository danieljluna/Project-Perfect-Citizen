#include "observer.h"

using namespace ppc;

unsigned int BaseObserver::id_counter_ = 0;

BaseObserver::BaseObserver() : id(++id_counter_) {
    next = prev = nullptr;
}


BaseObserver::~BaseObserver() {}


