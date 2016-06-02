#include "Save.h"
#include <string>
#include <fstream>
#include <iomanip>
#include "../ResourceDef.h"
#include "../Engine/debug.h"
#include "../Engine/World.h"

using namespace ppc;

std::map<std::string, Save::IniTags> Save::iniGroupMap = {
    { "DesktopEndings",    Save::DesktopEndings },
    { "CurrDesktop",       Save::CurrDesktop }
};



Save::Save() : extractionCount_(5) {
    loginId_ = "";
    for (unsigned i = 0; i < extractionCount_; ++i) {
        reports_[i] = World::UNPLAYED;
    }
        
}


Save::Save(const Save& other) : extractionCount_(5) {
    loginId_ = other.loginId_;
    for (unsigned i = 0; i < extractionCount_; ++i) {
        reports_[i] = other.reports_[i];
    }
}


Save& Save::operator=(const Save& other) {
    loginId_ = other.loginId_;
    for (unsigned i = 0; i < extractionCount_; ++i) {
        reports_[i] = other.reports_[i];
    }

    return *this;
}


bool Save::importSave(const std::string& login) {
    std::ifstream in(resourcePath() + "Saves/" + login + ".sav");

    if (in.bad()) return false;

    loginId_ = login;

    std::string word;

    //Loop over groupings
    while (in) {
        in >> word;

       
        auto mapIt = Save::iniGroupMap.find(word);
        if (mapIt == Save::iniGroupMap.end()) {
            //Output error
            DEBUGF("wl", "Bad Settings Tag: " << word);

        } else {


            unsigned i = 0;

            //Get info from sub item as appropriate
            switch (mapIt->second) {
            case Save::CurrDesktop:
                in >> currDesktop_;
                break;
            case Save::DesktopEndings:
                in >> word;

                for (auto charIt : word) {
                    if (i >= extractionCount_) {
                        break;
                    }
                    switch (charIt) {
                    case 'A':
                    case '0':
                        reports_[i++] = World::A;
                        break;
                    case 'B':
                    case '1':
                        reports_[i++] = World::B;
                        break;
                    case 'C':
                    case '2':
                        reports_[i++] = World::C;
                        break;
                    case 'D':
                    case '3':
                        reports_[i++] = World::D;
                        break;
                    default:
                        reports_[i++] = World::UNPLAYED;
                        break;
                    }
                }
                break;
            default:
                in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
            }
        }
    }

    return in.good();
}



void Save::exportSave(const std::string& login) {
    loginId_ = login;
    loginId_ = loginId_.substr(loginId_.find_first_not_of(" \t"),
                               loginId_.find_last_not_of(" \t") + 1);
    for (unsigned i = 0; i < loginId_.size(); ++i) {
        loginId_[i] = tolower(loginId_[i]);
    }

    std::ofstream out(resourcePath() + "Saves/" + loginId_ + ".sav");

    out << std::left;

    out << std::setw(25) << "CurrDesktop" << std::setw(0) <<
        currDesktop_ << std::endl;
    out << std::setw(25) << "DesktopEndings" << std::setw(0);
    for (unsigned i = 0; i < extractionCount_; ++i) {
        out << reports_[i];
    }
    out << std::endl;
}

