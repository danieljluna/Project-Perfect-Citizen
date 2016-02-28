//
//  BootLoader.hpp
//  Project-Perfect-Citizen
//
//  Created by Michael Lowe on 2/28/16.
//  Copyright © 2016 Hyperfocus Games. All rights reserved.
//

#ifndef BootLoader_hpp
#define BootLoader_hpp

#include <stdio.h>
#include <string>


std::string getRandomString(int stringLength);
std::string bootLoad(int step, std::string renderString);

#endif /* BootLoader_hpp */
