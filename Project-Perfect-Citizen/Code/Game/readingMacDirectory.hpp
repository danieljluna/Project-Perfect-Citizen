//
//  readingMacDirectory.hpp
//  Project-Perfect-Citizen
//
//  Created by Brandon Gomez on 4/22/16.
//  Copyright © 2016 Hyperfocus Games. All rights reserved.
//

#ifndef readingMacDirectory_hpp
#define readingMacDirectory_hpp

#include <stdio.h>
#include <string>
#include <iostream>

class readingMacDirectory {
    
public:
    std::string getDirectory(std::string s){
        std::string delimiter = "/";
        
        size_t pos = 0;
        std::string token;
        while ((pos = s.find(delimiter)) != std::string::npos) {
            token = s.substr(0, pos);
            //std::cout << token << std::endl;
            s.erase(0, pos + delimiter.length());
        }
        //std::cout << s << std::endl;
        return s;
    }
};

#endif /* readingMacDirectory_hpp */
