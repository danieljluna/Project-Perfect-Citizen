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
#include "../Engine/ScrollBarDeco.h"
#include "../Game/textOutputRenderComponent.h"
#include "../Game/databaseSearchRenderComponent.h"
#include "../Game/databaseSearchInputComponent.h"
#include "../Game/databaseDisplayRenderComponent.h"
#include "../Game/Inbox.h"
#include "../Game/errorMessageRenderComponent.h"
#include "../Game/Explorer.h"

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
#include "../Game/createListElement.h"
#include "../Game/emailExtraction.hpp"
#include "../Library/json/json.h"
#include"../Engine/TestFunctionClass.h"
#include"../Engine/FreeFunctionObserver.h"

using namespace ppc;

const string PNG = ".png";
const string JPG = ".jpg";
const string TXT = ".txt";

bool testBackFunction(TestFunctionClass* tfc, sf::Event& ev) {
	//tfc->callFunc(ev);
	return true;
}


void ppc::spawnConsole(Desktop& dt, WindowInterface*& windowToModify,
                       InputHandler & ih, NodeState & ns,
                       sf::Image& buttonSheet, float x, float y) {
    
    /* Check to make sure the window passed isn't null */
    if (windowToModify == nullptr) { return; }

	/* Reset the current directory to the root */
	ns.moveToRoot();
    
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
    int fontSize = 14;
    int windowOffset = 5;
    
    textInputRenderComponent* textInputBox =
    new textInputRenderComponent(ns, myFont, 0,
                                 windowToModify->getSize().y - (fontSize+windowOffset),
                                 fontSize);
    textOutputRenderComponent* textDisplayBox =
    new textOutputRenderComponent(dt, buttonSheet, myFont, ns, 0, 0, fontSize);
    
    
    
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
    sf::FloatRect viewRect = {
            0.0f,
            0.0f,
            float(windowToModify->getSize().x),
            float(windowToModify->getSize().y / 2)
    };
    windowToModify = new ScrollBarDecorator(*windowToModify, buttonSheet, sf::View(viewRect));
    windowToModify = new BorderDecorator(*windowToModify);
    dynamic_cast<BorderDecorator*>(windowToModify)->addButton(buttonSheet, closeWindow);    
    
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
    
    
    databaseDisplayRenderComponent* searchResults =
    new databaseDisplayRenderComponent(myFont, faceSheet, 0, fontSize + 5, fontSize - 10);
    
    
    /* Create the input components */
    databaseSearchRenderComponent* searchBox = new databaseSearchRenderComponent(myFont, 75, 0, fontSize);
    
    characterRender* render = new characterRender(faceSheet);
    float x1 =  static_cast<float>(windowToModify->getSize().x/2);
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
	//TODO FIX THIS
//    TestFunctionClass cool = new TestFunctionClass();

    spawnBackButton(dSI, backButton, ih, buttonSheet, 0, 0, 0.2f);
    
    /////////////////////////////////////////
    /////// WINDOW CONSTRUCTION
    ///////////////////////////////////////
    windowToModify->setPosition(x, y);
    windowToModify->addEntity(searchBoxEntity);
    windowToModify->addEntity(resultsBoxEntity);
    windowToModify->addEntity(characterProfile);
    windowToModify->addEntity(backButton);
    windowToModify = new BorderDecorator(*windowToModify);
    dynamic_cast<BorderDecorator*>(windowToModify)->addButton(buttonSheet, closeWindow);
}

