#include <random>
#include <cassert>
#include <algorithm>
#include <map>

#include "../Engine/debug.h"
#include "PipelineCharacter.h"
#include "PipelineJobsAndIncomes.h"

using namespace ppc;

const std::string DEBUG_FLAG = "pc";

//see crimvalue below.  Can be set in range [0,500].  The greater the
//number the lower the percentage of characters that are deemed "criminals"
const int CRIM_THRESHOLD = 350;

ppc::PipelineCharacter::PipelineCharacter() {
	age_ = NULL;
	educationLevel_ = NULL;
	annualIncome_ = NULL;
	criminal_ = NULL;
	persAssertive_ = NULL;
	persJerk_ = NULL;
	persDirectness_ = NULL;
	ssn_ = "";
	email_ = "";
	phoneNumber_ = "";
	job_ = "";
}

//ppc::PipelineCharacter::PipelineCharacter(const std::string & job) {
//	auto itor = std::find(JOBS_ALL.begin(), JOBS_ALL.end(), job);
//	generate();
//	if (itor == JOBS_ALL.end()) {
//		DEBUGF(DEBUG_FLAG, "Job not found");
//	}
//	else {
//		job_ = job;
//		auto itor = MIN_EDUCATION.find(job);
//		if (itor == MIN_EDUCATION.end()) {
//			DEBUGF(DEBUG_FLAG, "Job not found in MIN_EDUCATION");
//		} 
//		else if (MIN_EDUCATION.at(job_) > educationLevel_)
//			educationLevel_ = MIN_EDUCATION.at(job_);
//	}
//	calcIncomeAndCrim();
//}
//
//ppc::PipelineCharacter::PipelineCharacter(const std::string & job, int age, bool criminal) {
//	auto itor = std::find(JOBS_ALL.begin(), JOBS_ALL.end(), job);
//	generate();
//	if (itor == JOBS_ALL.end()) {
//		DEBUGF(DEBUG_FLAG, "Job not found");
//	}
//	else {
//		job_ = job;
//		auto itor = MIN_EDUCATION.find(job);
//		if (itor == MIN_EDUCATION.end()) {
//			DEBUGF(DEBUG_FLAG, "Job not found in MIN_EDUCATION");
//		} 
//		else if (MIN_EDUCATION.at(job_) > educationLevel_)
//			educationLevel_ = MIN_EDUCATION.at(job_);
//	}
//
//	if (age > 65) {
//		age_ = 65;
//	}
//	else if (age < 18) {
//		age_ = 18;
//	}
//	else age_ = age;
//
//	calcIncomeAndCrim();
//
//	criminal_ = criminal;
//}

void PipelineCharacter::calcIncomeAndCrim() {
	int median = 0;
	int starting = 0;

	auto itora = MEDIAN_INCOME_MAP.find(job_);
	if (itora == MEDIAN_INCOME_MAP.end()) {
		DEBUGF(DEBUG_FLAG, "Job not found in MEDIAN_INCOME_MAP");
	}
	else median = MEDIAN_INCOME_MAP.at(job_);

	auto itorb = STARTING_INCOME_MAP.find(job_);
	if (itorb == STARTING_INCOME_MAP.end()) {
		DEBUGF(DEBUG_FLAG, "Job not found in STARTING_INCOME_MAP");
	}
	else starting = STARTING_INCOME_MAP.at(job_);

	if (starting == 0) starting = 25;
	if (median == 0) median = 40;

	bool cap = true;
	auto itorc = INCOME_CAP.find(job_);
	if (itorc == INCOME_CAP.end()) {
		DEBUGF(DEBUG_FLAG, "Job not found in INCOME_CAP");
	}
	else cap = INCOME_CAP.at(job_);
		
	int incap = static_cast<int>(median + 1.5 * (median - starting));
	annualIncome_ = starting + ((median - starting) / 15) * age_;
	
	if (cap && annualIncome_ > incap) annualIncome_ = incap;


	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> incdiff(0, 5000);
	annualIncome_ = annualIncome_ * 1000 + incdiff(gen);

	//
	//
	//  SET CRIMINAL WEIGHTED BY AGE, PERSONALITY
	if (criminal_ == NULL) {
		std::uniform_int_distribution<> variance(0, 99);
		int crimvariance = variance(gen);
		// (100 - 2.128 * (age_ - 18)) = inverse of age as a % of closeness to 65
		// so 18 = 100%, 65 = 0%
		//crimvalue ranges [0, 500]
		int crimvalue = static_cast<int>(100 - 2.128 * (age_ - 18)) + persAssertive_ * 25 +
			persDirectness_ * 25 + persJerk_ * 25 + crimvariance;
		if (crimvalue > CRIM_THRESHOLD) criminal_ = true;
		else criminal_ = false;
	}
	//
	//
}

void PipelineCharacter::generateWithNameJob(const std::string& name, const std::string& job) {
	if (name.length() > 2) {
		ssn_ = name.substr(0, 2);
	}
	for (auto & c : ssn_) c = toupper(c);

	for (unsigned int i = 0; i < JOBS_ALL.size(); ++i) {
		if (JOBS_ALL[i].compare(job) == 0) {
			job_ = job;
			generateRaw();
			return;
		}
	}
	job_ = "";
	generateRaw();
}

void PipelineCharacter::generateWithName(const std::string& name) {
	if (name.length() > 2) {
		ssn_ = name.substr(0, 2);
	}
	for (auto & c : ssn_) c = toupper(c);
	generateRaw();
}

