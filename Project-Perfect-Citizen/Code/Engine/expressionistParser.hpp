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
#include <map>

namespace ppc {
    
class expressionistParser{
    
public:
    
    ///////////////////////////////////////////////////////////////////
    ///@brief constructor for parsing expressionist data
    ///////////////////////////////////////////////////////////////////

    expressionistParser();
    
    
    std::vector<expressionistParser> parse(std::string file);
    
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
    void setMarkUp(std::map<std::string, std::string> markUp){
        markUp_ = markUp;
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
    std::map<std::string, std::string> getMarkUp(){
        return markUp_;
    }
    
private:
    std::string expression_;
    bool complete_;
    bool deep_;
    
    int appRate_;
    std::map<std::string, std::string> markUp_;
};
    
};

#endif /* expressionistParser_hpp */
