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
// Event Mapping
///////////////////////////////////////////////////////////////////////

int TimerUpdateCmpnt::mapEvent(ppc::Event ev) {
    eventMap_.in
}




ppc::Event TimerUpdateCmpnt::getMapping(int key) {
    auto it = eventMap_.find(key);
    ppc::Event result;
    if (it != eventMap_.end()) {
        return it->second;
    } else {
        ppc::Event emptyEv;
        emptyEv.type = Event::Count;
        return emptyEv;
    }
}




void TimerUpdateCmpnt::setTimerEvent(unsigned int timer, ppc::Event ev) {

}




void TimerUpdateCmpnt::setTimerEvent(unsigned int timer, int key) {

}




///////////////////////////////////////////////////////////////////////
// Inherited Interface
///////////////////////////////////////////////////////////////////////

void TimerUpdateCmpnt::update(sf::Time& deltaTime) {
    //Update all timers
    for (unsigned int i = 0; i < timerVec_.size(); ++i) {
        Timer& timer = timerVec_.at(i);
        //If timer is running
        if (timer.isRunning) {
            timer.timeLeft -= deltaTime;
            if (timer.timeLeft.asMicroseconds() <= 0) {
                activateTimer(i);
            }
        }
    }
}




void TimerUpdateCmpnt::recieveMessage(ppc::Event ev) {
    if (ev.type == ev.TimerType) {
        switch (ev.timer.action) {
        case ev.timer.Reset:
            resetTimer(ev.timer.timerIndex, ev.timer.time);
            break;
        case ev.timer.FastForward:
            ffwdTimer(ev.timer.timerIndex, ev.timer.time);
            break;
        case ev.timer.Play:
            playTimer(ev.timer.timerIndex);
            break;
        case ev.timer.Pause:
            pauseTimer(ev.timer.timerIndex);
            break;
        case ev.timer.Rewind:
            rewindTimer(ev.timer.timerIndex, ev.timer.time);
            break;
        case ev.timer.Finished:
            break;
        }
    }
}




///////////////////////////////////////////////////////////////////////
// Private Functionality
///////////////////////////////////////////////////////////////////////

void TimerUpdateCmpnt::activateTimer(unsigned int timer) {

}
