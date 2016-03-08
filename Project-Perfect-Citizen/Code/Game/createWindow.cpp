#ifdef WINDOWS_MARKER
#define resourcePath() string("Resources/")
#else
#include "ResourcePath.hpp"
#endif

#include "createWindow.h"

#include <iostream>
#include <fstream>
#include <SFML/Main.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <sstream>

#include "../Engine/Window.h"
#include "buttonRenderComponent.h"
#include "consoleUpdateComponent.h"
#include "../Engine/inputComponent.h"
#include "../Engine/InputHandler.h"
#include "../Engine/Entity.h"
#include "../Engine/subject.h"
#include "textInputRenderComponent.hpp"
#include "textInputKeys.hpp"
#include "../Engine/BorderDecorator.h"
#include "../Game/textOutputRenderComponent.h"
#include "../Game/databaseSearchRenderComponent.h"
#include "../Game/databaseSearchInputComponent.h"
#include "../Game/databaseDisplayRenderComponent.h"

#include "../Engine/debug.h"
#include "../Game/characterRender.hpp"

#include "../Game/PipelineDataRenderComponent.h"
#include "../Game/PipelineGraphRenderComponent.h"
#include "../Game/photoRenderComponent.hpp"
#include "textRenderComponent.hpp"

#include "../Game/NetworkRenderCmpnt.h"
#include"../Game/NetworkInputCmpnt.h"
#include"../Game/NetworkUpdateCmpnt.h"
#include"../Game/PipelineLevelBuilder.h"
using namespace ppc;


void ppc::spawnConsole(WindowInterface*& windowToModify,
                       InputHandler & ih, NodeState & ns,
                       sf::Image& buttonSheet, float x, float y) {
    
    /* Check to make sure the window passed isn't null */
    if (windowToModify == nullptr) { return; }
    
    /////////////////////////////////////////
    /////// COMPONENTS
    ///////////////////////////////////////
    /* Create the render components */
    sf::Image iconSheet;
    iconSheet.loadFromFile(resourcePath() + "Icon_Sheet.png");
    //sf::Image buttonSheet;
    //buttonSheet.loadFromFile(resourcePath() + "Windows_UI.png");
    
    
    sf::Font myFont;
    myFont.loadFromFile(resourcePath() + "consola.ttf");
    int fontSize = 20;
    int windowOffset = 5;
    
    textInputRenderComponent* textInputBox =
    new textInputRenderComponent(ns, myFont, 0,
                                 windowToModify->getSize().y - (fontSize+windowOffset),
                                 fontSize);
    textOutputRenderComponent* textDisplayBox =
    new textOutputRenderComponent(myFont, ns, 0, 0, fontSize);
    
    
    
    /* Create the update component */
    consoleUpdateComponent* cup = new consoleUpdateComponent(ns);
    
    /* Create the input components */
    textInputKeys* tik = new textInputKeys(ih, *textInputBox,
                                           *textDisplayBox, *cup);
    
    /////////////////////////////////////////
    /////// ENTITIES
    ///////////////////////////////////////
    Entity textBox;
    textBox.addComponent(textInputBox);
   // textBox.addComponent(textRenderComponent);
    textBox.addComponent(tik);
    textBox.addComponent(cup);
    
    Entity textDisplay;
    textDisplay.addComponent(textDisplayBox);
    
    /////////////////////////////////////////
    /////// WINDOW CONSTRUCTION
    ///////////////////////////////////////
    windowToModify->setPosition(x, y);
    windowToModify->addEntity(textBox);
    windowToModify->addEntity(textDisplay);
    windowToModify = new BorderDecorator(*windowToModify);
    dynamic_cast<BorderDecorator*>(windowToModify)->addButton(buttonSheet, "localCloseButton");
    
}

