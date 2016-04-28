#pragma once
#include "../Engine/subject.h"

namespace ppc {

    class Network;

class NetworkCheckFunctor {
public:

    NetworkCheckFunctor(Network& net1, Network& net2) {
        net1_ = &net1;
        net2_ = &net2;
    };


    bool operator() ();

    Subject& onWin () { return onWin_; };


private:

    Network* net1_; 
    Network* net2_;

    Subject onWin_;


};


bool runSubmitCheck(NetworkCheckFunctor* ncf, Event ev);


};


