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

desktopExtractionComponent::desktopExtractionComponent(NodeState& ft) : fileTree_(ft){
    BaseObserver* subHead = fileTree_.onOpen().getObserverHead();
    if (subHead != nullptr) {
        fileTree_.onOpen().removeObserver(subHead);
    }
}

Json::Value desktopExtractionComponent::parseDesktopAsJson(std::string file, std::string obj) {
    Json::Reader reader;
    Json::Value value;
    std::ifstream doc(resourcePath() + file, std::ifstream::binary);
    bool parsingSuccessful = reader.parse(doc, value, false);
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
        if(contentObj.size() > 0){
            std::vector<std::string> CMD;
            std::string mk_dir_cmd = "mkdir";
            std::string directory_name = objName;
            std::string directory_name_copy = objName;
            std::string password;
            std::string hint;
            std::string delimiter = "/";
            size_t pos = 0;
            std::string token;
            std::string token2;
            int count = 0;
            bool dirHasPassword = false;
            commandFn executeCommand;
            while ((pos = directory_name_copy.find(delimiter)) != std::string::npos) {
                dirHasPassword = true;
                token = directory_name_copy.substr(0, pos);
                if(count == 0){
                    directory_name = token;
                    directory_name_copy.erase(0, pos + delimiter.length());
                    CMD.push_back(mk_dir_cmd);
                    CMD.push_back(directory_name);
                    executeCommand = findFunction(mk_dir_cmd);
                    executeCommand(fileTree_, CMD);
                }
                else{
                    std::string cd_cmd = "cd";
                    CMD.push_back(cd_cmd);
                    CMD.push_back(directory_name);
                    executeCommand = findFunction(cd_cmd);
                    executeCommand(fileTree_, CMD);
                    password = token;
                    directory_name_copy.erase(0, pos + delimiter.length());
                    pos = directory_name_copy.find(delimiter);
                    hint = directory_name_copy.substr(0, pos);
                    fileTree_.getCwd()->setPassword(password, hint);
                    parseForFileTree(directoryObj, objNames[i]);
                }
                count++;
            }
            if(!dirHasPassword){
                CMD.push_back(mk_dir_cmd);
                CMD.push_back(directory_name);
                executeCommand = findFunction(mk_dir_cmd);
                executeCommand(fileTree_, CMD);
                std::string cd_cmd = "cd";
                CMD.push_back(cd_cmd);
                CMD.push_back(directory_name);
                executeCommand = findFunction(cd_cmd);
                executeCommand(fileTree_, CMD);
                parseForFileTree(directoryObj, objNames[i]);
            }
        }
        else{
            // find delimeter to get suspiconPoints
            std::string directory_name_copy = objName;
            std::string delimiter = "/";
            unsigned int suspicionPoints;
            size_t pos = 0;
            pos = directory_name_copy.find(delimiter);
            suspicionPoints = std::stoi(directory_name_copy.substr(0, pos));
            directory_name_copy.erase(0, pos + delimiter.length());
            pos = directory_name_copy.find(delimiter);
            
            // name of the path to access content in resources
            std::vector<std::string> CMD;
            std::string mk_cmd = "make";
            std::string directory_name = directory_name_copy.substr(0, pos);
            std::string pathName = directoryObj[objNames[i]].asString();
            CMD.push_back(mk_cmd);
            CMD.push_back(directory_name);
            CMD.push_back(pathName);
            if(directory_name != "Empty"){
                fileTree_.getCwd()->setSuspicionLevel(suspicionPoints);
                commandFn executeCommand = findFunction(mk_cmd);
                executeCommand(fileTree_, CMD);
                fileTree_.getCwd()->findElement(directory_name)->setSuspicionLevel(suspicionPoints);
            }
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
