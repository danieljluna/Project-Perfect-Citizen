//
//  playerLocator.cpp
//  Project-Perfect-Citizen
//
//  Created by Michael Lowe on 5/31/16.
//  Copyright © 2016 Hyperfocus Games. All rights reserved.
//

#include "playerLocator.hpp"


PlayerLocator::PlayerLocator() {
    fullLocation = generateLocation();
    reader.parse(fullLocation, value);
    ip_ = value["ip"].asString();
    loc_ = value["loc"].asString();
    city_ = value["city"].asString();
    postal_ = value["postal"].asString();
    region_ = value["region"].asString();
    country_ = value["country"].asString();
}

PlayerLocator::~PlayerLocator() {
    
}

std::string PlayerLocator::generateLocation() {
    #ifdef WINDOWS_MARKER
    
    #else
    FILE *pipe;
    std::string tmp;
    
    char str[1000];
    
    pipe = popen ( "curl ipinfo.io", "r" );
    
    while (fgets ( str, 1000, pipe )) {
       tmp += str;
    }
    pclose (pipe);
    #endif
    return tmp;
}