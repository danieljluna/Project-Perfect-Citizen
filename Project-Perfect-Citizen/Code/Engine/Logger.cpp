#include "Logger.h"

using namespace ppc;

std::map<std::string, LoggerParcel> Logger::parcelMap;

std::map<std::string, sf::Time> Logger::timerStarts;

sf::Clock Logger::clock;




/////////////////////////////////////////////////////////////////////
// Storing Times
/////////////////////////////////////////////////////////////////////

void Logger::startTimer(const std::string& label) {
    auto it = timerStarts.find(label);
    //If we aren't waiting on this timer already:
    if (it == timerStarts.end()) {
        //Save the current time for an endTimer call later
        timerStarts.emplace(label, clock.getElapsedTime());
    }
}



void Logger::restartTimer(const std::string& label) {
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



bool Logger::endTimer(const std::string& label, bool aggregate) {
    bool result = false;

    auto it_tStarts = timerStarts.find(label);
    //If the timer we are trying to end has been started:
    if (it_tStarts != timerStarts.end()) {
        //Get Elapsed Time and delete old label
        sf::Time dt = clock.getElapsedTime() - it_tStarts->second;
        timerStarts.erase(it_tStarts);

        //Find the label in the timerMap
        auto it_pMap = parcelMap.find(label);

        //If the label doesn't exist:
        if (it_pMap == parcelMap.end()) {
            LoggerParcel lp;
            lp.type = LoggerParcel::Timer;
            lp.time = dt;
            parcelMap.emplace(label, lp); //Add the time to the map
        } else {
            //If we are aggregating the time:
            if (aggregate) {                
                it_pMap->second.time += dt;       //Aggegate time
            } else {
                it_pMap->second.time = dt;        //Override time
            }
        }

        //We succeeded in ending a timer
        result = true;
    }

    return result;
}



void Logger::eraseLabel(const std::string& label) {
    auto it = parcelMap.find(label);
    //If we even have a time for this label:
    if (it != parcelMap.end()) {
        if (it->second.type == LoggerParcel::Timer) {
            //Remove that label
            parcelMap.erase(label);
        }
    }
}


