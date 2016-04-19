#pragma once

#include <SFML/System/Time.hpp>

namespace ppc {


///////////////////////////////////////////////////////////////////////
/// @brief Defines a parcel used for logging.
///////////////////////////////////////////////////////////////////////
struct LoggerParcel {

    LoggerParcel() { type = TypeCount; };

    enum ParcelType {
        Timer,
        Number,
        TypeCount
    };

    ParcelType type;

    union {
        float number;
        sf::Time time;
    };


};


};
