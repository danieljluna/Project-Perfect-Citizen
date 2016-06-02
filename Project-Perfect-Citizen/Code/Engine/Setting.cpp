#include "Setting.h"
#include <iostream>
#include <iomanip>
#include <string>
#include "debug.h"

using namespace ppc;

std::map<std::string, Setting::IniTags> Setting::iniGroupMap = {
    { "ResolutionWidth",    Setting::ResolutionX },
    { "ResolutionX",        Setting::ResolutionX },
    { "ResolutionHeight",   Setting::ResolutionY },
    { "ResolutionWidth",    Setting::ResolutionX },
    { "Fullscreen",         Setting::Fullscreen  }
};


std::istream& ppc::operator>>(std::istream& in, Setting& setting) {
    std::string word;

    //Loop over groupings
    while (in) {
        in >> word;

        //If we are not at a new tag
        if (word.front() != '[') {

            auto mapIt = Setting::iniGroupMap.find(word);
            if (mapIt == Setting::iniGroupMap.end()) {
                //Output error
                DEBUGF("wl", "Bad Settings Tag: " << word);

            } else {

                //Get info from sub item as appropriate
                switch (mapIt->second) {
                case Setting::ResolutionX:
                    in >> setting.resolution.x;
                    break;
                case Setting::ResolutionY:
                    in >> setting.resolution.y;
                    break;
                case Setting::Fullscreen:
                    in >> setting.fullscreen;
                    break;
                default:
                    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    break;
                }
            }

        } else {
            break;
        }

    }

    return in;
}

std::ostream& ppc::operator<<(std::ostream& out, const Setting& setting) {
    out << std::left;
    out << std::setw(25) << "ResolutionWidth" <<
            std::setw(0) << setting.resolution.x << std::endl;
    out << std::setw(25) << "ResolutionHeight" <<
        std::setw(0) << setting.resolution.y << std::endl;

    return out;
}
