#include <random>
#include <cassert>
#include <algorithm>

#include "../Engine/debug.h"
#include "PipelineCharacter.h"
#include "PipelineJobsAndIncomes.h"

using namespace ppc;

const std::string DEBUG_FLAG = "pc";


ppc::PipelineCharacter::PipelineCharacter() {
	generate();
}

ppc::PipelineCharacter::PipelineCharacter(const std::string & job) {
	auto itor = std::find(JOBS.begin(), JOBS.end(), job);
	generate();
	if (itor == JOBS.end()) {
		DEBUGF(DEBUG_FLAG, "Job not found");
	}
	else {
		job_ = job;
		auto itor = std::find(MIN_EDUCATION.begin(), MIN_EDUCATION.end(), job);
		if (itor == MIN_EDUCATION.end()) {
			DEBUGF(DEBUG_FLAG, "Job not found in MIN_EDUCATION");
		} 
		else if (MIN_EDUCATION.at(job_) > educationLevel_)
			educationLevel_ = MIN_EDUCATION.at(job_);
	}
}

ppc::PipelineCharacter::PipelineCharacter(const std::string & job, int age, bool criminal) {
	auto itor = std::find(JOBS.begin(), JOBS.end(), job);
	generate();
	if (itor == JOBS.end()) {
		DEBUGF(DEBUG_FLAG, "Job not found");
	}
	else {
		job_ = job;
		auto itor = std::find(MIN_EDUCATION.begin(), MIN_EDUCATION.end(), job);
		if (itor == MIN_EDUCATION.end()) {
			DEBUGF(DEBUG_FLAG, "Job not found in MIN_EDUCATION");
		} 
		else if (MIN_EDUCATION.at(job_) > educationLevel_)
			educationLevel_ = MIN_EDUCATION.at(job_);
	}

	if (age > 65) {
		age_ = 65;
	}
	else if (age < 18) {
		age_ = 18;
	}
	else age_ = age;

	criminal_ = criminal;
}

void PipelineCharacter::calcIncomeAndCrim() {
	std::random_device rd;
	std::mt19937 gen(rd());

	int median = 0;
	int starting = 0;

	auto itora = std::find(MEDIAN_INCOME_MAP.begin(), MEDIAN_INCOME_MAP.end(), job_);
	if (itora == MEDIAN_INCOME_MAP.end()) {
		DEBUGF(DEBUG_FLAG, "Job not found in MEDIAN_INCOME_MAP");
	}
	else median = MEDIAN_INCOME_MAP.at(job_);

	auto itorb = std::find(STARTING_INCOME_MAP.begin(), STARTING_INCOME_MAP.end(), job_);
	if (itorb == STARTING_INCOME_MAP.end()) {
		DEBUGF(DEBUG_FLAG, "Job not found in STARTING_INCOME_MAP");
	}
	else starting = STARTING_INCOME_MAP.at(job_);

	if (starting == 0) starting == 25;
	if (median == 0) median == 40;

	bool cap = true;
	auto itorc = std::find(INCOME_CAP.begin(), INCOME_CAP.end(), job_);
	if (itorc == INCOME_CAP.end()) {
		DEBUGF(DEBUG_FLAG, "Job not found in INCOME_CAP");
	}
	else cap = INCOME_CAP.at(job_);

	if (cap) {
		int incap = median + 1.5 * (median - starting);
		annualIncome_ = starting + ((median - starting) / 15) * age_;
		if (annualIncome_ > incap) annualIncome_ = incap;
	}
	else {
		annualIncome_ = starting + ((median - starting) / 15) * age_;
	}
	std::uniform_int_distribution<> incdiff(0, 5000);
	annualIncome_ = annualIncome_ * 1000 + incdiff(gen);


	// set credit score (normal distribution, centered at 600, std dev
	// 150, capped at 800, minimum 200 - this likely needs a bit of
	// tweaking but it's not super important)
	// weight by age/income? or deprecate?
	std::normal_distribution<> csd(600, 150);
	creditScore_ = static_cast<int>(std::round(csd(gen)));
	std::uniform_int_distribution<> csmod(0, 99);
	float csmodifier = 1 / (csmod(gen));

	if (creditScore_ > 800) creditScore_ = 800;
	if (creditScore_ < 200) creditScore_ = 200;

	//
	//
	//  SET CRIMINAL WEIGHTED BY AGE, CREDIT SCORE, PERSONALITY
	//
	//
}

