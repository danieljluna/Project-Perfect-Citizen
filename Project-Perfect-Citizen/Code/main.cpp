//Used to get XCODE working/////////////////////////////////

#ifdef WINDOWS_MARKER
    #define resourcePath() string()
#else
    #include "ResourcePath.hpp"
#endif

///////////////////////////////////////////////////////////

#include <SFML/Main.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Engine/renderSquare.h"
#include "Engine/testRenderSprite.h"
#include <iostream>
#include "Engine/testRotateSprite.h"
#include "Engine/subject.h"
#include "Engine/TestSubject.h"
#include "Engine/TestObserver.h"
#include "Engine/debug.h"
#include "Library/json/json.h"
#include <fstream>

using namespace std;
//Note that this is placeholder for now
int main(int argc, char** argv) {
	//Need this at very beginning
	Debug::scanOpts(argc, argv);
	//Example of using the debugger
	DEBUGF("ac", argc);

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

	ppc::RenderComponent* testSpriteTwo = new TestRenderSprite(
		resourcePath() + "kappa.png");
	ppc::RenderComponent* testSpriteThree = new TestRenderSprite(
		resourcePath() + "kappa.png");
	sf::RenderStates testRenderState;


	TestSubject* testChildSubject = new TestSubject();
	TestObserver* testChildObserver = new TestObserver();


	//Define a Sprite
	sf::Sprite S;
	sf::Texture T;
	T.loadFromFile(resourcePath() + "kappa.png");
	S.setTexture(T);
	S.setPosition(100, 100);
	S.setScale(0.2f, 0.2f);

	//Add the component to it
	testRotateSprite test(S, 1);
    // Start the game loop
	sf::Clock deltaTime; //define deltaTime
	sf::Time dt;
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
        for (int i = 0; i < arrayObj.size(); i++){
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
    ////////////////////////////////////////////////////////////////////
    while (window.isOpen()) {
		dt = deltaTime.restart();
        // Process events
		//sperate from ppc::event
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }
		//Update
		test.update(dt);

        // Clear screen
        window.clear();
		//testRect->render(&window);
		//going though the static renderVector inside component and 
		//calling class testRenderSprites' render function

		for (auto iter = ppc::RenderComponent::renderVector.begin(); 
			iter != ppc::RenderComponent::renderVector.end(); iter++) {
			//this line casts the (*iter) which is originally a base 
			//pointer of type RenderComponent into 
			//type TestRenderSprite*
			//http://www.cplusplus.com/forum/general/2710/
			//(dynamic_cast <TestRenderSprite*>(*iter))->draw(window, testRenderState);
			window.draw(**iter);
		}

		window.draw(S);
		//testSpriteTwo->draw(window, testRenderState);
        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}
