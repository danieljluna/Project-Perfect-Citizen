//
//  nameGeneration.cpp
//  Project-Perfect-Citizen
//
//  Created by Brandon Gomez on 4/8/16.
//  Copyright © 2016 Hyperfocus Games. All rights reserved.
//

#include "../ResourceDef.h"

#include "nameGeneration.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <time.h>

using namespace ppc;

void nameGeneration::readFiles() {
    std::string firstNameFile = resourcePath() + "first.txt";
    std::string lastNameFile = resourcePath() + "last.txt";
    std::ifstream firstFile(firstNameFile);
    std::ifstream lastFile(lastNameFile);
    std::string line;
    int nlines = 0 ;
    int max = 0;
    int randomLine = 0;
    while(getline(firstFile, line)){
        if(nlines == 0){
            max = stoi(line);
            srand (static_cast<unsigned int>(time(NULL)));
            randomLine = rand() % max;
        }
        if(++nlines == randomLine) {
            setFirst(line);
            firstFile.clear();
            break;
        }
    }
    nlines = 0 ;
    max = 0;
    randomLine = 0;
    while(getline(lastFile, line)){
        if(nlines == 0){
            max = stoi(line);
            srand (static_cast<unsigned int>(time(NULL)));
            randomLine = rand() % max;
        }
        if(++nlines == randomLine) {
            setLast(line);
            lastFile.clear();
            break;
        }
    }
    setFull();
}