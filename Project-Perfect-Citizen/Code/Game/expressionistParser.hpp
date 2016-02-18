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

namespace expr {
    
class expressionistParser{
    ////////////////////////////////////////////////////////////////////
    ///@brief parsing out the JSON file returning a vector of the class
    ////////////////////////////////////////////////////////////////////
    friend std::vector<expressionistParser> parseExpressionist(std::string file);
public:
    
    ////////////////////////////////////////////////////////////////////
    ///@brief constructor for parsing expressionist data
    ////////////////////////////////////////////////////////////////////
    expressionistParser();
    
    
    
  ////////////////////////////////////////////////////////////////////
  // Setters
  ////////////////////////////////////////////////////////////////////
    
    ////////////////////////////////////////////////////////////////////
    // @brief sets the name of the object in the expressionistParser
    ////////////////////////////////////////////////////////////////////
    void setExpression(std::string expression){
        expression_ = expression;
    }
    
    ////////////////////////////////////////////////////////////////////
    // @brief sets the expression's complete.
    //     Dont know what this does yet, will ask James
    ////////////////////////////////////////////////////////////////////
    void setComplete(bool complete){
        complete_ = complete;
    }
    ////////////////////////////////////////////////////////////////////
    // @brief sets the expression's deep.
    //     Dont know what this does yet, will ask James
    ////////////////////////////////////////////////////////////////////
    void setDeep(bool deep){
        deep_ = deep;
    }
    
    ////////////////////////////////////////////////////////////////////
    // @brief sets the markup's or rules of the expression.
    //     first = expression, second.first = condition, second.second =
    //     rate. The rate of the
    //     expression, a higher rate means a higher chance of being
    //     called.
    ////////////////////////////////////////////////////////////////////
    void setMarkUp(std::map<std::string, std::pair<std::string, int>> markUp){
        markUp_ = markUp;
    }
    
  ////////////////////////////////////////////////////////////////////
  // Getters
  ////////////////////////////////////////////////////////////////////
    
    ////////////////////////////////////////////////////////////////////
    // @brief returns the name of the object in the expressionistParser
    ////////////////////////////////////////////////////////////////////
    std::string getExpression(){
        return expression_;
    }
    
    ///////////////////////////////////////////////////////////////////
    // @brief returns the expression's complete.
    //     Dont know what this does yet, will ask James
    ////////////////////////////////////////////////////////////////////
    bool getComplete(){
        return complete_;
    }
    
    ////////////////////////////////////////////////////////////////////
    // @brief returns the expression's deep.
    //     Dont know what this does yet, will ask James
    ////////////////////////////////////////////////////////////////////
    bool getDeep(){
        return deep_;
    }

    ////////////////////////////////////////////////////////////////////
    // @brief returns the markup's or rules of the expression.
    //     first = expression, second.first = condition, second.second =
    //     rate. The rate of the
    //     expression, a higher rate means a higher chance of being
    //     called.
    ////////////////////////////////////////////////////////////////////
    std::map<std::string, std::pair<std::string, int>> getMarkUp(){
        return markUp_;
    }
    
private:
    std::string expression_;
    bool complete_;
    bool deep_;
    
    std::map<std::string, std::pair<std::string, int>> markUp_;
};
    
};

#endif /* expressionistParser_hpp */
