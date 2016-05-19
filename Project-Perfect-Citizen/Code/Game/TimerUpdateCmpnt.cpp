#include "TimerUpdateCmpnt.h"

using namespace ppc;

///////////////////////////////////////////////////////////////////////
// Constructors and Destructor
///////////////////////////////////////////////////////////////////////

TimerUpdateCmpnt::TimerUpdateCmpnt() {

}




TimerUpdateCmpnt::~TimerUpdateCmpnt() {

}

///////////////////////////////////////////////////////////////////////
// Timer Manipulation
///////////////////////////////////////////////////////////////////////

void TimerUpdateCmpnt::playTimer(unsigned int timer) {
    timerVec_.at(timer).isRunning = true;
}




void TimerUpdateCmpnt::pauseTimer(unsigned int timer) {
    timerVec_.at(timer).isRunning = false;
}




void TimerUpdateCmpnt::resetTimer(unsigned int timer, sf::Time newTime) {
    timerVec_.at(timer).timeLeft = newTime;

    //Resets to <= 0 should be paused
    if (newTime.asMicroseconds() <= 0) {
        timerVec_.at(timer).isRunning = false;
    } else {
        timerVec_.at(timer).isRunning = true;
    }
}




void TimerUpdateCmpnt::ffwdTimer(unsigned int index, sf::Time dt) {
    Timer timer = timerVec_.at(index);
    timer.timeLeft += dt;

    //Check if timer just timed out
    if (timer.timeLeft.asMicroseconds() <= 0) {
        activateTimer(index);
    }
}




void TimerUpdateCmpnt::rewindTimer(unsigned int timer, sf::Time dt) {
    ffwdTimer(timer, -1.0f * dt);
}




///////////////////////////////////////////////////////////////////////
// Inherited Interface
///////////////////////////////////////////////////////////////////////

void TimerUpdateCmpnt::update(sf::Time& deltaTime) {
    //Update all timers
    for (Timer& timer : timerVec_) {
        timer.timeLeft -= deltaTime;
    }
}




void TimerUpdateCmpnt::recieveMessage(ppc::Event ev) {

}

