#include "SubjectObsvr.h"
#include "event.h"
#include "subject.h"

using namespace ppc;

SubjectObsvr::SubjectObsvr(Subject& subject) {
    subject_ = &subject;
}



bool SubjectObsvr::eventHandler(Event ev) {
    if (subject_ != nullptr) {
        subject_->sendEvent(ev);
    }
    
    return true;
}
