#include "createDesktop.h"

using namespace ppc;

void createPlayerDesktop(Desktop& desktopToModify, WindowInterface& desktopWindowToModify, InputHandler& ih, sf::Image& iconSheet) {

	//////////////////////////////////////////////
	//// Create Player File Tree
	/////////////////////////////////////////////
	//NodeState* playerFileTree = new NodeState();;
	//playerFileTree->setUp();

	//////////////////////////////////////////////
	//// Create the desktop window/desktop itself
	/////////////////////////////////////////////
	//WindowInterface* desktopWindow = new Window(1800, 1000, sf::Color(200, 200, 200));
	//Desktop myDesktop(*desktopWindow, *playerFileTree);

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

	spawnConsoleIcon(*ConsoleIcon, desktopToModify, ih, iconSheet, 25.0f, 50.0f, 0.4f, 0.25f);
	spawnFolderIcon(*FolderIcon, ih, iconSheet, 25.0f, 100.0f, 0.4f, 0.25f);
	spawnBrowserIcon(*BrowserIcon, ih, iconSheet, 25.0f, 150.0f, 0.4f, 0.25f);
	spawnChatIcon(*ChatIcon, ih, iconSheet, 25.0f, 200.0f, 0.4f, 0.25f);
	spawnDataGraphIcon(*DataGraphIcon, ih, iconSheet, 25.0f, 250.0f, 0.4f, 0.25f);
	spawnHardDriveIcon(*HardDriveIcon, ih, iconSheet, 25.0f, 300.0f, 0.4f, 0.25f);
	spawnSettingsIcon(*SettingsIcon, ih, iconSheet, 25.0f, 350.0f, 0.4f, 0.25f);
	spawnSearchIcon(*SearchIcon, ih, iconSheet, 25.0f, 400.0f, 0.4f, 0.25f);

	desktopWindowToModify.addEntity(*ConsoleIcon);
	desktopWindowToModify.addEntity(*FolderIcon);
	desktopWindowToModify.addEntity(*BrowserIcon);
	desktopWindowToModify.addEntity(*ChatIcon);
	desktopWindowToModify.addEntity(*DataGraphIcon);
	desktopWindowToModify.addEntity(*HardDriveIcon);
	desktopWindowToModify.addEntity(*SettingsIcon);
	desktopWindowToModify.addEntity(*SearchIcon);

}