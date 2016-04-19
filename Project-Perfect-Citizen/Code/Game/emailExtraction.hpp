//
//  emailExtraction.hpp
//  Project-Perfect-Citizen
//
//  Created by Brandon Gomez on 3/7/16.
//  Copyright © 2016 Hyperfocus Games. All rights reserved.
//

#ifndef emailExtraction_hpp
#define emailExtraction_hpp

#include <vector>


namespace Json {
    class Value;
};

namespace ppc {
    
    class emailExtraction{
        
    public:
        
        ///////////////////////////////////////////////////////////////////
        /// @brief constructor for creating email data
        ///////////////////////////////////////////////////////////////////
        emailExtraction();
        
        ////////////////////////////////////////////////////////////////////
        /// @brief Builds Json::Value Object containing email content
        /// @details Builds a C++ Json representation of email content
        ///     object as specified by a .json file
        /// @param[out] Json::Value         Json object containing
        ///                                 email content
        /// @param[in]  string              Name of Email Json file
        ////////////////////////////////////////////////////////////////////
        Json::Value parseEmailAsJson(std::string file);
        
        ///////////////////////////////////////////////////////////////////
        /// @brief parses the JSON file and gets the appropiate file name
        ///     & path, to be used email loading
        /// @param[in] Json::Value          Json object containg the dir
        ///                                 objects
        /// @param[in] std::string          The name of the email to be
        ///                                 entered
        ///////////////////////////////////////////////////////////////////
        void parseEmailForInbox(Json::Value folder, std::string obj);
        
        ///////////////////////////////////////////////////////////////////
        /// @brief adds a string to the TO vector of email
        /// @param[in] string               String name to be pushed
        ///                                 into TO vector
        ///////////////////////////////////////////////////////////////////
        void addTo(std::string content){
            to_.push_back(content);
        }
        
        ///////////////////////////////////////////////////////////////////
        /// @brief adds a string to the FROM vector of email
        /// @param[in] string               String name to be pushed
        ///                                 into FROM vector
        ///////////////////////////////////////////////////////////////////
        void addFrom(std::string content){
            from_.push_back(content);
        }
        
        ///////////////////////////////////////////////////////////////////
        /// @brief adds a string to the SUBJECT vector of email
        /// @param[in] string               String name to be pushed
        ///                                 into SUBJECT vector
        ///////////////////////////////////////////////////////////////////
        void addSubject(std::string content){
            subject_.push_back(content);
        }
        
        ///////////////////////////////////////////////////////////////////
        /// @brief adds a string to the BODY vector of email
        /// @param[in] string               String name to be pushed
        ///                                 into BODY vector
        ///////////////////////////////////////////////////////////////////
        void addBody(std::string content){
            body_.push_back(content);
        }
        
        void addVisible(bool b){
            visible_.push_back(b);
        }
        
        ///////////////////////////////////////////////////////////////////
        /// @brief gets the TO vector of email
        /// @param[out] vector<string>      Vector containing all TO
        ///                                 strings
        ///////////////////////////////////////////////////////////////////
        std::vector<std::string> getTo(){
            return to_;
        }
        
        ///////////////////////////////////////////////////////////////////
        /// @brief gets the FROM vector of email
        /// @param[out] vector<string>      Vector containing all FROM
        ///                                 strings
        ///////////////////////////////////////////////////////////////////
        std::vector<std::string> getFrom(){
            return from_;
        }
        
        ///////////////////////////////////////////////////////////////////
        /// @brief gets the SUBJECT vector of email
        /// @param[out] vector<string>      Vector containing all SUBJECT
        ///                                 strings
        ///////////////////////////////////////////////////////////////////
        std::vector<std::string> getSubject(){
            return subject_;
        }
        
        ///////////////////////////////////////////////////////////////////
        /// @brief gets the BODY vector of email
        /// @param[out] vector<string>      Vector containing all BODY
        ///                                 strings
        ///////////////////////////////////////////////////////////////////
        std::vector<std::string> getBody(){
            return body_;
        }
        
        std::vector<bool> getVisible(){
            return visible_;
        }
        
        bool checkSizeOfAll(){
            if(to_.size() == from_.size()){
                if(from_.size() == subject_.size()){
                    if(subject_.size() == body_.size()){
                        return true;
                    }
                }
            }
            return false;
        }
        
    private:
        std::vector<std::string> to_;
        std::vector<std::string> from_;
        std::vector<std::string> subject_;
        std::vector<std::string> body_;
        std::vector<bool> visible_;
    };
    
};

#endif /* emailExtraction_hpp */