void ppc::spawnDatabase(WindowInterface*& windowToModify, InputHandler& ih, Database* db,
                        sf::Image& buttonSheet, float x, float y) {
    /* Check to make sure the window passed isn't null */
    if (windowToModify == nullptr) { return; }
    
    /////////////////////////////////////////
    /////// COMPONENTS
    ///////////////////////////////////////
    sf::Font myFont;
    myFont.loadFromFile(resourcePath() + "consola.ttf");
    int fontSize = 20;
    int windowOffset = 5;
    
    /* Create the render components */
    sf::Image iconSheet;
    iconSheet.loadFromFile(resourcePath() + "Icon_Sheet.png");
    
    sf::Image faceSheet;
    faceSheet.loadFromFile(resourcePath() + "Face_Sheet.png");
    
    
    // We probably do not need these
    
   /* buttonRenderComponent* textRenderComponent =
    new buttonRenderComponent(iconSheet, 0, 0, 1, 4);
    textRenderComponent->renderPosition(sf::Vector2f(0, 220));*/
    
    
    databaseDisplayRenderComponent* searchResults =
    new databaseDisplayRenderComponent(myFont, faceSheet, 0, fontSize + 5, fontSize - 10);
    
    
    /* Create the input components */
    databaseSearchRenderComponent* searchBox = new databaseSearchRenderComponent(myFont, 75, 0, fontSize);
    
    /*databaseSearchRenderComponent* searchBox = new databaseSearchRenderComponent(myFont, 0,
     windowToModify->getSize().y - (fontSize + windowOffset),
     fontSize);*/
    
    characterRender* render = new characterRender(faceSheet);
    float x1 =  windowToModify->getSize().x/2;
    render->setOrigin(x1, 100);
    /* Create the update components */
    
    /* Create the input components */
    databaseSearchInputComponent* dSI = new databaseSearchInputComponent(db, ih, *searchBox, *searchResults,
                                                                          *render);
    
    
    
    /////////////////////////////////////////
    /////// ENTITIES
    ///////////////////////////////////////
    Entity characterProfile;
    characterProfile.addComponent(render);
    
    Entity searchBoxEntity;
    searchBoxEntity.addComponent(searchBox);
    searchBoxEntity.addComponent(dSI);
    
    Entity resultsBoxEntity;
    resultsBoxEntity.addComponent(searchResults);

    Entity backButton;
    spawnBackButton(backButton, ih, buttonSheet, 0, 0, 0.2f);
    
    /////////////////////////////////////////
    /////// WINDOW CONSTRUCTION
    ///////////////////////////////////////
    windowToModify->setPosition(x, y);
    windowToModify->addEntity(searchBoxEntity);
    windowToModify->addEntity(resultsBoxEntity);
    windowToModify->addEntity(characterProfile);
    windowToModify->addEntity(backButton);
    windowToModify = new BorderDecorator(*windowToModify);
    dynamic_cast<BorderDecorator*>(windowToModify)->addButton(buttonSheet, "localCloseButton");
}