void ppc::spawnPipeline(WindowInterface*& windowToModify, InputHandler& ih, Database* db,
	sf::Image& buttonSheet, float x, float y) {
	if (windowToModify == nullptr) { return; }

	sf::Font myFont;
	myFont.loadFromFile(resourcePath() + "consola.ttf");
	int fontSize = 14;
	int dataWindowX = (2 * windowToModify->getSize().x) / 3;

	/////////////////////////////////////////
	/////// COMPONENTS 
	///////////////////////////////////////

	/* Create the render components */
	PipelineDataRenderComponent* dataText = new PipelineDataRenderComponent(myFont, 
		dataWindowX, 0, fontSize, windowToModify->getSize().x, windowToModify->getSize().y);

	PipelineGraphRenderComponent* graphBounds = new PipelineGraphRenderComponent(0, 0, dataWindowX,
		windowToModify->getSize().y);
    

    Network* solNet = PipelineLevelBuilder::buildLevelOneNetworkSolution();
	Network* playNet = solNet->copyNetworkByVerts();
	playNet->setCenter(-1);

	std::vector<int> indexVec {0, 1, 2, 3, 4, 5, 6, 7};
	std::random_shuffle(indexVec.begin(), indexVec.end());
	//No Overlapping Edges (Think of this positioning as an 8x8 grid
	//the number after the * is the row/column number)
	playNet->vert(indexVec[0]).setPosition(50 + 50 * 0, 50 + 50 * 0);
	playNet->vert(indexVec[1]).setPosition(50 + 50 * 0, 50 + 50 * 7);
	playNet->vert(indexVec[2]).setPosition(50 + 50 * 2, 50 + 50 * 1);
	playNet->vert(indexVec[3]).setPosition(50 + 50 * 2, 50 + 50 * 6);
	playNet->vert(indexVec[4]).setPosition(50 + 50 * 5, 50 + 50 * 1);
	playNet->vert(indexVec[5]).setPosition(50 + 50 * 5, 50 + 50 * 6);
	playNet->vert(indexVec[6]).setPosition(50 + 50 * 7, 50 + 50 * 0);
	playNet->vert(indexVec[7]).setPosition(50 + 50 * 7, 50 + 50 * 7);

	NetworkRenderComponent* networkRender = 
		new NetworkRenderComponent(*playNet);
	NetworkInputCmpnt* networkInput = 
		new NetworkInputCmpnt(*playNet, *solNet, windowToModify->getInputHandler());
	//Always need to call this setter.
	networkInput->setPipelineData(*dataText);
    sf::FloatRect temp = graphBounds->getLocalBounds();
    temp.width -= 60;
    temp.height -= 60;
    networkInput->setClampBounds(temp);
	
	/////////////////////////////////////////
	/////// ENTITIES 
	///////////////////////////////////////
	Entity dataBox;
	dataBox.addComponent(dataText);


	Entity graphBox;
	graphBox.addComponent(graphBounds);
	graphBox.addComponent(networkRender);
	graphBox.addComponent(networkInput);

	Entity submitButton;
	float buttonScale = 0.25f;
	int buttonSize = 256;
	spawnNetworkOkayButton(playNet,submitButton, windowToModify->getInputHandler(), buttonSheet, 
		( ( graphBounds->getLocalBounds().width - (buttonSize * buttonScale) ) / 2 ), static_cast<float>(windowToModify->getSize().y-50), buttonScale);
	/////////////////////////////////////////
	/////// WINDOW CONSTRUCTION
	///////////////////////////////////////
	windowToModify->addEntity(dataBox);
	windowToModify->addEntity(graphBox);
	windowToModify->addEntity(submitButton);
	windowToModify->setPosition(x, y);
	windowToModify = new BorderDecorator(*windowToModify);
	dynamic_cast<BorderDecorator*>(windowToModify)->addButton(buttonSheet, closeWindow);

}

