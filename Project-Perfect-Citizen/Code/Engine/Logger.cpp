#include "Logger.h"

#include <time.h>
#include <string>
#include <fstream>
#include <iostream>

using namespace ppc;

std::map<std::string, LoggerParcel> Logger::parcelMap;

std::map<std::string, sf::Time> Logger::timerStarts;

sf::Clock Logger::clock;



///////////////////////////////////////////////////////////////////////
// Parcel Manipulation
///////////////////////////////////////////////////////////////////////

LoggerParcel Logger::getParcel(const std::string& label) {
    LoggerParcel result;

    auto it = parcelMap.find(label);
    //If we even have a parcel for this label:
    if (it != parcelMap.end()) {
        //Get that label
        result = it->second;
    }

    return result;
}



bool Logger::scaleParcel(const std::string& label,
                         const float scale) {
    bool result = false;
    auto it = parcelMap.find(label);

    //If we even have a parcel for this label:
    if (it != parcelMap.end()) {
        result = true;

        //Apply scaling factor
        switch (it->second.type) {
        case LoggerParcel::Timer:
            it->second.time *= scale;
            break;
        case LoggerParcel::Number:
            it->second.number *= scale;
            break;
        }
    }

    return result;
}




bool Logger::exportParcels() {
    bool result = false;

    std::string filename(generateFileName());

    std::ofstream out(filename);
    std::ifstream in(filename);

    if (in && out) {
        result = true;

        std::string label;
        in >> label;


        while (in) {
            in >> label;    //Keeps from infinite loop
        }

        //Introduce Export to file (tellp) (seekp)
    }

    return result;
}




bool Logger::eraseParcel(const std::string& label) {
    bool result = false;
    
    auto it = parcelMap.find(label);
    //If we even have a parcel for this label:
    if (it != parcelMap.end()) {
        result = true;

        //Remove that label
        parcelMap.erase(label);
    }

    return result;
}




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





///////////////////////////////////////////////////////////////////////
// Initializer for the ostream
///////////////////////////////////////////////////////////////////////

std::string& Logger::generateFileName() {
    /*
    time_t rawTime;
    struct tm* timeInfo;
    char buffer[80];

    time(&rawTime);

    timeInfo = localtime(&rawTime);

    strftime(buffer, 80, "ppc_%d-%b-%y_%H-%M.log", timeInfo);
    std::string result(buffer);
    */

    std::string result("PPC_TESTING.LOG");

    return result;
}


