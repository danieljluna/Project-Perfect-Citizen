#pragma once

#include <SFML/System/Time.hpp>
#include <string>

namespace ppc {


///////////////////////////////////////////////////////////////////////
/// @brief Defines a parcel used for logging.
///////////////////////////////////////////////////////////////////////
struct LoggerParcel {

    LoggerParcel() { type = TypeCount; };

    explicit operator std::string() const;

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
