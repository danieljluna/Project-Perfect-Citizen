#include "createDesktop.h"
using namespace ppc;

void createPlayerDesktop(Desktop& desktopToModify, WindowInterface& desktopWindowToModify, InputHandler& ih, sf::Image& iconSheet, sf::Image& buttonSheet ) {

	
	//////////////////////////////////////////////
	//// Create the database (really should take a seed)
	/////////////////////////////////////////////
	Database theDatabase;
	theDatabase.generateFullDatabase(25);
	/*Database& filteredDatabase = Database();
	string filter = "job";
	string query = "Doctor";
	if (theDatabase.filterIsValid(filter)) {
	filteredDatabase = theDatabase.sortBy(filter, query);
	cout << " New Filtered Database: " << endl;
	filteredDatabase.printCharacters();
	} */
	
	
	//////////////////////////////////////////////
	//// Create the start menu
	/////////////////////////////////////////////
	ppc::WindowInterface* startToolbar =
		new ppc::Window(1000, 60, sf::Color(128, 128, 128));
	startToolbar->setPosition(0, 750);
	Entity* startButton = new Entity();
	spawnStartButton(*startButton, startToolbar->getInputHandler(), buttonSheet, 0, 0, 0.4f);
	startToolbar->addEntity(*startButton);
	desktopToModify.addWindow(startToolbar);


	////////////////////////////////
	///// ICONS ON PLAYER DESKTOP
	////////////////////////////////
	Entity* ConsoleIcon = new Entity();
	Entity* FolderIcon = new Entity();
	Entity* BrowserIcon = new Entity();
	Entity* ChatIcon = new Entity();
	Entity* DataGraphIcon = new Entity();
	Entity* HardDriveIcon = new Entity();
	Entity* SettingsIcon = new Entity();
	Entity* SearchIcon = new Entity();

	spawnConsoleIcon(*ConsoleIcon, desktopToModify, ih, iconSheet, buttonSheet, 25.0f, 50.0f, 0.4f, 0.25f);
	spawnFolderIcon(*FolderIcon, desktopToModify, ih, iconSheet, buttonSheet, 25.0f, 100.0f, 0.4f, 0.25f);
	spawnBrowserIcon(*BrowserIcon, desktopToModify, ih, iconSheet, buttonSheet, 25.0f, 150.0f, 0.4f, 0.25f);
	spawnChatIcon(*ChatIcon, desktopToModify, ih, iconSheet, buttonSheet, 25.0f, 200.0f, 0.4f, 0.25f);
	spawnDataGraphIcon(*DataGraphIcon, desktopToModify, ih, iconSheet, buttonSheet, 25.0f, 250.0f, 0.4f, 0.25f);
	spawnHardDriveIcon(*HardDriveIcon, desktopToModify, ih, iconSheet, buttonSheet, 25.0f, 300.0f, 0.4f, 0.25f);
	spawnSettingsIcon(*SettingsIcon, desktopToModify, ih, iconSheet, buttonSheet, 25.0f, 350.0f, 0.4f, 0.25f);
	spawnSearchIcon(*SearchIcon, desktopToModify, ih, iconSheet, buttonSheet, 25.0f, 400.0f, 0.4f, 0.25f);

	desktopWindowToModify.addEntity(*ConsoleIcon);
	desktopWindowToModify.addEntity(*FolderIcon);
	desktopWindowToModify.addEntity(*BrowserIcon);
	desktopWindowToModify.addEntity(*ChatIcon);
	desktopWindowToModify.addEntity(*DataGraphIcon);
	desktopWindowToModify.addEntity(*HardDriveIcon);
	desktopWindowToModify.addEntity(*SettingsIcon);
	desktopWindowToModify.addEntity(*SearchIcon);

}