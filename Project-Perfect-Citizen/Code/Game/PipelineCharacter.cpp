#include <random>

#include "PipelineCharacter.h"

using namespace ppc;

const std::string SOCIAL_VALUES[] = { "Extravert", "Ambivert", 
                                 "Introvert" };
const int SOCIAL_SIZE	 = 3;

const std::string TAKE_IN_VALUES[] = { "Sensing", "Middle", 
										  "Intuition" };
const int TAKE_IN_SIZE = 3;

const std::string DECISIONS_VALUES[] = { "Thinking", "Middle", 
									   "Feeling" };
const int DECISIONS_SIZE = 3;

const std::string OUTER_LIFE_VALUES[] = { "Judging", "Middle", 
										"Perceiving" };
const int OUTER_LIFE_SIZE = 3;

const std::string JOBS[] = {
	"Doctor",
	"Lawyer",
	"Teacher",
	"Student",
	"Retail",
	"Service"
};
const int JOBS_SIZE = 6;


void PipelineCharacter::generate() {
	std::random_device rd;
	std::mt19937 gen(rd());

	// set IQ (normal distribution approx range 55 - 145)
	std::normal_distribution<> iqd(100, 15);
	iq_ = static_cast<int>(std::round(iqd(gen)));

	// set age (even distribution 18 - 65)
	std::uniform_int_distribution<> aged(18, 65);
	age_ = aged(gen);

	// set credit score (normal distribution, centered at 600, std dev
	// 150, capped at 800, minimum 200 - this likely needs a bit of
	// tweaking but it's not super important)
	std::normal_distribution<> csd(600, 150);
	creditScore_ = static_cast<int>(std::round(csd(gen)));
	if (creditScore_ > 800) creditScore_ = 800;
	if (creditScore_ < 200) creditScore_ = 200;

	// set "Social Security Number" - two random letters followed by
	// two random 3 digit numbers
	std::uniform_int_distribution<> letterd(0, 25);
	std::uniform_int_distribution<> threed(100, 999);
	char first = letterd(gen) + 'A';
	char second = letterd(gen) + 'A';
	ssn_ = first;
	ssn_ += second;
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
	std::uniform_int_distribution<> outd(0, SOCIAL_SIZE - 1);
	std::uniform_int_distribution<> infod(0, TAKE_IN_SIZE - 1);
	std::uniform_int_distribution<> decd(0, DECISIONS_SIZE - 1);
	std::uniform_int_distribution<> strucd(0, OUTER_LIFE_SIZE - 1);
	std::uniform_int_distribution<> jobd(0, JOBS_SIZE - 1);
	persSocial_ = SOCIAL_VALUES[outd(gen)];
	persTakeIn_ = TAKE_IN_VALUES[infod(gen)];
	persDecisions_ = DECISIONS_VALUES[decd(gen)];
	persOuterLife_ = OUTER_LIFE_VALUES[strucd(gen)];
	job_ = JOBS[jobd(gen)];

}

std::ostream& ppc::operator<<(std::ostream & os, 
	                          const PipelineCharacter & pc)
{
	os << "IQ = " << pc.iq_ << ", Age = " << pc.age_;
	os << ", Credit Score = " << pc.creditScore_ << std::endl;

	os << "SSN: " << pc.ssn_ << ", Email: " << pc.email_;
	os << ", Phone: " << pc.phoneNumber_ << std::endl;

	os << "Personality: " << pc.persSocial_ << ", " << pc.persTakeIn_;
	os << ", " << pc.persDecisions_ << ", " << pc.persOuterLife_;
	os << std::endl;

	return os;
}
