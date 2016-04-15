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
	int getAge() const { return age_; }

	std::string getSSN() const { return ssn_; }
	std::string getEmail() const { return email_; }
	std::string getPhoneNum() const { return phoneNumber_; }

	int getPersAssertive() const { return persAssertive_; }
	int getPersDirectness() const { return persDirectness_; }
	int getPersJerk() const { return persJerk_; }


	std::string getJob() const { return job_; }
    
    int getEyeType() const { return eyeType_;}
    int getBrowType() const { return browType_;}
    int getMouthType() const { return mouthType_;}
    int getNoseType() const { return noseType_;}
    int getSkinType() const { return skinType_;}
    int getHairType() const { return hairType_;}
    int getShirtType() const { return shirtType_;}
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

	///////////////////////////////////////////////////////////////////
	/// @brief Specific constructor, generates a character with a
	///			specified job, age, and criminality
	/// @param [in] job a string corresponding to a specific job type,
	///                 must be one of the jobs listed in JOBS in
	///                 PipelineCharacter.cpp
	///////////////////////////////////////////////////////////////////

	PipelineCharacter(const std::string& job, int age, bool criminal);


private:

	///////////////////////////////////////////////////////////////////
	/// @brief Generates pipeline character data
	///////////////////////////////////////////////////////////////////
	void generate();

	///////////////////////////////////////////////////////////////////
	/// @brief Sets income level and criminality based
	///        on previously generated factors
	///////////////////////////////////////////////////////////////////
	void calcIncomeAndCrim();

	int age_;

	// 0 - DID NOT GRADUATE HIGH SCHOOL, 1 - HIGH SCHOOL GRADUATE
	// 2 - ASSOCIATE DEGREE, 3 - BACHELORS DEGREE, 
	// 4 - MASTERS DEGREE, 5 - DOCTORATE
	int educationLevel_;

	int annualIncome_;

	bool criminal_;

	//Range 0 - 4, where 4 is most close to the descriptive word
	//ex. for persJerk: 4 = asshole, 0 = sweet/kindly
	int persAssertive_;
	int persJerk_;
	int persDirectness_;
	
	std::string ssn_;
	std::string email_;
	std::string phoneNumber_;

	//std::string persSocial_;
	//std::string persTakeIn_;
	//std::string persDecisions_;
	//std::string persOuterLife_;

	std::string job_;
    
    ////// CHARACTER PROFILES /////
    int eyeType_;
    int browType_;
    int mouthType_;
    int noseType_;
    int skinType_;
    int hairType_;
    int shirtType_;
    int skinColorIndex_;
    int hairColorIndex_;
    int lipColorIndex_;
    
    sf::Color eyeColor_;
    sf::Color shirtColor_;
};

};