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

#include "../Game/NetworkRenderCmpnt.h"
#include"../Game/NetworkInputCmpnt.h"

using namespace ppc;


void ppc::spawnConsole(WindowInterface*& windowToModify,
                       InputHandler & ih, NodeState & ns,
                       sf::Image& buttonSheet, float x, float y) {
    
    /* Check to make sure the window passed isn't null */
    if (windowToModify == nullptr) { return; }

	ns.getDirString();
    
    /////////////////////////////////////////
    /////// COMPONENTS
    ///////////////////////////////////////
    /* Create the render components */
    sf::Image iconSheet;
    iconSheet.loadFromFile(resourcePath() + "Icon_Sheet.png");
    //sf::Image buttonSheet;
    //buttonSheet.loadFromFile(resourcePath() + "Windows_UI.png");
    buttonRenderComponent* textRenderComponent =
    new buttonRenderComponent(iconSheet, 0, 0, 1, 4);
    textRenderComponent->renderPosition(sf::Vector2f(0, 220));
    
    sf::Font myFont;
    myFont.loadFromFile(resourcePath() + "consola.ttf");
    int fontSize = 20;
    int windowOffset = 5;
    
    textInputRenderComponent* textInputBox =
    new textInputRenderComponent(myFont, 0,
                                 windowToModify->getSize().y - (fontSize+windowOffset),
                                 fontSize);
    textOutputRenderComponent* textDisplayBox =
    new textOutputRenderComponent(myFont, ns, 0, 0, fontSize);
    
    /* Create the update component */
    consoleUpdateComponent* cup = new consoleUpdateComponent(ns);
    
    /* Create the input components */
    textInputKeys* tik = new textInputKeys(ih,
                                           *textRenderComponent->getSprite(), *textInputBox,
                                           *textDisplayBox, *cup);
    
    /////////////////////////////////////////
    /////// ENTITIES
    ///////////////////////////////////////
    Entity textBox;
    textBox.addComponent(textInputBox);
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
    buttonRenderComponent* textRenderComponent =
    new buttonRenderComponent(iconSheet, 0, 0, 1, 4);
    textRenderComponent->renderPosition(sf::Vector2f(0, 220));
    
    
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
                                                                         *textRenderComponent->getSprite(), *render);
    
    
    
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
	//bool (databaseSearchInputComponent::*backFunction)(sf::Event&); 
	//backFunction = &databaseSearchInputComponent::goBack;
	//dSI->*backFunction;
	//goBack f = &databaseSearchInputComponent::goBack;
	//backFunction bFunc = dSI->goBack;
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

	/* NADER: PUT YOUR RENDER COMPONENTS HERE FOR THE GRAPH */
	//Ask about how are we making networks to be added to the pipeline window.
	Network* net = new Network(3);

	PipelineCharacter Bob;
	PipelineCharacter Tim;
	PipelineCharacter Rob;

	net->vert(0).setCharacter(Bob);
	net->vert(1).setCharacter(Tim);
	net->vert(2).setCharacter(Rob);
	net->vert(0).setPosition(100, 50);
	net->vert(1).setPosition(150, 150);
	net->vert(2).setPosition(200, 300);

	Edge e1, e2;
	e1.setColorRed();
	e2.setColorGreen();
	e1.setWeight(1);
	e1.setRelation("");

	net->setEdge(0, 1, e1);
	net->setEdge(1, 2, e2);

	NetworkRenderComponent* networkRender = new NetworkRenderComponent(*net);
	NetworkInputCmpnt* networkInput = new NetworkInputCmpnt(*net, windowToModify->getInputHandler());
	/* MARK: this is how you display the text in the blue box. 
	Pass a reference of dataText to the thing thats making the PCG SMS
	stuff call this function, passing your string to this function.*/
	dataText->updateString("SMS MESSAGE\n\n { Ayy lmao }");

	/////////////////////////////////////////
	/////// ENTITIES 
	///////////////////////////////////////
	Entity dataBox;
	dataBox.addComponent(dataText);

	Entity graphBox;
	graphBox.addComponent(graphBounds);
	graphBox.addComponent(networkRender);
	graphBox.addComponent(networkInput);
	/////////////////////////////////////////
	/////// WINDOW CONSTRUCTION
	///////////////////////////////////////
	windowToModify->addEntity(dataBox);
	windowToModify->addEntity(graphBox);
	windowToModify->setPosition(x, y);
	windowToModify = new BorderDecorator(*windowToModify);
	dynamic_cast<BorderDecorator*>(windowToModify)->addButton(buttonSheet, "localCloseButton");

}

void ppc::spawnFile(WindowInterface*& windowToModify, InputHandler & ih, NodeState & ns, sf::Image& buttonSheet, float x, float y) {
    if (windowToModify == nullptr) { return; }
    
    /////////////////////////////////////////
    /////// COMPONENTS
    ///////////////////////////////////////
    sf::Image iconSheet;
    iconSheet.loadFromFile(resourcePath() + "Icon_Sheet.png");
    buttonRenderComponent* textRenderComponent =
    new buttonRenderComponent(iconSheet, 0, 0, 1, 4);
    textRenderComponent->renderPosition(sf::Vector2f(0, 220));
    
    sf::Image photo;
    photo.loadFromFile(resourcePath() + "kappa.png");
    photoRenderComponent* photoRender = new photoRenderComponent(photo);
    photoRender->setImageScale((float)windowToModify->getSize().x /
                               (float)photo.getSize().x,
                               (float)windowToModify->getSize().y /
                               (float)photo.getSize().y);
    
    /////////////////////////////////////////
    /////// ENTITIES
    ///////////////////////////////////////
    Entity newEnt;
    newEnt.addComponent(photoRender);
    
    /////////////////////////////////////////
    /////// WINDOW CONSTRUCTION
    ///////////////////////////////////////
    windowToModify->setPosition(x, y);
    windowToModify->addEntity(newEnt);
    windowToModify = new BorderDecorator(*windowToModify);
    dynamic_cast<BorderDecorator*>(windowToModify)->addButton(buttonSheet, "localCloseButton");
}


