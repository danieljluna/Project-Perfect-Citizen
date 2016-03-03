#pragma once

#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>

///////////////////////////////////////////////////////////////////////
/// @author Mark Biundo / Michael Lowe
/// @brief Procedurally Generated Pipeline Characters
/// @details contains elements of procedurally generated characters for
///  use in pipeline extraction sequences, as well as the function to
///  generate a character.  Characters are not automatically generated
///  when instantiated.
///////////////////////////////////////////////////////////////////////

namespace ppc {

class PipelineCharacter {
	friend std::ostream& operator<<(std::ostream& os, 
		                            const PipelineCharacter& pc);
public:
	///////////////////////////////////////////////////////////////////
	// Getters
	///////////////////////////////////////////////////////////////////
	int getIQ() const { return iq_;  }
	int getAge() const { return age_; }
	int getCreditScore() const { return creditScore_; }

	std::string getSSN() const { return ssn_; }
	std::string getEmail() const { return email_; }
	std::string getPhoneNum() const { return phoneNumber_; }

	std::string getPersSocial() const { return persSocial_; }
	std::string getPersTakeIn() const { return persTakeIn_; }
	std::string getPersDecisions() const { return persDecisions_; }
	std::string getPersOuterLife() const { return persOuterLife_; }

	std::string getJob() const { return job_; }
    
    int getEyeType() const { return eyeType_;}
    int getBrowType() const { return browType_;}
    int getMouthType() const { return mouthType_;}
    int getNoseType() const { return noseType_;}
    int getSkinType() const { return skinType_;}
    int getHairType() const { return hairType_;}
    int getSkinColorIndex() const { return skinColorIndex_;}
    int getHairColorIndex() const { return hairColorIndex_;}
    int getLipColorIndex() const { return lipColorIndex_;}
    sf::Color getEyeColor() const { return eyeColor_;}
    sf::Color getShirtColor() const { return shirtColor_;}
	///////////////////////////////////////////////////////////////////
	// Setters not needed?
	// BE CAREFUL IF SETTING PERSONALITY/JOB, MUST CONFIRM IT EXISTS AS
	// A POSSIBLE OUTCOME
	///////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////
	// Constructors
	///////////////////////////////////////////////////////////////////
	
	///////////////////////////////////////////////////////////////////
	/// @brief Default Constructor, generates character procedurally
	///        with no set features
	///////////////////////////////////////////////////////////////////

	PipelineCharacter();

	///////////////////////////////////////////////////////////////////
	/// @brief Job Constructor, generates character procedurally
	///        with a specific Job
	/// @param [in] job a string corresponding to a specific job type,
	///                 must be one of the jobs listed in JOBS in
	///                 PipelineCharacter.cpp
	///////////////////////////////////////////////////////////////////

	PipelineCharacter(const std::string& job);


private:

	///////////////////////////////////////////////////////////////////
	/// @brief Generates pipeline character data
	///////////////////////////////////////////////////////////////////
	void generate();

	int iq_;
	int age_;
	int creditScore_;

	std::string ssn_;
	std::string email_;
	std::string phoneNumber_;

	std::string persSocial_;
	std::string persTakeIn_;
	std::string persDecisions_;
	std::string persOuterLife_;

	std::string job_;
    
    ////// CHARACTER PROFILES /////
    int eyeType_;
    int browType_;
    int mouthType_;
    int noseType_;
    int skinType_;
    int hairType_;
    int skinColorIndex_;
    int hairColorIndex_;
    int lipColorIndex_;
    
    sf::Color eyeColor_;
    sf::Color shirtColor_;
};

};