//
//  desktopExtractionComponent.cpp
//  Project-Perfect-Citizen
//
//  Created by Brandon Gomez on 2/12/16.
//  Copyright © 2016 Hyperfocus Games. All rights reserved.
//

//Used to get XCODE working/////////////////////////////////

#ifdef WINDOWS_MARKER
#define resourcePath() std::string("Resources/")
#else
#include "ResourcePath.hpp"
#endif

///////////////////////////////////////////////////////////

#include "../Engine/debug.h"
#include "desktopExtractionComponent.hpp"
#include "../Library/json/json.h"
#include "../Game/TreeCommands.h"
#include <iostream>
#include <fstream>

using namespace ppc;

desktopExtractionComponent::desktopExtractionComponent(NodeState ft) : fileTree_(ft){
    
}

Json::Value desktopExtractionComponent::parseDesktopAsJson(std::string file, std::string obj) {
    Json::Reader reader;
    Json::Value value;
    std::ifstream doc(resourcePath() + file, std::ifstream::binary);
    reader.parse(doc, value);
    parseForFileTree(value, obj);
    return value;
}

void desktopExtractionComponent::parseForFileTree(Json::Value value, std::string folder){
    Json::Value directoryObj = value[folder];
    std::vector<std::string> objNames = directoryObj.getMemberNames();
    for (unsigned int i = 0; i < directoryObj.size(); i++){
        auto contentObj = directoryObj[objNames[i]];
        std::string objName = objNames[i];
        // name of file/folder
        // std::cout << objName << std::endl;
        if(contentObj.size() > 0){
            std::vector<std::string> CMD;
            std::string mk_dir_cmd = "mkdir";
            std::string directory_name = objName;
            
            std::string directory_name_copy = objName;
            std::string password;
            std::string hint;
            std::string delimiter = " ";
            size_t pos = 0;
            std::string token;
            int count = 0;
            while ((pos = directory_name_copy.find(delimiter)) != std::string::npos) {
                token = directory_name_copy.substr(0, pos);
                if(count == 0){
                    directory_name = token;
                }
                if(count == 1){
                    password = token;
                }
                else{
                    hint = token;
                    fileTree_.getCwd()->setPassword(password, hint);
                }
                std::cout << token << std::endl;
                directory_name_copy.erase(0, pos + delimiter.length());
                count++;
            }
            CMD.push_back(mk_dir_cmd);
            CMD.push_back(directory_name);
            commandFn executeCommand = findFunction(mk_dir_cmd);
            executeCommand(fileTree_, CMD);
            std::string cd_cmd = "cd";
            CMD.push_back(cd_cmd);
            CMD.push_back(directory_name);
            executeCommand = findFunction(cd_cmd);
            executeCommand(fileTree_, CMD);
            parseForFileTree(directoryObj, objNames[i]);
        }
        else{
            // name of the path to access content in resources
            std::vector<std::string> CMD;
            std::string mk_cmd = "make";
            std::string directory_name = objName;
            std::string pathName = directoryObj[objNames[i]].asString();
            CMD.push_back(mk_cmd);
            CMD.push_back(directory_name);
            CMD.push_back(pathName);
            commandFn executeCommand = findFunction(mk_cmd);
            executeCommand(fileTree_, CMD);
            //std::cout << pathName << std::endl;
        }
        
    }
    std::vector<std::string> CMD2;
    std::string cd_cmd = "cd";
    std::string dot_dot = "..";
    CMD2.push_back(cd_cmd);
    CMD2.push_back(dot_dot);
    commandFn executeCommand = findFunction(cd_cmd);
    executeCommand(fileTree_, CMD2);
}


