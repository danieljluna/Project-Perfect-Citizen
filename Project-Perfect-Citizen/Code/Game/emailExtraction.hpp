//
//  emailExtraction.hpp
//  Project-Perfect-Citizen
//
//  Created by Brandon Gomez on 3/7/16.
//  Copyright © 2016 Hyperfocus Games. All rights reserved.
//

#ifndef emailExtraction_hpp
#define emailExtraction_hpp

#include <stdio.h>
#include <string>
#include <vector>

#include "../Library/json/json.h"
#include "../Engine/NodeState.h"

namespace ppc {
    
    class emailExtraction{
        
    public:
        
        emailExtraction();
        
        Json::Value parseEmailAsJson(std::string file, std::string obj);
        
        void parseEmailForInbox(Json::Value folder, std::string obj);
        
        void addSubject(string content){
            subject_.push_back(content);
        }
        
        void addContent(string content){
            content_.push_back(content);
        }
        
    private:
        vector<string> subject_;
        vector<string> content_;
    };
    
};

#endif /* emailExtraction_hpp */
