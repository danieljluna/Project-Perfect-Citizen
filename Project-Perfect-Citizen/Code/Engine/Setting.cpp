#include "Setting.h"
#include <iostream>
#include <string>

using namespace ppc;

std::map<std::string, Setting::IniTags> Setting::iniGroupMap = {
    { "ResolutionWidth",    Setting::ResolutionX },
    { "ResolutionX",        Setting::ResolutionX },
    { "ResolutionHeight",   Setting::ResolutionY },
    { "ResolutionWidth",    Setting::ResolutionX }
};


std::istream& ppc::operator>>(std::istream& in, Setting& setting) {
    std::string word;
    Setting::IniTags tag;

    //Loop over groupings
    while (in) {
        in >> word;

        //If we are not at a new tag
        if (word.front() != '[') {

            //Get info from sub item as appropriate
            switch (Setting::iniGroupMap.find(word)->second) {
            case Setting::ResolutionX:
                in >> setting.resolution.x;
                break;
            case Setting::ResolutionY:
                in >> setting.resolution.x;
                break;
            default:
                break;
            }

        } else {
            break;
        }

    }

    return in;
}

std::ostream& ppc::operator<<(std::ostream& out, const Setting& setting) {
    return out;
}
