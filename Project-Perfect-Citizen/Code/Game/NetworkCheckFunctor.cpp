#include "NetworkCheckFunctor.h"
#include "../Engine/Network.h"
#include "../Engine/subject.h"
#include "../Engine/World.h"
#include "../Engine/desktop.h"
#include "../Engine/Window.h"

#include "../Engine/WindowInterface.h"

#include "createWindow.h"

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
		else {
			//respond to center equal
		}
    }
	WindowInterface* feedback = new ppc::Window(300, 300);
	Desktop& desk = World::getCurrDesktop();
	spawnErrorMessage(feedback, feedback->getInputHandler(), desk.getButtonSheet(), 400.f, 200.f, "Check Center", "Pipeline Feedback");
	desk.addWindow(feedback);
	//respond to center different
    return false;
}




bool ppc::runSubmitCheck(NetworkCheckFunctor* ncf, Event ev) {
    if ((*ncf)()) { ppc::World::quitDesktop(); };

    return true;
}