void ppc::spawnFile(WindowInterface*& windowToModify, InputHandler & ih, NodeState & ns, sf::Image& buttonSheet, float x, float y, string p) {
    if (windowToModify == nullptr) { return; }
    
    string path = resourcePath() + p;
    string dotEnd;
    
    if (!path.empty()){
        dotEnd = path.substr(path.length() - 4);
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
    
    if(dotEnd == TXT){
        sf::Font myFont;
        myFont.loadFromFile(resourcePath() + "consola.ttf");
        int fontSize = 20;
        int windowOffset = 5;
        
        int textMuliplier = 23;
        int maxWindowScroll = 16284;
        int maxWindowLines = 700;
        int windowScrollHeight = 0;
        ifstream f(path);
        std::string line;
        string content;
        while (std::getline(f, line)){
            if(windowScrollHeight < maxWindowLines){
                ++windowScrollHeight;
                content += line + "\n";
            }
            else if(windowScrollHeight > maxWindowLines){
                break;
            }
        }

        windowScrollHeight = windowScrollHeight * textMuliplier;
        if(windowScrollHeight > maxWindowScroll){
            windowScrollHeight = maxWindowScroll;
        }
        
        textRenderComponent* textBox =
            new textRenderComponent(myFont, content, 0, 0, fontSize);
        
        newEnt.addComponent(textBox);
        
        windowToModify->setSize(windowToModify->getSize().x, windowScrollHeight);
        sf::FloatRect viewRect = {
            0.0f,
            0.0f,
            float(windowToModify->getSize().x),
            float(windowToModify->getSize().x)
        };
        windowToModify = new ScrollBarDecorator(*windowToModify, buttonSheet, sf::View(viewRect));
    }
    
    else if(dotEnd == PNG || dotEnd == JPG){
        sf::Image photo;
        photo.loadFromFile(path);
        windowToModify->setSize(photo.getSize().x/2, photo.getSize().y/2);
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
    dynamic_cast<BorderDecorator*>(windowToModify)->addButton(buttonSheet, closeWindow);
}

void ppc::spawnInbox(Desktop& dT, WindowInterface*& windowToModify, InputHandler& ih, sf::Image& buttonSheet, float x, float y, Inbox& inbox) {
	/* Check to make sure the window passed isn't null */
	if (windowToModify == nullptr) { return; }

	sf::Font myFont;
	myFont.loadFromFile(resourcePath() + "consola.ttf");
	int fontSize = 20;
	int windowOffset = 5;
	int emailBoxElementWidth = windowToModify->getSize().x;
	int emailBoxElementHeight = 50;
	int emailBoxPadding = 25;
    
	int totalEmailsLoaded = 0;
	/////////////////////////////////////////
	/////// ENTITIES
	///////////////////////////////////////
	/* Create an email list element entity for each email in the inbox*/
	for (int i = 0; i < inbox.getInboxSize(); ++i) {
		Entity emailListElement;
        createEmailListElement(
			emailListElement, dT, buttonSheet, ih, myFont, inbox.getEmailAt(i), 0, (i * (emailBoxElementHeight+emailBoxPadding)),
			emailBoxElementWidth, emailBoxElementHeight, 0, static_cast<int>((i * (1.5*emailBoxElementHeight))), fontSize);
		windowToModify->addEntity(emailListElement);
		++totalEmailsLoaded;
	}

	int newHeight = (totalEmailsLoaded) * (emailBoxElementHeight + emailBoxPadding);
	int newWidth = windowToModify->getSize().x;
	windowToModify->setSize(newWidth, newHeight);

	/////////////////////////////////////////
	/////// WINDOW CONSTRUCTION
	///////////////////////////////////////

	/*sf::FloatRect viewRect = {
		0.0f,
		0.0f,
		float(windowToModify->getSize().x),
		float(windowToModify->getSize().y / 2)
	};
	windowToModify = new ScrollBarDecorator(*windowToModify, buttonSheet, sf::View(viewRect));*/
	windowToModify = new BorderDecorator(*windowToModify);
	windowToModify->setPosition(x, y);
	dynamic_cast<BorderDecorator*>(windowToModify)->addButton(buttonSheet, closeWindow);

}
void ppc::spawnEmailMessage(WindowInterface*& windowToModify, InputHandler& ih, Email& mail, sf::Image& buttonSheet, float x, float y) {
	/* Check to make sure the window passed isn't null */
	if (windowToModify == nullptr) { return; }

	/////////////////////////////////////////
	/////// COMPONENTS
	///////////////////////////////////////
	
	sf::Font myFont;
	myFont.loadFromFile(resourcePath() + "consola.ttf");
	int fontSize = 20;

	emailMessageRenderComponent* eMRC = new emailMessageRenderComponent(myFont, mail, 0, 0, fontSize);

	/////////////////////////////////////////
	/////// ENTITIES
	///////////////////////////////////////
	Entity emailMessageDisplayBox;
	emailMessageDisplayBox.addComponent(eMRC);
	/////////////////////////////////////////
	/////// WINDOW CONSTRUCTION
	///////////////////////////////////////
    string content = mail.getContentField();
    int lineCount = 1;
    int lineMultiplier = 23;
    int preLineCount = 6;
    for (unsigned int i = 0; i < content.size(); i++){
        if (content[i] == '\n') {
            lineCount++;
        }
    }
    lineCount += preLineCount;
    lineCount = lineCount*lineMultiplier;
    
    windowToModify->setSize(windowToModify->getSize().x, lineCount);
    if(static_cast<unsigned int>(lineCount) > windowToModify->getSize().x){
        sf::FloatRect viewRect = {
            0.0f,
            0.0f,
            float(windowToModify->getSize().x),
            float(windowToModify->getSize().x)
        };
        windowToModify = new ScrollBarDecorator(*windowToModify, buttonSheet, sf::View(viewRect));
    }
	windowToModify->addEntity(emailMessageDisplayBox);
	windowToModify->setPosition(x, y);
	windowToModify = new BorderDecorator(*windowToModify);
	dynamic_cast<BorderDecorator*>(windowToModify)->addButton(buttonSheet, closeWindow);
}


void ppc::spawnErrorMessage(WindowInterface*& windowToModify, InputHandler& ih, sf::Image& buttonSheet, float x, float y, std::string message) {
	/* Check to make sure the window passed isn't null */
	if (windowToModify == nullptr) { return; }

	/////////////////////////////////////////
	/////// COMPONENTS
	///////////////////////////////////////

	sf::Font myFont;
	myFont.loadFromFile(resourcePath() + "consola.ttf");
	int fontSize = 14;

	errorMessageRenderComponent* eMRC = new errorMessageRenderComponent(myFont, message, 
		windowToModify->getSize().x/3, windowToModify->getSize().y/3, fontSize);


	/////////////////////////////////////////
	/////// ENTITIES
	///////////////////////////////////////
	Entity alertIcon;
	float alertScale = 0.5f;
	float alertWidth = 128.0;
	float windowWidth = static_cast<float>(windowToModify->getSize().x);
	float windowHeight = static_cast<float>(windowToModify->getSize().y);
	float alertX = windowWidth - ((alertWidth * alertScale) + (3 * (windowWidth / 4)));
	float alertY = (windowHeight - (alertWidth * alertScale)) / 3;
	spawnAlertIcon(alertIcon, ih, buttonSheet, alertX, alertY, 0.5f);

	Entity errorMessageDisplayBox;
	errorMessageDisplayBox.addComponent(eMRC);

	/////////////////////////////////////////
	/////// WINDOW CONSTRUCTION
	///////////////////////////////////////
	windowToModify->addEntity(errorMessageDisplayBox);
	windowToModify->addEntity(alertIcon);
	windowToModify->setPosition(x, y);
	windowToModify = new BorderDecorator(*windowToModify);
	dynamic_cast<BorderDecorator*>(windowToModify)->addButton(buttonSheet, closeWindow);
}

void ppc::spawnExplorer(Desktop& dt, WindowInterface*& windowToModify, InputHandler& ih, NodeState& ns,
	sf::Image& buttonSheet, sf::Image& iconSheet, float x, float y) {
	/* Check to make sure the window passed isn't null */
	if (windowToModify == nullptr) { return; }

	/////////////////////////////////////////
	/////// COMPONENTS
	///////////////////////////////////////

	sf::Font myFont;
	myFont.loadFromFile(resourcePath() + "consola.ttf");
	int fontSize = 14;

	Explorer theExplorer(dt, windowToModify, ns, buttonSheet, iconSheet);

	/////////////////////////////////////////
	/////// ENTITIES
	///////////////////////////////////////
	

	/////////////////////////////////////////
	/////// WINDOW CONSTRUCTION
	///////////////////////////////////////

	windowToModify->setPosition(x, y);
	windowToModify = new BorderDecorator(*windowToModify);
	dynamic_cast<BorderDecorator*>(windowToModify)->addButton(buttonSheet, closeWindow);
}


