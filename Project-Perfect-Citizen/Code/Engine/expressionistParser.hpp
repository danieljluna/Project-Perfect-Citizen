//
//  expressionistParser.hpp
//  Project-Perfect-Citizen
//
//  Created by Brandon Gomez on 2/15/16.
//  Copyright © 2016 Hyperfocus Games. All rights reserved.
//

#ifndef expressionistParser_hpp
#define expressionistParser_hpp

#include <stdio.h>
#include <string>
#include <vector>

namespace ppc {
    
class expressionistParser{
    
public:
    
    ///////////////////////////////////////////////////////////////////
    ///@brief constructor for parsing expressionist data
    ///////////////////////////////////////////////////////////////////

    expressionistParser();
    
    
    void parse(std::string file);
    
    ///////////////////////////////////////////////////////////////////
    // Setters
    ///////////////////////////////////////////////////////////////////
    void setExpression(std::string expression){
        expression_ = expression;
    }
    void setDeep(bool deep){
        deep_ = deep;
    }
    void setAppRate(int appRate){
        appRate_ = appRate;
    }
    void setExpansion(std::string expansion){
        expansion_ = expansion;
    }
    void setMarkUp(std::vector<std::string> markUp){
        markUp_ = markUp;
    }
    void setRules(std::vector<expressionistParser> rules){
        rules_ = rules;
    }
    
    ///////////////////////////////////////////////////////////////////
    // Getters
    ///////////////////////////////////////////////////////////////////
    
    std::string getExpression(){
        return expression_;
    }
    bool getDeep(){
        return deep_;
    }
    int getAppRate(){
        return appRate_;
    }
    std::string getExpansion(){
        return expansion_;
    }
    std::vector<std::string> getMarkUp(){
        return markUp_;
    }
    std::vector<expressionistParser> getRules(){
        return rules_;
    }
    
private:
    std::string expression_;
    bool complete_;
    bool deep_;
    int appRate_;
    std::string expansion_;
    std::vector<std::string> markUp_;
    std::vector<expressionistParser> rules_;
};
    
};

#endif /* expressionistParser_hpp */
