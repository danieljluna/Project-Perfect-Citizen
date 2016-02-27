//
//  desktopExtractionComponent.hpp
//  Project-Perfect-Citizen
//
//  Created by Brandon Gomez on 2/12/16.
//  Copyright © 2016 Hyperfocus Games. All rights reserved.
//

#ifndef desktopExtractionComponent_hpp
#define desktopExtractionComponent_hpp

#include <stdio.h>
#include <string>
#include <vector>

#include "../Library/json/json.h"

namespace ppc {

class desktopExtractionComponent{
    
public:
    
    ///////////////////////////////////////////////////////////////////
    ///@brief constructor for crearting desktop data
    ///////////////////////////////////////////////////////////////////
    desktopExtractionComponent();
    
    ////////////////////////////////////////////////////////////////////
    /// @brief Builds Json::Value Object containing Desktop content and
    //      their appropiate paths
    /// @details Builds a C++ Json representation of Desktop content
    ///     object as specified by a .json file
    /// @param[out] Json::Value         Json object containing
    ///                                 an expressionist grammar
    /// @param[in]  string              Json file name containing an
    ///                                 expressionist grammar
    ////////////////////////////////////////////////////////////////////
    Json::Value parseDesktopAsJson(std::string file);
    
  ///////////////////////////////////////////////////////////////////
  // Setters
  ///////////////////////////////////////////////////////////////////
    
    ///////////////////////////////////////////////////////////////////
    // @brief stores all the emails in a vector
    ///////////////////////////////////////////////////////////////////
    void setEmail(std::vector<std::string> emails){
        emails_ = emails;
    }
    
    ///////////////////////////////////////////////////////////////////
    // @brief stores all the messages in a vector
    ///////////////////////////////////////////////////////////////////
    void setMessages(std::vector<std::string> messages){
        chatMessages_ = messages;
    }
    
    ///////////////////////////////////////////////////////////////////
    // @brief stores all the local history in a vector
    ///////////////////////////////////////////////////////////////////
    void setHistory(std::vector<std::string> history){
        localHistory_ = history;
    }
    
    ///////////////////////////////////////////////////////////////////
    // @brief stores all the local documents in a vector
    ///////////////////////////////////////////////////////////////////
    void setDocuments(std::vector<std::string> documents){
        localDocuments_ = documents;
    }
    
  ///////////////////////////////////////////////////////////////////
  // Getters
  ///////////////////////////////////////////////////////////////////
    
    ///////////////////////////////////////////////////////////////////
    // @brief returns the local email vector of the desktop
    ///////////////////////////////////////////////////////////////////
    std::vector<std::string> getEmail(){
        return emails_;
    }
    
    ///////////////////////////////////////////////////////////////////
    // @brief returns the local messages vector of the desktop
    ///////////////////////////////////////////////////////////////////
    std::vector<std::string> getMessages(){
        return chatMessages_;
    }
    
    ///////////////////////////////////////////////////////////////////
    // @brief returns the local history vector of the desktop
    ///////////////////////////////////////////////////////////////////
    std::vector<std::string> getHistory(){
        return localHistory_;
    }
    
    ///////////////////////////////////////////////////////////////////
    // @brief returns the local documetns vector of the desktop
    ///////////////////////////////////////////////////////////////////
    std::vector<std::string> getDocuments(){
        return localDocuments_;
    }
    
private:
    std::vector<std::string> emails_;
    std::vector<std::string> chatMessages_;
    std::vector<std::string> localHistory_;
    std::vector<std::string> localDocuments_;
};

};
    


#endif /* desktopExtractionComponent_hpp */