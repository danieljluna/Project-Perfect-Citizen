#pragma once

#include "observer.h"

namespace ppc {

class SubjectObsvr : public BaseObserver {
public:

    SubjectObsvr() = delete;

    /// @brief Default Constructor
    SubjectObsvr(Subject& subject);

    ///////////////////////////////////////////////////////////////////
    ///@brief Virtaul eventHandler
    ///@details This is the function that will be called when an 
    /// Observer is notified of an event of interest.
    ///@param event The event this Observer was notified of.
    ///@return Denotes whether this observer propogates the event.
    ///////////////////////////////////////////////////////////////////
    bool eventHandler(Event ev) override;


private:

    Subject* subject_;

};


};
