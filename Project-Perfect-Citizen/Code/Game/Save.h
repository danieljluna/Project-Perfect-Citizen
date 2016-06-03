#pragma once
#include <map>
#include <string>

namespace ppc {

class Save {
public:

    Save();

    Save(const Save& other);

    std::string getLoginId() const { return loginId_; };

    bool importSave(const std::string& login);

    void exportSave(const std::string& login);

    Save& operator=(const Save& other);
    
	unsigned int getReport(unsigned int);

private:

    const unsigned extractionCount_;

    std::string loginId_;
    //Array for each desktop ending. Match ExtractionCount
    unsigned int reports_[5];
    unsigned int currDesktop_ = 0;

    enum IniTags {
        DesktopEndings = 0,
        CurrDesktop,
        TagCount
    };

    static std::map<std::string, IniTags> iniGroupMap;


};


};