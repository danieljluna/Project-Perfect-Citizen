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


namespace ppc {

class desktopExtractionComponent{
    
public:
    
    ///////////////////////////////////////////////////////////////////
    ///@brief constructor for crearting desktop data
    ///////////////////////////////////////////////////////////////////
    
    desktopExtractionComponent();
    
    ///////////////////////////////////////////////////////////////////
    // Create Desktop Extraction Data using JSON
    ///////////////////////////////////////////////////////////////////
    
    void setDesktop(std::string file);
    
    ///////////////////////////////////////////////////////////////////
    // Setters
    ///////////////////////////////////////////////////////////////////
    void setEmail(std::vector<std::string> emails){
        emails_ = emails;
    }
    void setMessages(std::vector<std::string> messages){
        chatMessages_ = messages;
    }
    void setHistory(std::vector<std::string> history){
        localHistory_ = history;
    }
    void setDocuments(std::vector<std::string> documents){
        localDocuments_ = documents;
    }
    ///////////////////////////////////////////////////////////////////
    // Getters
    ///////////////////////////////////////////////////////////////////
    std::vector<std::string> getEmail(){
        return emails_;
    }
    std::vector<std::string> getMessages(){
        return chatMessages_;
    }
    std::vector<std::string> getHistory(){
        return localHistory_;
    }
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