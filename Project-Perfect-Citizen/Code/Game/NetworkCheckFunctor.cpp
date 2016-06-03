#include "NetworkCheckFunctor.h"
#include "../Engine/Network.h"
#include "../Engine/subject.h"
#include "../Engine/World.h"

#include "../Engine/WindowInterface.h"

using namespace ppc;


bool NetworkCheckFunctor::operator()() {
    bool CenterEquality = net1_->checkCenterEquality(*net2_); //*network needs to be OTHER network
    float EdgeEquality = net1_->checkEdgeEquality(*net2_);    //for both of these
    if (CenterEquality) {
        //std::cout << "Center Selection Correct!" << std::endl;
        if (EdgeEquality > .7) {
            //std::cout << "You win!" << std::endl;
            sf::Event ev;
            ev.type = sf::Event::Count;
            onWin_.sendEvent(ev);
            return true;
        }
    }

    return false;
}




bool ppc::runSubmitCheck(NetworkCheckFunctor* ncf, Event ev) {
    if ((*ncf)()) { ppc::World::quitDesktop(); };

    return true;
}

