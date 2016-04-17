#include <iostream>
#include <fstream>
#include <ostream>
#include <iomanip>
#include <string>
#include <vector>


using namespace std;
void splitString(string line, char delimiter, vector<string>& vec) {
	//int i = 0;
	//int j = line.find()
}


int main() {

	string fileName = "";
	string outputFile = "";
	cout << "Please enter the name of the file to be read" << endl;
	getline(std::cin, fileName);
	cout << "Please enter the file to be written to" << endl;
	getline(std::cin, outputFile);
	cout << "Exporting to file: " << outputFile << ". Reading from: " << fileName << ". The file will be created if it does not exist, otherwise it will be appended to." << endl;

	std::vector<std::string> splitVector;
	string line;

	ifstream ppcOutput(fileName);
	if (ppcOutput.is_open()) {
		string clockLabel = "";
		string clockTime = "";
		while (getline(ppcOutput, line)) {
			cout << line << endl;
			int labelLocation = line.find_first_of(":");
			clockLabel = line.substr(0, labelLocation);
			line = line.substr(labelLocation + 2);
			cout << "line is: " << line << endl;
			while (true) {
				int pos = line.find_first_not_of(", ");
				line = line.substr(pos, std::string::npos);
				pos = line.find_first_of(", ");
				string token = line.substr(0, pos);
				splitVector.push_back(token);
				if (pos == -1) break;
				line = line.substr(pos, std::string::npos);
			}
			cout << "printing line : ";
			std::ofstream output;
			output.open(outputFile, std::ios::app);
			int counter = 0;
			bool first = true;
			output << clockLabel + ",";
			for (auto iter = splitVector.begin(); iter != splitVector.end(); iter++) {
				output << *iter;
				counter++;
				if (counter != splitVector.size()) {
					output << ",";
				}
				if (counter == splitVector.size()) {
					output << std::endl;
				}
			}
			cout << endl;
			splitVector.clear();
			output.close();
		}
	}
	
	return 0;
}