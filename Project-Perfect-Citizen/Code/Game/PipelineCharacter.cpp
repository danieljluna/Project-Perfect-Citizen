#include <random>

#include "PipelineCharacter.h"

using namespace ppc;

const std::string OUTGOING_VALUES[] = { "Extravert", "Ambivert", 
                                 "Introvert" };
const int OUTGOING_SIZE	 = 3;

const std::string INFORMATION_VALUES[] = { "Sensing", "Middle", 
										  "Intuition" };
const int INFORMATION_SIZE = 3;

const std::string DECISION_VALUES[] = { "Thinking", "Middle", 
									   "Feeling" };
const int DECISION_SIZE = 3;

const std::string STRUCTURE_VALUES[] = { "Judging", "Middle", 
										"Perceiving" };
const int STRUCTURE_SIZE = 3;

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
	std::uniform_int_distribution<> outd(0, OUTGOING_SIZE - 1);
	std::uniform_int_distribution<> infod(0, INFORMATION_SIZE - 1);
	std::uniform_int_distribution<> decd(0, DECISION_SIZE - 1);
	std::uniform_int_distribution<> strucd(0, STRUCTURE_SIZE - 1);
	std::uniform_int_distribution<> jobd(0, JOBS_SIZE - 1);
	persOutgoing_ = OUTGOING_VALUES[outd(gen)];
	persInfo_ = INFORMATION_VALUES[infod(gen)];
	persDecision_ = DECISION_VALUES[decd(gen)];
	persStructure_ = STRUCTURE_VALUES[strucd(gen)];
	job_ = JOBS[jobd(gen)];

}

std::ostream& ppc::operator<<(std::ostream & os, 
	                          const PipelineCharacter & pc)
{
	os << "IQ = " << pc.iq_ << ", Age = " << pc.age_;
	os << ", Credit Score = " << pc.creditScore_ << std::endl;

	os << "SSN: " << pc.ssn_ << ", Email: " << pc.email_;
	os << ", Phone: " << pc.phoneNumber_ << std::endl;

	os << "Personality: " << pc.persOutgoing_ << ", " << pc.persInfo_;
	os << ", " << pc.persDecision_ << ", " << pc.persStructure_;
	os << std::endl;

	return os;
}
