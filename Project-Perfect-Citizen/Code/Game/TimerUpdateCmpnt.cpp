#include "TimerUpdateCmpnt.h"
#include "../Engine/Entity.h"

#include <algorithm>

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




unsigned int TimerUpdateCmpnt::createTimer(sf::Time time, int evKey) {
    unsigned int result = timerVec_.size();
    
    timerVec_.push_back(Timer());
    timerVec_.back().eventIndex = evKey;
    timerVec_.back().timeLeft = time;

    return result;
}




bool TimerUpdateCmpnt::isValidTimer(unsigned int timer) {
    return (timer < timerVec_.size());
}




///////////////////////////////////////////////////////////////////////
// Event Mapping
///////////////////////////////////////////////////////////////////////

int TimerUpdateCmpnt::mapEvent(ppc::Event ev) {
    int result;

    /*
    auto it = std::find(eventVec_.begin(), eventVec_.end(), ev);
    if (it != eventVec_.end()) {
        result = (it - eventVec_.begin());
    } else {
        result = eventVec_.size();
        eventVec_.push_back(ev);
    }
    */ // This doesn't work since Event has no == op.

    result = eventVec_.size();
    eventVec_.push_back(ev);

    return result;
}




ppc::Event TimerUpdateCmpnt::getMapping(int key) {
    ppc::Event result;
    if (static_cast<unsigned int>(key) < eventVec_.size()) {
        return eventVec_.at(key);
    } else {
        ppc::Event emptyEv;
        emptyEv.type = Event::Count;
        return emptyEv;
    }
}




void TimerUpdateCmpnt::setTimerEvent(unsigned int timer, ppc::Event ev) {
    int key = mapEvent(ev);
    setTimerEvent(timer, key);
}




void TimerUpdateCmpnt::setTimerEvent(unsigned int timer, int key) {
    timerVec_.at(timer).eventIndex = key;
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
    Event ppcEv;

    pauseTimer(timer);

    if (timerVec_.at(timer).eventIndex == -1) {
        //Use Default Event
        ppcEv.type = Event::TimerType;
        ppcEv.timer.timerIndex = timer;
        ppcEv.timer.time = timerVec_.at(timer).timeLeft;
        ppcEv.timer.action = Event::TimerEv::Finished;
    } else {
        ppcEv = eventVec_.at(timerVec_.at(timer).eventIndex);
    }

    onTimer_.sendEvent(ppcEv);
    getEntity()->broadcastMessage(ppcEv);
}
