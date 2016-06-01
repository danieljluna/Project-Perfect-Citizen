//  playerLocator.hpp
//  Project-Perfect-Citizen
//  Created by Michael Lowe on 5/31/16.
//  Copyright © 2016 BadCop Studios. All rights reserved.
//

#pragma once
#include "json.h"

class PlayerLocator {
        
    private:
        
        Json::Reader reader;
        Json::Value value;
        std::string fullLocation;
        // Player's IP Address
        std::string ip_;
        // Player's Lat/Long
        std::string loc_;
        std::string lat_;
        std::string long_;
        // Player's City
        std::string city_;
        //Players Zip
        std::string postal_;
        // Player's Region (State)
        std::string region_;
        // Player's Country
        std::string country_;

    public:
        PlayerLocator();
        ~PlayerLocator();
        std::string generateLocation();
        std::string getIp() const {return ip_;}
        std::string getLoc() const {return loc_;}
        std::string getLat() const {return lat_;}
        std::string getLong() const {return long_;}
        std::string getCity() const {return city_;}
        std::string getPostal() const {return postal_;}
        std::string getRegion() const {return region_;}
        std::string getCountry() const {return country_;}
};