void PipelineCharacter::generate() {
	std::random_device rd;
	std::mt19937 gen(rd());

	// set IQ (normal distribution approx range 55 - 145)
	std::normal_distribution<> iqd(100, 15);
	iq_ = static_cast<int>(std::round(iqd(gen)));

	std::uniform_int_distribution<> educd(0, 80);
	int edvalue = educd(gen) + (iq_ / 5); //range 11 - 109
	if (edvalue < 40) educationLevel_ = 0;
	if (edvalue >= 40 && edvalue < 70) educationLevel_ = 1;
	if (edvalue >= 70 && edvalue < 87) educationLevel_ = 2;
	if (edvalue >= 87 && edvalue < 100) educationLevel_ = 3;
	if (edvalue >= 100) educationLevel_ = 4;

	// set age (even distribution 18 - 65)
	std::uniform_int_distribution<> aged(18, 65);
	age_ = aged(gen);

	// set "Social Security Number" - two random letters followed by
	// two random 3 digit numbers
	std::uniform_int_distribution<> letterd(0, 25);
	std::uniform_int_distribution<> threed(100, 999);
	char first = letterd(gen) + 'A';
	char second = letterd(gen) + 'A';
	ssn_ = first;
	ssn_ += second;
	ssn_ += '-';
	ssn_ += std::to_string(threed(gen));
	ssn_ += '-';
	ssn_ += std::to_string(threed(gen));

	// set email - currently just appends domain.tld to ssn
	email_ = ssn_;
	email_ += "@example.ppc";

	// set phone number, 555- random 3 digit - random 4 digit
	std::uniform_int_distribution<> fourd(1000, 9999);
	phoneNumber_ = "555-";
	phoneNumber_ += std::to_string(threed(gen));
	phoneNumber_ += '-';
	phoneNumber_ += std::to_string(fourd(gen));

	// set peronality and job, random from a list of possible string
	// values that are used elsewhere for expressionist parsing
	//std::uniform_int_distribution<> outd(0, SOCIAL_SIZE - 1);
	//std::uniform_int_distribution<> infod(0, TAKE_IN_SIZE - 1);
	//std::uniform_int_distribution<> decd(0, DECISIONS_SIZE - 1);
	//std::uniform_int_distribution<> strucd(0, OUTER_LIFE_SIZE - 1);
	//persSocial_ = SOCIAL_VALUES[outd(gen)];
	//persTakeIn_ = TAKE_IN_VALUES[infod(gen)];
	//persDecisions_ = DECISIONS_VALUES[decd(gen)];
	//persOuterLife_ = OUTER_LIFE_VALUES[strucd(gen)];
	std::uniform_int_distribution<> persRange(0, 4);
	persAssertive_ = persRange(gen);
	persJerk_ = persRange(gen);
	persDirectness_ = persRange(gen);

	//could add some more procedurality here
	//As it currently stands higher education jobs are pretty unlikely
	while (true) {
		std::uniform_int_distribution<> jobd(0, JOBS_SIZE - 1);
		job_ = JOBS[jobd(gen)];
		auto itor = std::find(MIN_EDUCATION.begin(), MIN_EDUCATION.end(), job_);
		if (itor == MIN_EDUCATION.end()) {
			DEBUGF(DEBUG_FLAG, "Job not found in MIN_EDUCATION");
		}
		else if (educationLevel_ >= MIN_EDUCATION.at(job_)) break;
	}
    
    
    
    // for random colors
    std::uniform_int_distribution<> colord(100, 250);
    // for eye types
    std::uniform_int_distribution<> eyed(0, 2);
    // for brow types
    std::uniform_int_distribution<> browd(7, 9);
    // for mouth types
    std::uniform_int_distribution<> mouthd(4, 6);
    // for nose types
    std::uniform_int_distribution<> nosed(0, 2);
    // for skin index
    std::uniform_int_distribution<> skind(0, 7);
    // for hair index
    std::uniform_int_distribution<> haircd(0, 7);
    // for har type
    std::uniform_int_distribution<> haird(0, 2);
    //for lip index
    std::uniform_int_distribution<> lipcd(0, 3);
    
    
    sf::Color sc(colord(gen),colord(gen),colord(gen));
    shirtColor_ = sc;
    
    sf::Color ec(colord(gen),colord(gen),colord(gen));
    eyeColor_ = ec;
    
    
    eyeType_ = eyed(gen);
    
    browType_ = browd(gen);
    
    mouthType_ = mouthd(gen);
    
    noseType_ = nosed(gen);
    
    skinColorIndex_ = skind(gen);
    hairColorIndex_ = haircd(gen);
    lipColorIndex_ = lipcd(gen);
    

}

std::ostream& ppc::operator<<(std::ostream & os, 
	                          const PipelineCharacter & pc)
{
	os << "IQ = " << pc.iq_ << ", Age = " << pc.age_;
	os << ", Credit Score = " << pc.creditScore_ << std::endl;

	os << "SSN: " << pc.ssn_ << ", Email: " << pc.email_;
	os << ", Phone: " << pc.phoneNumber_ << std::endl;

	//os << "Personality: " << pc.persSocial_ << ", " << pc.persTakeIn_;
	//os << ", " << pc.persDecisions_ << ", " << pc.persOuterLife_;
	os << std::endl;

	return os;
}
