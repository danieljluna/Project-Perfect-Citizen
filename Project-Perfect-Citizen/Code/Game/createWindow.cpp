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
    buttonRenderComponent* textRenderComponent =
    new buttonRenderComponent(iconSheet, 0, 0, 1, 4);
    textRenderComponent->renderPosition(sf::Vector2f(0, 220));
    
    sf::Font myFont;
    myFont.loadFromFile(resourcePath() + "consola.ttf");
    int fontSize = 24;
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
    Entity* textBox = new Entity();
    textBox->addComponent(textInputBox);
    textBox->addComponent(tik);
    textBox->addComponent(cup);
    
    Entity* textDisplay = new Entity();
    textDisplay->addComponent(textDisplayBox);
    
    /////////////////////////////////////////
    /////// WINDOW CONSTRUCTION
    ///////////////////////////////////////
    windowToModify->setPosition(x, y);
    windowToModify->addEntity(*textBox);
    windowToModify->addEntity(*textDisplay);
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
    Entity* characterProfile = new Entity();
    characterProfile->addComponent(render);
    
    Entity* searchBoxEntity = new Entity();
    searchBoxEntity->addComponent(searchBox);
    searchBoxEntity->addComponent(dSI);
    
    Entity* resultsBoxEntity = new Entity();
    resultsBoxEntity->addComponent(searchResults);
    
    Entity backButton;
    spawnBackButton(backButton, ih, buttonSheet, 0, 0, 0.2f);
    
    /////////////////////////////////////////
    /////// WINDOW CONSTRUCTION
    ///////////////////////////////////////
    windowToModify->setPosition(x, y);
    windowToModify->addEntity(*searchBoxEntity);
    windowToModify->addEntity(*resultsBoxEntity);
    windowToModify->addEntity(*characterProfile);
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
    
    /* MARK: this is how you display the text in the blue box.
     Pass a reference of dataText to the thing thats making the PCG SMS
     stuff call this function, passing your string to this function.*/
    dataText->updateString("SMS MESSAGE\n\n { Ayy lmao }");
    
    /////////////////////////////////////////
    /////// ENTITIES
    ///////////////////////////////////////
    Entity* dataBox = new Entity();
    dataBox->addComponent(dataText);
    
    Entity* graphBox = new Entity();
    dataBox->addComponent(graphBounds);
    
    /////////////////////////////////////////
    /////// WINDOW CONSTRUCTION
    ///////////////////////////////////////
    windowToModify->addEntity(*dataBox);
    windowToModify->addEntity(*graphBox);
    windowToModify->setPosition(x, y);
    windowToModify = new BorderDecorator(*windowToModify);
    dynamic_cast<BorderDecorator*>(windowToModify)->addButton(buttonSheet, "localCloseButton");
}

void ppc::spawnFile(WindowInterface*& windowToModify, InputHandler & ih, NodeState & ns, sf::Image& buttonSheet, float x, float y) {
    if (windowToModify == nullptr) { return; }
    
    string path = resourcePath() + "Bluebird by Charles Bukowski.txt";
    char lastChar;
    
    if (!path.empty()){
        lastChar = *path.rbegin();
    }
    /////////////////////////////////////////
    /////// COMPONENTS & ENTITIES
    ///////////////////////////////////////
    sf::Image iconSheet;
    iconSheet.loadFromFile(resourcePath() + "Icon_Sheet.png");
    buttonRenderComponent* textRender =
        new buttonRenderComponent(iconSheet, 0, 0, 1, 4);
    textRender->renderPosition(sf::Vector2f(0, 220));
    
    Entity *newEnt = new Entity();
    
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
        newEnt->addComponent(textBox);
    }
    
    else if(lastChar == 'g'){
        sf::Image photo;
        photo.loadFromFile(path);
        photoRenderComponent* photoRender = new photoRenderComponent(photo);
        photoRender->setImageScale((float)windowToModify->getSize().x /
                               (float)photo.getSize().x,
                               (float)windowToModify->getSize().y /
                               (float)photo.getSize().y);
        newEnt->addComponent(photoRender);
    }
    
    /////////////////////////////////////////
    /////// WINDOW CONSTRUCTION
    ///////////////////////////////////////
    windowToModify->setPosition(x, y);
    windowToModify->addEntity(*newEnt);
    windowToModify = new BorderDecorator(*windowToModify);
    dynamic_cast<BorderDecorator*>(windowToModify)->addButton(buttonSheet, "localCloseButton");
    
}


