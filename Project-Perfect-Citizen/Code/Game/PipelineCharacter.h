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
// In regards to the above I was running into issues when I had them
// generate immediately when instantiated, I don't remember why.  If
// it ends up being better to automatically generate them it should be
// simple to change it.
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

	std::string getPersOutgoing() const { return persOutgoing_; }
	std::string getPersInfo() const { return persInfo_; }
	std::string getPersDecision() const { return persDecision_; }
	std::string getPersStructure() const { return persStructure_; }

	std::string getJob() const { return job_; }

	///////////////////////////////////////////////////////////////////
	// Setters not needed?
	// BE CAREFUL IF SETTING PERSONALITY/JOB, MUST CONFIRM IT EXISTS AS
	// A POSSIBLE OUTCOME
	///////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////
	// Generate Character
	///////////////////////////////////////////////////////////////////
	
	///////////////////////////////////////////////////////////////////
	/// @brief Generates pipeline character data
	///////////////////////////////////////////////////////////////////
	void generate();


private:
	int iq_;
	int age_;
	int creditScore_;

	std::string  ssn_;
	std::string email_;
	std::string phoneNumber_;

	std::string persOutgoing_;
	std::string persInfo_;
	std::string persDecision_;
	std::string persStructure_;

	std::string job_;

};

};