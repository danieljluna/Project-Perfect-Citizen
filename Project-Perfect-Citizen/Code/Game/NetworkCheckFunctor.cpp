#include "NetworkCheckFunctor.h"
#include "../Engine/Network.h"
#include "../Engine/subject.h"

using namespace ppc;


bool NetworkCheckFunctor::operator()() {
    bool CenterEquality = net1_->checkCenterEquality(*net2_); //*network needs to be OTHER network
    float EdgeEquality = net1_->checkEdgeEquality(*net2_);    //for both of these
    if (CenterEquality) {
        std::cout << "Center Selection Correct!" << std::endl;
        if (EdgeEquality > .9) {
            std::cout << "You win!" << std::endl;
            onWin_.sendEvent(sf::Event());
            return true;
        }
    }

    return false;
}