void ppc::spawnPipeline(WindowInterface*& windowToModify, InputHandler& ih, Database* db,
	sf::Image& buttonSheet, float x, float y) {
	if (windowToModify == nullptr) { return; }

	sf::Font myFont;
	myFont.loadFromFile(resourcePath() + "consola.ttf");
	int fontSize = 20;
	int dataWindowX = (2 * windowToModify->getSize().x) / 3;

	/////////////////////////////////////////
	/////// COMPONENTS 
	///////////////////////////////////////

	/* Create the render components */
	PipelineDataRenderComponent* dataText = new PipelineDataRenderComponent(myFont, 
		dataWindowX, 0, fontSize, windowToModify->getSize().x, windowToModify->getSize().y);

	PipelineGraphRenderComponent* graphBounds = new PipelineGraphRenderComponent(0, 0, dataWindowX,
		windowToModify->getSize().y);
    
    Network* net = PipelineLevelBuilder::buildLevelOneNetworkSolution();

	//No Overlapping Edges (Think of this positioning as an 8x8 grid
	//the number after the * is the row/column number)
	net->vert(0).setPosition(50 + 50 * 0, 50 + 50 * 0);
	net->vert(1).setPosition(50 + 50 * 0, 50 + 50 * 7);
	net->vert(2).setPosition(50 + 50 * 2, 50 + 50 * 1);
	net->vert(3).setPosition(50 + 50 * 2, 50 + 50 * 6);
	net->vert(4).setPosition(50 + 50 * 5, 50 + 50 * 1);
	net->vert(5).setPosition(50 + 50 * 5, 50 + 50 * 6);
	net->vert(6).setPosition(50 + 50 * 7, 50 + 50 * 0);
	net->vert(7).setPosition(50 + 50 * 7, 50 + 50 * 7);

	NetworkRenderComponent* networkRender = new NetworkRenderComponent(*net);
	NetworkInputCmpnt* networkInput = new NetworkInputCmpnt(*net, windowToModify->getInputHandler());
	networkInput->setPipelineData(*dataText);
	NetworkUpdateCmpnt* networkUpdate = new NetworkUpdateCmpnt(*net);
	networkUpdate->setBounds(graphBounds->getLocalBounds());
	networkUpdate->setDrags(networkInput->getDraggables());
	
    int somevert = std::rand() % 8;
	for (unsigned int i = 0; i < net->size(); ++i) {
		if (net->isAdjacent(somevert, i)) {
			std::vector<std::string> smsvec = net->edge(somevert, i)->getSmsData();
			
			for (unsigned int j = 0; j < smsvec.size(); ++j) {
				dataText->appendString(smsvec[j] + "\n\n");
			}
		}
	}
	/////////////////////////////////////////
	/////// ENTITIES 
	///////////////////////////////////////
	Entity dataBox;
	dataBox.addComponent(dataText);


	Entity graphBox;
	graphBox.addComponent(graphBounds);
	graphBox.addComponent(networkRender);
	graphBox.addComponent(networkInput);
	graphBox.addComponent(networkUpdate);
	/////////////////////////////////////////
	/////// WINDOW CONSTRUCTION
	///////////////////////////////////////
	windowToModify->addEntity(dataBox);
	windowToModify->addEntity(graphBox);
	windowToModify->setPosition(x, y);
	windowToModify = new BorderDecorator(*windowToModify);
	dynamic_cast<BorderDecorator*>(windowToModify)->addButton(buttonSheet, "localCloseButton");

}

void ppc::spawnFile(WindowInterface*& windowToModify, InputHandler & ih, NodeState & ns, sf::Image& buttonSheet, float x, float y, string p) {
    if (windowToModify == nullptr) { return; }
    
    string path = resourcePath() + p;
    char lastChar;
    
    if (!path.empty()){
        lastChar = *path.rbegin();
    }
    /////////////////////////////////////////
    /////// COMPONENTS & ENTITIES
    ///////////////////////////////////////
    sf::Image iconSheet;
    iconSheet.loadFromFile(resourcePath() + "Icon_Sheet.png");

   /*buttonRenderComponent* textRenderComponent =
    new buttonRenderComponent(iconSheet, 0, 0, 1, 4);
    textRenderComponent->renderPosition(sf::Vector2f(0, 220));*/
    
    Entity newEnt;
    
    if(lastChar == 't'){
        sf::Font myFont;
        myFont.loadFromFile(resourcePath() + "consola.ttf");
        int fontSize = 10;
        int windowOffset = 5;
        ifstream t(path);
        stringstream buffer;
        buffer << t.rdbuf();
        string content = buffer.str();
        textRenderComponent* textBox =
            new textRenderComponent(myFont, content, 0, 0, fontSize);
        newEnt.addComponent(textBox);
    }
    
    else if(lastChar == 'g'){
        sf::Image photo;
        photo.loadFromFile(path);
        photoRenderComponent* photoRender = new photoRenderComponent(photo);
        photoRender->setImageScale((float)windowToModify->getSize().x /
                               (float)photo.getSize().x,
                               (float)windowToModify->getSize().y /
                               (float)photo.getSize().y);
        newEnt.addComponent(photoRender);
    }
    
    /////////////////////////////////////////
    /////// WINDOW CONSTRUCTION
    ///////////////////////////////////////
    windowToModify->setPosition(x, y);
    windowToModify->addEntity(newEnt);
    windowToModify = new BorderDecorator(*windowToModify);
    dynamic_cast<BorderDecorator*>(windowToModify)->addButton(buttonSheet, "localCloseButton");
}


