#include "Logger.h"

using namespace ppc;

std::map<std::string, sf::Time> Logger::timeMap;

std::map<std::string, sf::Time> Logger::timerStarts;

sf::Clock Logger::clock;




/////////////////////////////////////////////////////////////////////
// Storing Times
/////////////////////////////////////////////////////////////////////

void Logger::startTimer(std::string label) {
    auto it = timerStarts.find(label);
    //If we aren't waiting on this timer already:
    if (it == timerStarts.end()) {
        //Save the current time for an endTimer call later
        timerStarts.emplace(label, clock.getElapsedTime());
    }
}



void Logger::restartTimer(std::string label) {
    auto it = timerStarts.find(label);
    //If we are in fact waiting on this timer:
    if (it != timerStarts.end()) {
        //Reset that Timer's start time
        it->second = clock.getElapsedTime();
    } else {
        //Save the current time for an endTimer call later
        timerStarts.emplace(label, clock.getElapsedTime());
    }
}



bool Logger::endTimer(std::string label, bool aggregate) {
    bool result = false;

    auto it = timerStarts.find(label);
    //If the timer we are trying to end has been started:
    if (it != timerStarts.end()) {
        //Get Elapsed Time and delete old label
        sf::Time dt = clock.getElapsedTime() - it->second;
        timerStarts.erase(it);

        //Find the label in the timerMap
        it = timeMap.find(label);

        //If the label doesn't exist:
        if (it == timeMap.end()) {
            timeMap.emplace(label, dt); //Add the time to the map
        } else {
            //If we are aggregating the time:
            if (aggregate) {                
                it->second += dt;       //Aggegate time
            } else {
                it->second = dt;        //Override time
            }
        }

        //We succeeded in ending a timer
        result = true;
    }

    return result;
}



void Logger::clearTime(std::string label) {
    auto it = timeMap.find(label);
    //If we even have a time for this label:
    if (it != timeMap.end()) {
        //Remove that label
        timeMap.erase(label);
    }
}


