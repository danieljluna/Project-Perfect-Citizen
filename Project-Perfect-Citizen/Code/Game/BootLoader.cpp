//
//  BootLoader.cpp
//  Project-Perfect-Citizen
//
//  Created by Michael Lowe on 2/28/16.
//  Copyright © 2016 Hyperfocus Games. All rights reserved.
//
#include "../Engine/debug.h"
#include "BootLoader.hpp"
#include <string>
#include <algorithm>
#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <math.h>

using namespace ppc;

//////////////////////////////////////////////////////////
///// Random string function use for random file paths
/////////////////////////////////////////////////////////
std::string ppc::getRandomString(int stringLength) {
    std::string text = "";
    std::string possible = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    for (int i = 0; i < stringLength; ++i) {
        text += possible[int(floor(rand() % possible.length()))];
    }
    return text;
}


//////////////////////////////////////////////////////////
///// Boot loading animation function.
/////////////////////////////////////////////////////////

std::string ppc::bootLoad(int step, std::string renderString) {
    if (step == 200) {
        renderString += " PCOS(C) , UNMOS. UNAUTHORIZED USE OF THIS TERMINAL CAN RESULT IN PENALTY BY DEATH. \n";
    } else if (step == 500) {
        renderString += "  Beginning File System Initialization \n";
    } else if (step == 1000) {
        renderString +="   Loaded: /PCOS/init/config/system \n";
    } else if (step == 3000) {
        renderString +="   Loaded: /PCOS/init/config//ntoskrn1.exe \n";
    } else if (step == 4000) {
        for (int i = 0; i < 20; ++i) {
            renderString += "   Loaded: /PCOS/init/config//DRIVERSs";
            renderString += "//" + getRandomString((rand() % 12)+ 4) + "\n";
        }
    } else if (step == 4200) {
        for (int i = 0; i < 20; ++i) {
            renderString += "   Loaded: /PCOS/init/config//ntwkprtl";
            renderString += "//" + getRandomString((rand() % 12)+ 4) + "\n";
        }
    } else if (step == 5000) {
        for (int i = 0; i < 20; ++i) {
            renderString += "   Loaded: /PCOS/init/config//drivers";
            renderString += "//" + getRandomString((rand() % 12)+ 4) + "\n";
        }
    } else if (step == 5200) {
        renderString = "   > Receiving packet from [UNKNOWN-ADDRESS] \n";
    } else if (step == 5500) {
        renderString += "   > Packet Received \n";
    } else if (step == 6100) {
        renderString +="   > Executing";
    }
    return renderString;
    
}