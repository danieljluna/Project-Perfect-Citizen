#include "Database.h"


using namespace std;

Database::Database() {

}

Database::~Database() {

}

void Database::generateFullDatabase(int newMaxNumber) {
	
	/* Spawn a fresh database of the characters */
	dataBaseMax_ = newMaxNumber;
	vector<ppc::PipelineCharacter> newDatabase;
	for (int i = 0; i < dataBaseMax_; ++i) {
		ppc::PipelineCharacter newCharacter;
		newCharacter.generate();
		newDatabase.push_back(newCharacter);
	}
	databaseState_ = newDatabase;
}

void Database::setNewSnapshot(vector<ppc::PipelineCharacter> newSnapShot) {
	databaseState_ = newSnapShot;
}

bool Database::filterIsValid(string filter) {

	/* Clean the filter term of any caps*/
	string cleaned = "";
	for (unsigned int i = 0; i < filter.length(); ++i) {
		cleaned.push_back(tolower(filter.at(i)));
	}

	if (cleaned.compare("iq") == 0) return true;
	else if (cleaned.compare("age") == 0) return true;
	else if (cleaned.compare("credit score") == 0) return true;
	else if (cleaned.compare("ssn") == 0) return true;
	else if (cleaned.compare("email") == 0) return true;
	else if (cleaned.compare("phone") == 0) return true;
	else if (cleaned.compare("job") == 0) return true;

	cout << "Error: Invalid filter" << endl;
	return false;
	
}

Database& Database::sortBy(string filter, string query) {

	Database* newDatabaseState = new Database();
	vector<ppc::PipelineCharacter> newSnapshot;

	/* Case : Job Filter */
	if (filter.compare("job") == 0) {
		for (auto iter = databaseState_.begin(); iter != databaseState_.end(); ++iter) {
			if (iter->getJob().compare(query) == 0)
				newSnapshot.push_back(*iter);
		}
	}
	
	newDatabaseState->setNewSnapshot(newSnapshot);
	return *newDatabaseState;
}

void Database::printCharacters() {
	int entry = 0;
	for (auto iter = databaseState_.begin(); iter != databaseState_.end(); ++iter) {

		//STUB: Should print to in-game database
		cout << 
			"Entry: " << entry << ": " <<
			iter->getIQ() << ", " << 
			iter->getAge() << ", " <<
			iter->getCreditScore() << ", " <<
			iter->getSSN() << ", " <<
			iter->getEmail() << ", " <<
			iter->getPhoneNum() << ", " <<
			iter->getJob() << ", " <<
			endl;

		++entry;
	}

}


