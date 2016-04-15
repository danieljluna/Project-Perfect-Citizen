#pragma once

#include <SFML/System/Time.hpp>
#include <string>

namespace ppc {


///////////////////////////////////////////////////////////////////////
/// @brief A struct that holds a union of possible log values.
///////////////////////////////////////////////////////////////////////
struct LogParcel {

  /////////////////////////////////////////////////////////////////////
  // Type Enumeration
  /////////////////////////////////////////////////////////////////////

    enum LogType {
        Float = 0,
        Int,
        Time,
        Count
    };


  /////////////////////////////////////////////////////////////////////
  // Structs
  /////////////////////////////////////////////////////////////////////

    struct floatParcel {
        float average;
        float max;
        float min;
    };

    struct intParcel {
        int average;
        int max;
        int min;
    };

    struct timeParcel {
        sf::Time average;
        sf::Time max;
        sf::Time min;
    };


  /////////////////////////////////////////////////////////////////////
  // Data
  /////////////////////////////////////////////////////////////////////

    //Stores the label used to map this data to a variable in excel
    std::string label;

    //Determines the portion of the union in use
    LogType type = Count;

    //A union of all loggable data types
    union {
        floatParcel floatData;
        intParcel intData;
        timeParcel timeData;
    };


};


};
