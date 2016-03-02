#include "debug.h"
#include "observer.h"

#include "subject.h"

using namespace ppc;

unsigned int BaseObserver::id_counter_ = 0;

BaseObserver::BaseObserver() : id(++id_counter_) {
    next = prev = nullptr;
}


BaseObserver::~BaseObserver() {
    if (watching_ != nullptr) {
        watching_->removeObserver(this);
    }
}


bool BaseObserver::isInUse() {
    return (watching_ != nullptr);
}

Subject* BaseObserver::isWatching() {
    return watching_;
}