//Used to get XCODE working/////////////////////////////////

#ifdef WINDOWS_MARKER
    #define resourcePath() string("Resources/")
#else
    #include "ResourcePath.hpp"
#endif

///////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>

#include <SFML/Main.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "Library/json/json.h"

#include "Engine/testRenderSprite.h"
#include "Engine/testRotateSprite.h"
#include "Engine/subject.h"
#include "Engine/TestObserver.h"
#include "Engine/debug.h"
#include "Engine/entity.h"
#include "Engine/Window.h"
#include "Engine/desktop.h"
#include "Engine/TreeCommands.h"
#include "Engine/NodeState.h"


using namespace ppc;


//Note that this is placeholder for now
int main(int argc, char** argv) {
	//Scans Debug Flags
	Debug::scanOpts(argc, argv);
	//Example of using the debugger macro
	DEBUGF("ac", argc);

    // Create the main sf::window
    sf::RenderWindow screen(sf::VideoMode(800, 600), "SFML window");

	//////////////////////TREE TESTING///////////////////////////////////
	std::cout << "Start of tree testing" << endl;
	string splitTest = "/hello/my/name/is/Andy/";
	std::vector<std::string> splitVecotr = split(splitTest, "/");
	printVector(splitVecotr);
	NodeState state;
	vector<string>treeCommands;
	treeCommands.push_back("/");
	state.setUp();
	treeCommands.clear();
	treeCommands.push_back("mkDir");
	treeCommands.push_back("testDir");
	fn_mkDir(state, treeCommands);
	treeCommands.clear();
	treeCommands.push_back("mkdir");
	treeCommands.push_back("/one/two/three/four/");
	fn_mkDir(state, treeCommands);
	treeCommands.clear();
	treeCommands.push_back("cd");
	treeCommands.push_back("one");
	fn_cd(state, treeCommands);
	treeCommands.clear();
	treeCommands.push_back("cd");
	treeCommands.push_back("two");
	fn_cd(state, treeCommands);
	treeCommands.clear();
	treeCommands.push_back("make");
	treeCommands.push_back("insideTwo");
	fn_mkfile(state, treeCommands);
	fn_ls(state, treeCommands);
	//printVector(treeCommands);
	std::cout << "End of tree testing" << endl;

	//////////////////////TREE TESTING//////////////////////////////////







    //Define a Sprite
    sf::Sprite S;
    sf::Texture T;
    if (!(T.loadFromFile(resourcePath() + "Wallpaper.png"))) {
        //Test for failure
        cerr << "COULD NOT LOAD\n";
        std::system("PAUSE");
        return -1;
    };
    S.setTexture(T);
    S.setPosition(0, 0);
    S.setScale(0.7f, 0.7f);
    

    sf::Image spriteSheet;
    spriteSheet.loadFromFile(resourcePath() + "Windows_UI.png");
    //Create A TestRenderSprite
    TestRenderSprite testRenderSpr(spriteSheet, 0, 3, 1);
	testRenderSpr.renderPosition(sf::Vector2f(10, 10));
    TestRenderSprite rend(spriteSheet, 0, 4, 1);
    rend.renderPosition(sf::Vector2f(170,0));
    
    //Put that Component into an Entity
    Entity testEntity;
    testEntity.addComponent(&testRenderSpr);
    testEntity.addComponent(&rend);
    

    //Create ppc::Window
    Window testWindow(200, 200,sf::Color(200,200,200));
	Window testWindow2(200, 200, sf::Color(150, 150, 150));
    //Add testEntity to ppc::Window
	testWindow.addEntity(testEntity);

	//Create ppc::Desktop
	char dummyTree = 't'; //using a dummy variable for Ctor until
	//the actual FileTree is completed
	Desktop myDesktop(dummyTree);
	myDesktop.addWindow(&testWindow);

    //////////JSON EXAMPLE//////////////////////////////////////////////

    Json::Reader reader;
    Json::Value value;
    // read from file, why can I just use the name dummy.json?
    ifstream doc(resourcePath() + "dummy.json", ifstream::binary);
    if (reader.parse(doc, value)){
        //outputting whole dummy doc
        cout << value << endl;
        //output value acquanted with my-encoding
        string out = value[ "my-encoding" ].asString();
        cout << out << endl;
        // create Json Array object from my-plug-ins
        const Json::Value arrayObj = value[ "my-plug-ins" ];
        for (unsigned int i = 0; i < arrayObj.size(); i++){
            //output each arrayObj
            cout << arrayObj[i].asString();
            if (i != arrayObj.size() - 1) { cout << endl; }
        }
    }
    cout << endl;
    //create json array from my-indent
    const Json::Value indentArray = value["my-indent"];
    //can make returned value int, bool, string, etc.
    cout << indentArray.get("length", "Not found").asInt() << endl;
    cout << indentArray.get("use_space", "Not found").asBool() << endl;
    string temp = value.get("Try to find me", "Not found" ).asString();
    cout << temp << endl;

    ///////////////////////////////////////////////////////////////////
	// Start the game loop
	///////////////////////////////////////////////////////////////////
	sf::Clock deltaTime; //define deltaTime
    //Used to keep track time
    sf::Time framePeriod = sf::milliseconds(1000.0f / 30.f);
    while (screen.isOpen()) {
        //Process sf::events
        sf::Event event;
        while (screen.pollEvent(event)) {
            // Close window: exit
            if (event.type == sf::Event::Closed)
				screen.close();
        }

        if (deltaTime.getElapsedTime() > framePeriod) {
            // Clear screen
			screen.clear(sf::Color::White);

            //Draw Background
			screen.draw(S);
            
            //Update all Windows in the Desktop
            sf::Time dt = deltaTime.restart();
            myDesktop.update(dt);

            //Draw all the Windows in the Desktop
			myDesktop.refresh();
			screen.draw(myDesktop);

            //Display final Window
			screen.display();
        }
    }
    return EXIT_SUCCESS;
}
