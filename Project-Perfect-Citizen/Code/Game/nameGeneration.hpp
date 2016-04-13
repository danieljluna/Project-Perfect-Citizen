//
//  nameGeneration.hpp
//  Project-Perfect-Citizen
//
//  Created by Brandon Gomez on 4/8/16.
//  Copyright © 2016 Hyperfocus Games. All rights reserved.
//

#ifndef nameGeneration_hpp
#define nameGeneration_hpp

#include <stdio.h>
#include <string>

namespace ppc {
    
    class nameGeneration{
        
    public:
        
        ////////////////////////////////////////////////////////////////////
        /// @brief reads two texts files from resources called first.txt and
        ///     last.txt to set the first and last names of the name
        ///     generation
        ////////////////////////////////////////////////////////////////////
        void readFiles();
        
        ///////////////////////////////////////////////////////////////////
        /// @brief sets a value for the first name
        /// @param[in] string         first name string
        ///////////////////////////////////////////////////////////////////
        void setFirst(std::string firstName){
            first_ = firstName;
        }
        
        ///////////////////////////////////////////////////////////////////
        /// @brief sets a value for the last name
        /// @param[in] string         last name string
        ///////////////////////////////////////////////////////////////////
        void setLast(std::string lastName){
            last_ = lastName;
        }
        
        ///////////////////////////////////////////////////////////////////
        /// @brief once first and last name are set, this function will
        ///     a full name string consisting of first and last name
        ///////////////////////////////////////////////////////////////////
        void setFull(){
            full_ = first_ + " " + last_;
        }
        
        ////////////////////////////////////////////////////////////////////
        /// @brief returns the full name string
        /// @param[out] string         full name string
        ////////////////////////////////////////////////////////////////////
        std::string getFull(){
            return full_;
        }
        
        ////////////////////////////////////////////////////////////////////
        /// @brief returns the first name string
        /// @param[out] string         first name string
        ////////////////////////////////////////////////////////////////////
        std::string getfirst(){
            return first_;
        }
        
        ////////////////////////////////////////////////////////////////////
        /// @brief returns the last name string
        /// @param[out] string         last name string
        ////////////////////////////////////////////////////////////////////
        std::string getLast(){
            return last_;
        }
        
    private:
        std::string full_;
        std::string first_;
        std::string last_;
    };
    
};

#endif /* nameGeneration_hpp */
