#pragma once

#include <string>

//#include "emailMessageRenderComponent.h"

///////////////////////////////////////////////////////////////////////
/// @brief A toolkit of functions that sets up a complete window
/// @author Alex Vincent 
/// @details Create/initialize a WindowInterface pointer and pass it by 
/// pointer to any one of these functions. The passed WindowInterface 
/// will be augmented by the function you called on it. Make sure that
/// the input handler you pass is unique to that window.
///////////////////////////////////////////////////////////////////////
namespace sf {
	class Image;
};


namespace ppc {
	class WindowInterface;
	class InputHandler;
	class TextDisplayRenderComponent;
	class explorerFolderInputComponent;
	class Database;
	class Desktop;
	class Inbox;
	class NodeState;
	class Email;
	class Event;
	class Entity;
	//typedef bool (databaseSearchInputComponent::*goBack) (sf::Event&);
	//using backFunction = bool(databaseSearchInputComponent::*goBack)(sf::Event& ev);
	///////////////////////////////////////////////////////////////////////
	///@brief Constructs a console window on the WindowInterface passed.
	///
	///@param The newly created window to add components/entities to.
	///@param The input handler of the listened-to window.
	///@param The filetree for which the console will work on.
	///@param Sprite sheet of it's border component's buttons
	///////////////////////////////////////////////////////////////////////
void spawnConsole(Desktop& dt, WindowInterface*& windowToModify, InputHandler& ih, NodeState ns,
	sf::Image& buttonSheet, float x, float y);

///////////////////////////////////////////////////////////////////////
///@brief Constructs a database window on the WindowInterface passed.
///
///@param The newly created window to add components/entities to.
///@param The input handler of the listened-to window.
///@param Sprite sheet of it's border component's buttons
///////////////////////////////////////////////////////////////////////
void spawnDatabase(WindowInterface*& windowToModify, InputHandler& ih, Database* db,
	sf::Image& buttonSheet, float x, float y);
    
    ///////////////////////////////////////////////////////////////////////
    ///@brief Constructs a database window on the WindowInterface passed.
    ///
    ///@param The newly created window to add components/entities to.
    ///@param The input handler of the listened-to window.
    ///@param Sprite sheet of it's border component's buttons
    ///////////////////////////////////////////////////////////////////////
void spawnHelp(WindowInterface*& windowToModify, InputHandler& ih, 
      sf::Image& buttonSheet, float x, float y);
    
    
///////////////////////////////////////////////////////////////////////
///@brief Constructs a pipeline window on the WindowInterface passed.
///
///@param The newly created window to add components/entities to.
///@param The input handler of the listened-to window.
///@param Sprite sheet of it's border component's buttons
///////////////////////////////////////////////////////////////////////
void spawnPipeline(WindowInterface*& windowToModify, InputHandler& ih, Database* db,
        sf::Image& buttonSheet, float x, float y);

///////////////////////////////////////////////////////////////////////
///@brief Constructs a file window on the WindowInterface passed.
///
///@param The newly created window to add components/entities to.
///@param The input handler of the listened-to window.
///@param The file tree to read from
///@param Sprite sheet of it's border component's buttons
///@param The x position of the new window
///@param The y position of the new window
///@param The in-game filename
///@param The out-of-game resource path to load the new file
///////////////////////////////////////////////////////////////////////
void spawnFile(WindowInterface*& windowToModify, InputHandler& ih, float x, float y, 
	std::string filename, std::string path);

///////////////////////////////////////////////////////////////////////
///@brief Constructs an inbox window on the WindowInterface passed.
///
///@param The desktop to make new email windows unto
///@param The newly created window to add components/entities to.
///@param The input handler of the listened-to window.
///@param Sprite sheet of it's border component's buttons
///@param The x position of the new window
///@param The y position of the new window
///////////////////////////////////////////////////////////////////////
void spawnInbox(Desktop& dT, WindowInterface*& windowToModify, InputHandler& ih, sf::Image& buttonSheet, float x, float y, Inbox& ib);

///////////////////////////////////////////////////////////////////////
///@brief Constructs a generic email window on the WindowInterface passed.
///
///@param The newly created window to add components/entities to.
///@param The input handler of the listened-to window.
///@param The email object to read the contents of
///@param Sprite sheet of it's border component's buttons
///@param The x position of the new window
///@param The y position of the new window
///////////////////////////////////////////////////////////////////////
void spawnEmailMessage(WindowInterface*& windowToModify, InputHandler& ih, Email* eM, sf::Image& buttonSheet, float x, float y);

///////////////////////////////////////////////////////////////////////
///@brief Constructs a generic error message window
///
///@param The newly created window to add components/entities to.
///@param The input handler of the listened-to window.
///@param Sprite sheet of it's border component's buttons
///@param The x position of the new window
///@param The y position of the new window
///@param Custom string the message will display
///////////////////////////////////////////////////////////////////////
void spawnErrorMessage(WindowInterface*& windowToModify, InputHandler& ih, sf::Image& buttonSheet, float x, float y, std::string message, std::string windowCaption);

///////////////////////////////////////////////////////////////////////
///@brief Constructs a generic success message window
///
///@param The newly created window to add components/entities to.
///@param The input handler of the listened-to window.
///@param Sprite sheet of it's border component's buttons
///@param The x position of the new window
///@param The y position of the new window
///@param Custom string the message will display
///////////////////////////////////////////////////////////////////////
void spawnSuccessMessage(WindowInterface*& windowToModify, InputHandler& ih, sf::Image& buttonSheet, float x, float y, std::string message);
    
    
///////////////////////////////////////////////////////////////////////
///@brief Constructs a generic prompt message window
///
///@param The newly created window to add components/entities to.
///@param The input handler of the listened-to window.
///@param Sprite sheet of it's border component's buttons
///@param The x position of the new window
///@param The y position of the new window
///@param Custom string the message will display
///@param The window caption to display on the window
///////////////////////////////////////////////////////////////////////
void spawnPromptMessage(WindowInterface*& windowToModify, InputHandler& ih, sf::Image& buttonSheet, float x, float y, std::string message);

///////////////////////////////////////////////////////////////////////
///@brief Constructs a generic prompt message window
///
///@param The newly created window to add components/entities to.
///@param The input handler of the listened-to window.
///@param Sprite sheet of it's border component's buttons
///@param The x position of the new window
///@param The y position of the new window
///@param Custom string the message will display
///////////////////////////////////////////////////////////////////////
void spawnUnlock(WindowInterface*& windowToModify, InputHandler& ih, sf::Image& buttonSheet, float x, float y, explorerFolderInputComponent* fldr);

