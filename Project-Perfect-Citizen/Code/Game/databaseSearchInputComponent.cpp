#include "databaseSearchInputComponent.h"
#include <iostream>
#include <string>

using namespace std;
const string TEXT_KEY_INPUT = "TKI";

const float DOUBLE_CLICK_TIME = 500;
const int CONTROL_UNICODE = 128;
const int BACKSPACE_UNICODE = 8;
const int ENTER_UNICODE = 10;
const int CARRIAGE_RETURN_UNICODE = 13;

databaseSearchInputComponent::databaseSearchInputComponent(Database* initialDB, ppc::InputHandler& ih, databaseSearchRenderComponent& t,
	databaseDisplayRenderComponent& d, sf::Sprite& s)
	: InputComponent(2), textBoxSprt(s), textBox(t), textDisplay(d), inputHandle(ih) {

	ih.addHandle(sf::Event::TextEntered);
	ih.addHandle(sf::Event::KeyPressed);

	watch(ih, sf::Event::TextEntered);
	watch(ih, sf::Event::KeyPressed);
		
	searchHistory.push(initialDB);


	str += "Search: ";
	textBox.updateString(str);

	displayResults_.push_back("Enter a filter and query to begin searching");
	textDisplay.updateString(displayResults_);

}

databaseSearchInputComponent::~databaseSearchInputComponent() {
	ignore(inputHandle, sf::Event::TextEntered);
	ignore(inputHandle, sf::Event::KeyPressed);
}

bool databaseSearchInputComponent::isCollision(sf::Vector2i mousePos) {
	sf::Vector2f sprtBoxPos = { textBoxSprt.getGlobalBounds().left ,
		textBoxSprt.getGlobalBounds().top };

	sf::Vector2f sprtBoxDim = { textBoxSprt.getGlobalBounds().width,
		textBoxSprt.getGlobalBounds().height };

	bool result = false;
	if (mousePos.x >= sprtBoxPos.x  &&
		mousePos.x <= sprtBoxPos.x + sprtBoxDim.x) {
		if (mousePos.y >= sprtBoxPos.y &&
			mousePos.y <= sprtBoxPos.y + sprtBoxDim.y) {
			result = true;
		}
	}

	// textBoxSprt.setSelected(true);

	return result;
}

std::vector<string> convertToVector(string cmd) {
	std::vector<string> commandVec;
	string delimiter = " ";
	size_t last = 0;
	size_t next = 0;
	string token;
	while ((next = cmd.find(delimiter, last)) !=
		string::npos) {
		token = cmd.substr(last, next - last);
		commandVec.push_back(token);
		last = next + 1;
	}
	return commandVec;
}

void databaseSearchInputComponent::updateDisplayOutput(std::vector<std::string> newOut) {
	displayResults_.clear();
	displayResults_ = newOut;
}

void databaseSearchInputComponent::clearSearchBox() {
	this->str.erase(8, this->str.length());
	textBox.updateString(str);
}

void databaseSearchInputComponent::updateDisplayResults(vector<string> displayVec, string newDisplay) {
	displayVec.push_back(newDisplay);
	updateDisplayOutput(displayVec);
}

bool databaseSearchInputComponent::registerInput(sf::Event& ev) {
	if (getEntity() != nullptr) {

		/* Ignore CNTRL, BS, ENTR/LF, CR symbols*/
		if (ev.type == sf::Event::TextEntered) {
			if (ev.text.unicode < CONTROL_UNICODE && 
				ev.text.unicode != BACKSPACE_UNICODE &&
				ev.text.unicode != ENTER_UNICODE && 
				ev.text.unicode != CARRIAGE_RETURN_UNICODE) {
				str.push_back((char)ev.text.unicode);
				textBox.updateString(str);
			}
		}

		/* Register backspace as deletion, enter as execute */
		else if (ev.type == sf::Event::KeyPressed) {
			if (ev.key.code == sf::Keyboard::BackSpace && 
				(str.size()>8)) {
				str.pop_back();
				textBox.updateString(str);
			}
			else if (ev.key.code == sf::Keyboard::Return &&
				(str.size() != 0)) {
				std::string cmd;
				for (size_t i = 8; i<str.size(); ++i) {
					cmd.push_back(str.at(i));
				}
				cmd += " ";

				std::vector<string> commandVec = convertToVector(cmd);
				std::vector<string> displayVec;
				string filter = "";
				string query = "";


				/* Temp back functionality: Will turn into function pointer */
				if (commandVec.at(0) == "back") {
					clearSearchBox();
					if (searchHistory.size() > 1) {
						if (searchHistory.size() == 2) {
							searchHistory.pop();
							updateDisplayResults(displayVec, "Enter a filter and query to begin searching");
							textDisplay.updateString(displayResults_);
							return true;
						} else {
							searchHistory.pop();
							updateDisplayOutput(searchHistory.top()->getPrintableDatabase());
							textDisplay.updateString(displayResults_);
							return true;
						}	
					}
				}

				/* Assign good input to corresponding values */
				if (commandVec.size() == 2) {
					filter = commandVec.at(0);
					query = commandVec.at(1);
				}

				/* Otherwise reset it */
				else { 
					clearSearchBox();
					updateDisplayResults(displayVec, "Invalid input");
					textDisplay.updateString(displayResults_);
					return true;
				}
				
				if (searchHistory.top()->filterIsValid(filter)) {
					Database* filteredDatabase;
					filteredDatabase = &(searchHistory.top()->sortBy(filter, query));
					cout << filteredDatabase->getDatabaseSize() << endl;
					if (filteredDatabase->isEmpty()) { 
						updateDisplayResults(displayVec, "No results found");
					}
					else {
						searchHistory.emplace(filteredDatabase);
						updateDisplayOutput(searchHistory.top()->getPrintableDatabase());
					}
				}
				
				clearSearchBox();
				textDisplay.updateString(displayResults_);
			}
		}
	}
	return true;
}