void PipelineCharacter::generateWithNameJobAgeCrim(const std::string& name, const std::string& job, int age, bool crim) {
	if (name.length() > 2) {
		ssn_ = name.substr(0, 2);
	}
	for (auto & c : ssn_) c = toupper(c);

	for (unsigned int i = 0; i < JOBS_ALL.size(); ++i) {
		if (JOBS_ALL[i].compare(job) == 0) {
			job_ = job;
		}
	}

	if (age < 18) age_ = 18;
	else if (age > 65) age_ = 65;
	else age_ = age;

	criminal_ = crim;
	generateRaw();
}



void PipelineCharacter::generateRaw() {
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_int_distribution<> educd(0, 99);
	int edvalue = educd(gen);
	if (edvalue < 12) educationLevel_ = 0; //did not graduate high school
	else if (edvalue < 58) educationLevel_ = 1; // graduated high school, did not get degree
	else if (edvalue < 68) educationLevel_ = 2; // got associate degree, not bachelor
	else if (edvalue < 88) educationLevel_ = 3; // got bachelor
	else if (edvalue < 97) educationLevel_ = 4; // got master/professional degree
	else educationLevel_ = 5; //Doctorate

	// set age (even distribution 18 - 65)
	if (age_ == NULL) {
		std::uniform_int_distribution<> aged(18, 65);
		age_ = aged(gen);
	}

	// set "Social Security Number" - two random letters followed by
	// two random 3 digit numbers
	std::uniform_int_distribution<> threed(100, 999);
	if (ssn_.empty()) {
		std::uniform_int_distribution<> letterd(0, 25);

		char first = letterd(gen) + 'A';
		char second = letterd(gen) + 'A';
		ssn_ = first;
		ssn_ += second;
	}
	if (ssn_.length() == 2) {
		ssn_ += '-';
		ssn_ += std::to_string(threed(gen));
		ssn_ += '-';
		ssn_ += std::to_string(threed(gen));
	}

	// set email - currently just appends domain.tld to ssn
	email_ = ssn_;
	email_ += "@example.ppc";

	// set phone number, 555- random 3 digit - random 4 digit
	std::uniform_int_distribution<> fourd(1000, 9999);
	phoneNumber_ = "555-";
	phoneNumber_ += std::to_string(threed(gen));
	phoneNumber_ += '-';
	phoneNumber_ += std::to_string(fourd(gen));

	// set peronality and job
	std::uniform_int_distribution<> persRange(0, 4);
	persAssertive_ = persRange(gen);
	persJerk_ = persRange(gen);
	persDirectness_ = persRange(gen);

	//could add some more procedurality here
	if (job_.compare("") == 0) {
		std::vector<std::string> validjobs;
		for (unsigned int i = 0; i < MIN_EDUCATION.size(); ++i) {
			if (MIN_EDUCATION.at(JOBS_ALL[i]) <= educationLevel_ &&
				MIN_EDUCATION.at(JOBS_ALL[i]) >= educationLevel_ - 1) validjobs.push_back(JOBS_ALL[i]);
		}


		assert(!validjobs.empty());

		std::uniform_int_distribution<> jobd(0, validjobs.size() - 1);
		job_ = validjobs[jobd(gen)];
	}
    
	calcIncomeAndCrim();
    
    // for random colors
    std::uniform_int_distribution<> colord(100, 250);
    // for random colors
    std::uniform_int_distribution<> colorshirtd(0, 255);
    // for eye types
    std::uniform_int_distribution<> eyed(0, 2);
    // for brow types
    std::uniform_int_distribution<> browd(10, 19);
    // for mouth types
    std::uniform_int_distribution<> mouthd(4, 9);
    // for nose types
    std::uniform_int_distribution<> nosed(0, 8);
    // for skin index
    std::discrete_distribution<> skind
    {3, 3, 2, 1, 3, 2, 1, 3, 1, 3,  //10
     1, 1, 1, 2, 1, 2, 1, 1, 2, 1,  //10
	 1, 2, 1, 2, 1, 1, 1, 1, 1};


    std::uniform_int_distribution<> shirtd(5, 8);
    // for hair index
    std::uniform_int_distribution<> haircd(0, 7);
    // for har type
    std::uniform_int_distribution<> haird(0, 10);
    //for lip index
    std::uniform_int_distribution<> lipcd(0, 3);
    
    
    sf::Color sc(colorshirtd(gen),colorshirtd(gen),colorshirtd(gen));
    shirtColor_ = sc;
    
    sf::Color ec(colord(gen),colord(gen),colord(gen));
    eyeColor_ = ec;
    
    eyeType_ = eyed(gen);
    
    browType_ = browd(gen);
    
    mouthType_ = mouthd(gen);
    
    noseType_ = nosed(gen);
    
    hairType_ = 2*haird(gen);
    //int remainder = hairType_% 2;
    //hairType_ = hairType_ + 2 - remainder;
    
    shirtType_ = 5*shirtd(gen);
    //int remainders = shirtType_% 5;
    //shirtType_ = shirtType_ + 5 - remainders;    
    
    //shirtType_ =  5*(shirtd(gen)/5);
    //shirt remainder
    //int s_remainder = shirtType_ % 5;
    
    
    
    //shirtType_ = shirtType_ - s_remainder;//toRound - toRound % 10;
    
   /* if (shirtType_ == 0) {
        shirtType_ = 5;
    } else {
        shirtType_ = 10;
    }*/
    
    skinColorIndex_ = skind(gen);
    hairColorIndex_ = haircd(gen);
    lipColorIndex_ = lipcd(gen);
    

}

std::ostream& ppc::operator<<(std::ostream & os, 
	                          const PipelineCharacter & pc)
{
	os << "Age = " << pc.age_;
	os << "SSN: " << pc.ssn_ << ", Email: " << pc.email_;
	os << ", Phone: " << pc.phoneNumber_ << std::endl;
	//os << std::endl;

	return os;
}
