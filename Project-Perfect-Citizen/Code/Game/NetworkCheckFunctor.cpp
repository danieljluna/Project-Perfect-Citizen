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
        if ((EdgeEquality > .8  && World::getCurrDesktopEnum() != World::DE0A) || EdgeEquality == 1 ) {
            //std::cout << "You win!" << std::endl;
            sf::Event ev;
            ev.type = sf::Event::Count;
            onWin_.sendEvent(ev);
            return true;
        }
		else {
			//respond to center equal
			WindowInterface* feedback = new ppc::Window(300, 120, sf::Color(170, 170, 170));
			Desktop& desk = World::getCurrDesktop();
			std::string message = "Your target seems reasonable, but I don't think you have enough\n";
			message +=	          "     supporting evidence.  Recheck your connections! - CT";
			spawnErrorMessage(feedback, feedback->getInputHandler(), desk.getButtonSheet(), 300.f, 300.f,
				message, "Pipeline Feedback");
			desk.addWindow(feedback);
			return false;
		}
    }
	if (net2_->getCenter < net2_->size()) {
		WindowInterface* feedback = new ppc::Window(300, 150, sf::Color(170, 170, 170));
		Desktop& desk = World::getCurrDesktop();
		std::string message = "I think there is a target more suspicious than the\n";
		message += "  one you chose.  See if you can find them! - CT";
		spawnErrorMessage(feedback, feedback->getInputHandler(), desk.getButtonSheet(), 300.f, 300.f,
			message, "Pipeline Feedback");
		desk.addWindow(feedback);
	}
	else {
		WindowInterface* feedback = new ppc::Window(300, 150, sf::Color(170, 170, 170));
		Desktop& desk = World::getCurrDesktop();
		std::string message = "You must choose a center before submitting";
		spawnErrorMessage(feedback, feedback->getInputHandler(), desk.getButtonSheet(), 300.f, 300.f,
			message, "Pipeline Error");
		desk.addWindow(feedback);
	}
	//respond to center different
    return false;
}




bool ppc::runSubmitCheck(NetworkCheckFunctor* ncf, Event ev) {
    if ((*ncf)()) { ppc::World::quitDesktop(); };

    return true;
}