    ///////////////////////////////////////////////////////////////////////
    ///@brief Constructs a Login Prompt message window
    ///
    ///@param The newly created window to add components/entities to.
    ///@param The input handler of the listened-to window.
    ///@param Sprite sheet of it's border component's buttons
    ///@param The x position of the new window
    ///@param The y position of the new window
    ///@param Custom string the message will display
    ///////////////////////////////////////////////////////////////////////
void spawnLoginPrompt(WindowInterface*& windowToModify, InputHandler& ih, sf::Image& buttonSheet, float x, float y);

    

///////////////////////////////////////////////////////////////////////
///@brief Constructs a explore window on the WindowInterface passed.
///
///@param The newly created window to add components/entities to.
///@param The input handler of the listened-to window.
///@param The filetree for which the console will work on.
///@param Sprite sheet of it's border component's buttons
///@param The x position of the new window
///@param The y position of the new window
///////////////////////////////////////////////////////////////////////
void spawnExplorer(Desktop& dt, WindowInterface*& windowToModify, InputHandler& ih, NodeState* ns,
	sf::Image& buttonSheet, sf::Image& iconSheet, float x, float y);


///////////////////////////////////////////////////////////////////////
///@brief Constructs a temporary, borderless context menu
///
///@param The newly created window to add components/entities to.
///@param The input handler of the listened-to window.
///@param A vector of the names of the context list elements
///@param The x position of the new window
///@param The y position of the new window
///////////////////////////////////////////////////////////////////////
void spawnContextMenu(Desktop& dt, WindowInterface*& windowToModify, InputHandler& ih, 
	std::vector<std::string> n, std::vector<bool(*)(Desktop*, Event ev)>, float x, float y);

///////////////////////////////////////////////////////////////////////
///@brief Constructs a temporary, borderless context menu
///
///@param The newly created window to add components/entities to.
///@param A vector of ContextBuilder-constructed entities
///@param The x position of the new window
///@param The y position of the new window
///////////////////////////////////////////////////////////////////////
void spawnContextMenu(WindowInterface*& windowToModify,
	std::vector<ppc::Entity> listElements,  float x, float y);

///////////////////////////////////////////////////////////////////////
///@brief Constructs a static file tracker/suspicious file holder
///
///@param The newly created window to add components/entities to.
///@param The input handler of the listened-to window.
///@param The static suspicious folder holder for the desktop extraction
///@param The x position of the new window
///@param The y position of the new window
///////////////////////////////////////////////////////////////////////
void spawnFileTracker(Desktop& dt, WindowInterface*& windowToModify, InputHandler& ih, float x, float y);

///////////////////////////////////////////////////////////////////////
///@brief Constructs a settings menu
///
///@param The newly created window to add components/entities to.
///@param The input handler of the listened-to window.
///@param The static suspicious folder holder for the desktop extraction
///@param The x position of the new window
///@param The y position of the new window
///////////////////////////////////////////////////////////////////////
void spawnSettingsMenu(Desktop* dt, WindowInterface*& windowToModify, InputHandler& ih, float x, float y);

///////////////////////////////////////////////////////////////////////
///@brief Constructs a credits window
///
///@param The desktop to add it to
///@param An empty windowInterface
///@param The input handler of the empty window interface
///@param X position of the window
///@param Y position of the window
///////////////////////////////////////////////////////////////////////
void spawnCreditsWindow(Desktop* dt, WindowInterface*& windowToModify, InputHandler& ih, float x, float y);

bool close_window(WindowInterface* w, ppc::Event ev);
bool open_settings(WindowInterface *w, ppc::Event ev);
bool open_credits(WindowInterface* w, ppc::Event ev);
bool continue_world(WindowInterface* w, ppc::Event ev);

bool increment_resolution(TextDisplayRenderComponent*, ppc::Event ev);
bool decrement_resolution(TextDisplayRenderComponent*, ppc::Event ev);

bool increment_volume(TextDisplayRenderComponent*, ppc::Event ev);
bool decrement_volume(TextDisplayRenderComponent*, ppc::Event ev);

bool toggle_window_settings(TextDisplayRenderComponent*, ppc::Event);
bool update_settings(TextDisplayRenderComponent*, ppc::Event ev);
};



