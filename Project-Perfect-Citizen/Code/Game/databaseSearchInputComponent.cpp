#include "../Engine/debug.h"
#include "databaseSearchInputComponent.h"
#include <iostream>
#include <string>

using namespace ppc;
const string TEXT_KEY_INPUT = "TKI";

const float DOUBLE_CLICK_TIME = 500;
const int CONTROL_UNICODE = 128;
const int BACKSPACE_UNICODE = 8;
const int ENTER_UNICODE = 10;
const int CARRIAGE_RETURN_UNICODE = 13;

databaseSearchInputComponent::databaseSearchInputComponent(Database* initialDB, ppc::InputHandler& ih, databaseSearchRenderComponent& t,
	databaseDisplayRenderComponent& d, characterRender& r)
	: InputComponent(2),  textBox(t), textDisplay(d), inputHandle(ih), render(r) {

	ih.addHandle(sf::Event::TextEntered);
	ih.addHandle(sf::Event::KeyPressed);

	watch(ih, sf::Event::TextEntered);
	watch(ih, sf::Event::KeyPressed);
		
	searchHistory.push(initialDB);


	str += "Search: ";
	textBox.updateString(str);

	displayResults_.push_back("No filters entered. Please enter a filter and query to begin searching.");
	textDisplay.updateString(displayResults_);

}

databaseSearchInputComponent::~databaseSearchInputComponent() {
	ignore(inputHandle, sf::Event::TextEntered);
	ignore(inputHandle, sf::Event::KeyPressed);
}

bool databaseSearchInputComponent::isCollision(sf::Vector2i mousePos) {
	
    // Temporarily(?) removing collisions. May not be necessary
    
    /*sf::Vector2f sprtBoxPos = { textBoxSprt.getGlobalBounds().left ,
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

	// textBoxSprt.setSelected(true);*/

    return true;//result;
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

void databaseSearchInputComponent::goBack() {
		std::vector<string> displayVec;
		clearSearchBox();
		if (searchHistory.size() > 1) {
			if (searchHistory.size() == 2) {
				searchHistory.pop();
				updateDisplayResults(displayVec, "No filters entered. Please enter a filter and query to begin searching.");
				textDisplay.updateString(displayResults_);
			}
			else {
				searchHistory.pop();
				updateDisplayOutput(searchHistory.top()->getPrintableDatabase());
				textDisplay.updateString(displayResults_);
			}
		}
}

void databaseSearchInputComponent::updateDisplayResults(vector<string> displayVec, string newDisplay) {
	displayVec.push_back(newDisplay);
	updateDisplayOutput(displayVec);
}

bool databaseSearchInputComponent::registerInput(sf::Event& ev) {
	if (getEntity() != nullptr) {

		int lookAt = 0;

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


				/*// Temp back functionality: Will turn into function pointer
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
				}*/

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
				

				/* Clean the filter term of any caps*/
				string cleaned = "";
				for (unsigned int i = 0; i < filter.length(); ++i) {
					cleaned.push_back(tolower(filter.at(i)));

				}


				if (searchHistory.top()->filterIsValid(cleaned)) {
					Database* filteredDatabase;
					filteredDatabase = &(searchHistory.top()->sortBy(cleaned, query));
					cout << filteredDatabase->getDatabaseSize() << endl;
					if (filteredDatabase->isEmpty()) { 
						searchHistory.emplace(filteredDatabase);
						updateDisplayResults(displayVec, "No results found. Please go back and try another query.");
					}
					else {
						render.applyCharacterValues(filteredDatabase->getDatabaseState().at(lookAt));
						searchHistory.emplace(filteredDatabase);
						updateDisplayOutput(searchHistory.top()->getPrintableDatabase());
					}
				}
				
				clearSearchBox();
				cout << searchHistory.size() << endl;
				textDisplay.updateString(displayResults_);
			}
		}
	}
	return true;
}










bool ppc::goBackFn(databaseSearchInputComponent* ptr, sf::Event& ev) {
    ptr->goBack();
    return true;
}







