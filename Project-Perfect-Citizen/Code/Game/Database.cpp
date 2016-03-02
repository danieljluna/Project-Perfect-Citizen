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

std::vector<ppc::PipelineCharacter> Database::getDatabaseState()
{
	return databaseState_;
}

std::vector<std::string> Database::getPrintableDatabase(){
	vector<string> printable;
	string temp = "";
	for (auto iter = this->databaseState_.begin(); iter != this->databaseState_.end(); ++iter) {
		temp.append("Result: ");
		temp.append(std::to_string(iter->getIQ()) + " ");
		temp.append(std::to_string(iter->getAge()) + " ");
		temp.append(std::to_string(iter->getCreditScore()) + " ");
		temp.append(iter->getSSN() + " ");
		temp.append(iter->getEmail() + " ");
		temp.append(iter->getPhoneNum() + " ");
		temp.append(iter->getJob());
		temp.append("\n");
		printable.push_back(temp);
		temp.clear();
	}
	return printable;
}

size_t Database::getDatabaseSize() {
	return databaseState_.size();
}

bool Database::isEmpty() {
	return databaseState_.empty();
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
		for (auto iter = this->databaseState_.begin(); iter != this->databaseState_.end(); ++iter) {
			if (iter->getJob().compare(query) == 0) 
				newSnapshot.push_back(*iter);
		}
	}
	else if (filter.compare("iq") == 0) {
		for (auto iter = this->databaseState_.begin(); iter != this->databaseState_.end(); ++iter) {
			if (std::to_string(iter->getIQ()).compare(query) == 0)
				newSnapshot.push_back(*iter);
		}
	}
	else if (filter.compare("age") == 0) {
		for (auto iter = databaseState_.begin(); iter != databaseState_.end(); ++iter) {
			if (std::to_string(iter->getAge()).compare(query) == 0)
				newSnapshot.push_back(*iter);
		}
	}
	else if (filter.compare("credit") == 0) {
		for (auto iter = databaseState_.begin(); iter != databaseState_.end(); ++iter) {
			if (std::to_string(iter->getCreditScore()).compare(query) == 0)
				newSnapshot.push_back(*iter);
		}
	}
	else if (filter.compare("ssn") == 0) {
		for (auto iter = databaseState_.begin(); iter != databaseState_.end(); ++iter) {
			if (iter->getJob().compare(query) == 0)
				newSnapshot.push_back(*iter);
		}
	}
	else if (filter.compare("email") == 0) {
		for (auto iter = databaseState_.begin(); iter != databaseState_.end(); ++iter) {
			if (iter->getJob().compare(query) == 0)
				newSnapshot.push_back(*iter);
		}
	}
	else if (filter.compare("phone") == 0) {
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




