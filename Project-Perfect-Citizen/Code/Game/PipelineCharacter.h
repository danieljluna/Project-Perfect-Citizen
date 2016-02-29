#pragma once

#include <string>
#include <iostream>

///////////////////////////////////////////////////////////////////////
/// @author Mark Biundo
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

};

};