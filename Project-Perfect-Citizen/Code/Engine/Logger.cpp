#include "Logger.h"

#include <time.h>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

#include "debug.h"

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
    std::ifstream in(filename);
    //Vector of strings matching the desired final output
    std::vector<std::string> finalLines;
    //Traces where we are in the ParcelMap
    auto outIt = parcelMap.cbegin();

    while (in) {
        //Save the next line in the file
        std::string line;
        getline(in, line);

        //Parse out the label name
        std::string label;
        size_t labelEnd = line.find(':');
        label = line.substr(0, labelEnd);
        DEBUGF("dl", "Label=" << label);

        //If we're still worried about more parcelMap output
        if (outIt != parcelMap.cend()) {
            //Output all logs before the current label
            while (outIt->first < label) {
                std::string outputLine = outIt->first;
                outputLine += ": ";
                outputLine += (std::string)(outIt->second);
                finalLines.push_back(outputLine);
                ++outIt;
            }

            //Check if we need to append to the current label
            if (outIt->first == label) {
                line += ", ";
                line += (std::string)(outIt->second);
                finalLines.push_back(line);
                ++outIt;
            }
        }

    }   //End while(in)

    in.close();

    //Push remaining output to finalLines
    while (outIt != parcelMap.cend()) {
        std::string outputLine = outIt->first;
        outputLine += ": ";
        outputLine += (std::string)(outIt->second);
        finalLines.push_back(outputLine);
        ++outIt;
    }

    std::ofstream out(filename);
    if (out) {
        size_t i = 0;
        //Output the finalLines vec to the file
        for (size_t i = 0; (out) && (i < finalLines.size()); ++i) {
            out << finalLines.at(i) << std::endl;
        }

        //If out did not fail, we saved all data
        if (out) {
            result = true;
            parcelMap.clear();  //Clear out old data
        }
    }

    out.close();

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





/////////////////////////////////////////////////////////////////////
// Storing Ints
/////////////////////////////////////////////////////////////////////

bool Logger::saveNumber(const std::string& label,
                        const float number) {
    return false;
}



bool Logger::incrementNumber(const std::string& label,
                             const float incrementation) {
    return false;
}



///////////////////////////////////////////////////////////////////////
// Initializer for the ostream
///////////////////////////////////////////////////////////////////////

std::string Logger::generateFileName() {
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


