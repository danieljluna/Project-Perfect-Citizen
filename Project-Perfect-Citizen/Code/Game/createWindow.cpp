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

#include "../Engine/World.h"
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
#include "NetworkCheckFunctor.h"

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
#include"../Engine/FreeFunctionObserver.h"

#include "../Game/ButtonBuilder.h"
#include "../Game/TextDisplayBuilder.h"

#include "../Game/TextBoxBuilder.h"

#include "../Game/HelpRenderComponent.hpp"

using namespace ppc;

const string PNG = ".png";
const string JPG = ".jpg";
const string TXT = ".txt";

void ppc::spawnConsole(Desktop& dt, WindowInterface*& windowToModify,
                       InputHandler & ih, NodeState ns,
                       sf::Image& buttonSheet, float x, float y) {
    if (windowToModify == nullptr) { return; }
	ns.moveToRoot();
    
    /////////////////////////////////////////
    /////// COMPONENTS
    ///////////////////////////////////////
    /* Create the render components */
    sf::Image iconSheet;
    iconSheet.loadFromFile(resourcePath() + "Icon_Sheet.png");
   
    sf::Font myFont;
    myFont.loadFromFile(resourcePath() + "consola.ttf");
    int fontSize = 14;
    int windowOffset = 5;
    
    textInputRenderComponent* textInputBox =
    new textInputRenderComponent(ns, myFont, 0, 0, fontSize);
    textOutputRenderComponent* textDisplayBox =
    new textOutputRenderComponent(dt, windowToModify, buttonSheet, myFont, ns,
		textInputBox, 0, 0, fontSize);
    
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
    BorderDecorator* border = dynamic_cast<BorderDecorator*>(windowToModify);
    border->addButton(buttonSheet, closeWindow);    
    border->setCaption("Console");
    
}

void ppc::spawnDatabase(WindowInterface*& windowToModify, InputHandler& ih, Database* db,
                        sf::Image& buttonSheet, float x, float y) {
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
    
    
    Entity tbox;
    TextBoxBuilder tbuilder;
    tbuilder.setPosition(sf::Vector2f(200,200));
    sf::Font thefont;
    thefont.loadFromFile(resourcePath() + "consola.ttf");
    tbuilder.setFont(thefont);
    tbuilder.setString("text box");
    tbuilder.setSize(12);
    tbuilder.setColor(sf::Color::Black);
    tbuilder.setInputHandle(ih);
    tbuilder.create(tbox);

    
    /////////////////////////////////////////
    /////// WINDOW CONSTRUCTION
    ///////////////////////////////////////
    windowToModify->setPosition(x, y);
    windowToModify->addEntity(tbox);
    windowToModify->addEntity(searchBoxEntity);
    windowToModify->addEntity(resultsBoxEntity);
    windowToModify->addEntity(characterProfile);
    windowToModify->addEntity(backButton);
 
    windowToModify = new BorderDecorator(*windowToModify);
    dynamic_cast<BorderDecorator*>(windowToModify)->addButton(buttonSheet, closeWindow);
	dynamic_cast<BorderDecorator*>(windowToModify)->setCaption("DCPS Database v.2.4528");
}


void ppc::spawnHelp(WindowInterface*& windowToModify, InputHandler& ih,
                        sf::Image& buttonSheet, float x, float y) {
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
    
    
    Entity help;
    HelpWindowRenderComponent* helpText1 = new HelpWindowRenderComponent(myFont,30,90,16);
    help.addComponent(helpText1);

    
    Entity tab0;
    Entity tab1;
    

    // Button Test
    ButtonBuilder builder;
    builder.setButtonPosition(sf::Vector2f(16, 16));
    builder.setInputHandle(ih);
    builder.setSize(0.25f);
    builder.setSpriteSheet(buttonSheet);
    builder.setLabelMessage("Console");
    builder.setLabelFont(myFont);
    builder.setLabelSize(12);

    builder.create(tab0);
    createWithEventFunc(builder, tab0, helpText1, swithTab0Fn);

    builder.setButtonPosition(sf::Vector2f(128,16));
    builder.setLabelMessage("Graph");

    builder.create(tab1);
    createWithEventFunc(builder, tab1, helpText1, swithTab1Fn);

    
    /////////////////////////////////////////
    /////// ENTITIES
    ///////////////////////////////////////
   
    
    
    

//   sf::Font& f, std::string str, int x, int y, int size
    /////////////////////////////////////////
    /////// WINDOW CONSTRUCTION
    ///////////////////////////////////////
    windowToModify->setPosition(x, y);
    windowToModify->addEntity(tab0);
    windowToModify->addEntity(tab1);
    windowToModify->addEntity(help);
    
    windowToModify = new BorderDecorator(*windowToModify);
    dynamic_cast<BorderDecorator*>(windowToModify)->addButton(buttonSheet, closeWindow);
}


void ppc::spawnPipeline(WindowInterface*& windowToModify, InputHandler& ih, Database* db,
	sf::Image& buttonSheet, float x, float y) {
	if (windowToModify == nullptr) { return; }

	sf::Font myFont;
	myFont.loadFromFile(resourcePath() + "consola.ttf");
	int fontSize = 14;
	float dataWindowX = float(2 * windowToModify->getSize().x) / 3.0f;

	/////////////////////////////////////////
	/////// COMPONENTS 
	/////////////////////////////////////////

	/* Create the render components */
	PipelineDataRenderComponent* dataText = new PipelineDataRenderComponent(myFont, 
		dataWindowX, 0, fontSize, windowToModify->getSize().x, windowToModify->getSize().y);

	PipelineGraphRenderComponent* graphBounds = new PipelineGraphRenderComponent(0, 0, dataWindowX,
		float(windowToModify->getSize().y));
    

    //Network* solNet = PipelineLevelBuilder::buildLevelOneNetworkSolution();
	//Desktop* currDesk = &World::getCurrDesktop();
	int netvecindex = World::getCurrDesktop().getNetVecIndex();
	Network* solNet;
	if (!World::getCurrDesktop().getNetVec().empty()) {
		solNet = World::getCurrDesktop().getNetVec().at(netvecindex);
	} else {
		solNet = PipelineLevelBuilder::buildDefaultNetwork();
	}
	Network* playNet = solNet->copyNetworkByVerts();


    NetworkCheckFunctor *ncf = new NetworkCheckFunctor(*solNet, *playNet);
	playNet->setCenter(-1);  //TEST THIS

	//std::vector<int> indexVec {0, 1, 2, 3, 4, 5, 6, 7};
	std::vector<int> indexVec;
	for (unsigned int i = 0; i < solNet->size(); ++i) {
		indexVec.push_back(i);
	}
	std::random_shuffle(indexVec.begin(), indexVec.end());
	//No Overlapping Edges (Think of this positioning as an 8x8 grid
	//the number after the * is the row/column number)
	for (unsigned int i = 0, j = 0; i < indexVec.size(); ++i) {
		playNet->vert(indexVec[i]).setPosition(50 + 70 * i%4, 50 + 100 * j);
		if (i > 0 && i % 4 == 0) j++;
	}

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
		( ( graphBounds->getLocalBounds().width - (buttonSize * buttonScale) ) / 2 ), static_cast<float>(windowToModify->getSize().y-50), buttonScale, ncf);
	/////////////////////////////////////////
	/////// WINDOW CONSTRUCTION
	///////////////////////////////////////
	windowToModify->addEntity(dataBox);
	windowToModify->addEntity(graphBox);
	windowToModify->addEntity(submitButton);
	windowToModify->setPosition(x, y);
	windowToModify = new BorderDecorator(*windowToModify);
	dynamic_cast<BorderDecorator*>(windowToModify)->addButton(buttonSheet, closeWindow);
	dynamic_cast<BorderDecorator*>(windowToModify)->setCaption("DCPS Pipeline Application v.3.762");
}

void ppc::spawnFile(WindowInterface*& windowToModify, InputHandler & ih, NodeState & ns, sf::Image& buttonSheet,
	float x, float y, string filename, string p) {
    if (windowToModify == nullptr) return; 
    
    string path = resourcePath() + p;
    string dotEnd;
    
    if (!path.empty()) dotEnd = path.substr(path.length() - 4);
    
    /////////////////////////////////////////
    /////// COMPONENTS & ENTITIES
    ///////////////////////////////////////
    sf::Image iconSheet;
    iconSheet.loadFromFile(resourcePath() + "Icon_Sheet.png");

    Entity newEnt;
    
    if(dotEnd == TXT){
        sf::Font myFont;
        myFont.loadFromFile(resourcePath() + "consola.ttf");
        int fontSize = 20;
        int windowOffset = 5;
        
        int textMuliplier = 23;
        int maxWindowScroll = 8192;
        int maxWindowLines = 350;
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
        windowToModify->setPosition(x, y);
        windowToModify->addEntity(newEnt);
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
        
        photoRenderComponent* photoRender = new photoRenderComponent(photo);
        
        newEnt.addComponent(photoRender);
        windowToModify->setPosition(x, y);
        windowToModify->addEntity(newEnt);
        windowToModify->setSize(photo.getSize().x/2, photo.getSize().y/2);
        
        photoRender->setImageScale((float)windowToModify->getSize().x /
                               (float)photo.getSize().x,
                               (float)windowToModify->getSize().y /
                                   (float)photo.getSize().y);
    }
    
    /////////////////////////////////////////
    /////// WINDOW CONSTRUCTION
    ///////////////////////////////////////
    windowToModify = new BorderDecorator(*windowToModify);
    BorderDecorator* border = dynamic_cast<BorderDecorator*>(windowToModify);
    border->addButton(buttonSheet, closeWindow);
    border->setCaption(filename);
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
    int emailApplicationHeight = emailBoxElementHeight * 6;
    
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
    windowToModify->setPosition(x, y);

	/////////////////////////////////////////
	/////// WINDOW CONSTRUCTION
	///////////////////////////////////////
    /* Create email app height dynamically if only a few emails */
    sf::FloatRect viewRect = {
        0.0f,
        0.0f,
        float(windowToModify->getSize().x),
        float(windowToModify->getSize().y)
    };
    /* If many emails, have the app size be predetermined */
    if(newHeight > emailApplicationHeight){
        viewRect = {
            0.0f,
            0.0f,
            float(windowToModify->getSize().x),
            float(emailApplicationHeight)
        };
    }
	windowToModify = new ScrollBarDecorator(*windowToModify, buttonSheet, sf::View(viewRect));
	windowToModify = new BorderDecorator(*windowToModify);
	dynamic_cast<BorderDecorator*>(windowToModify)->addButton(buttonSheet, closeWindow);
	dynamic_cast<BorderDecorator*>(windowToModify)->setCaption("My Messages");

}

void ppc::spawnEmailMessage(WindowInterface*& windowToModify, InputHandler& ih, Email& mail, sf::Image& buttonSheet, float x, float y) {
	if (windowToModify == nullptr) { return; }

	/////////////////////////////////////////
	/////// COMPONENTS
	///////////////////////////////////////
	sf::Font myFont;
	myFont.loadFromFile(resourcePath() + "consola.ttf");
	int fontSize = 20;

	string content = mail.getContentField();
	int lineCount = 1;
	int lineMultiplier = 23;
	int preLineCount = 6;
	for (unsigned int i = 0; i < content.size(); i++) {
		if (content[i] == '\n') {
			lineCount++;
		}
	}
	lineCount += preLineCount;
	lineCount = lineCount*lineMultiplier;

	windowToModify->setSize(windowToModify->getSize().x, lineCount);

	emailMessageRenderComponent* eMRC = new emailMessageRenderComponent(myFont, mail, 0, 0, fontSize,
		windowToModify->getSize().x, windowToModify->getSize().y);

	/////////////////////////////////////////
	/////// ENTITIES
	///////////////////////////////////////
	Entity emailMessageDisplayBox;
	emailMessageDisplayBox.addComponent(eMRC);

	/////////////////////////////////////////
	/////// WINDOW CONSTRUCTION
	///////////////////////////////////////
    
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
	dynamic_cast<BorderDecorator*>(windowToModify)->setCaption(mail.getAbbrevSubjectField());
}


void ppc::spawnErrorMessage(WindowInterface*& windowToModify, InputHandler& ih, sf::Image& buttonSheet, float x, float y, std::string message) {
	if (windowToModify == nullptr) { return; }

	/////////////////////////////////////////
	/////// COMPONENTS
	///////////////////////////////////////

	sf::Font myFont;
	myFont.loadFromFile(resourcePath() + "consola.ttf");
	int fontSize = 16;

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
	float buttonScale = 0.25f;
	float buttonX = ((windowWidth - (alertWidth * buttonScale)) / 2);
	float buttonY = (2 * (windowHeight / 3));
	spawnAlertIcon(alertIcon, ih, buttonSheet, alertX, alertY, 0.5f);

	Entity errorMessageDisplayBox;
	errorMessageDisplayBox.addComponent(eMRC);

	// Button Test
	ButtonBuilder builder;
	builder.setButtonPosition(sf::Vector2f(buttonX, buttonY));
	builder.setInputHandle(ih);
	builder.setSize(0.25f);
	builder.setSpritesByIndicies(0, 2, 2, 1);
	builder.setSpriteSheet(buttonSheet);
	builder.setLabelMessage("OK");
	builder.setLabelFont(myFont);
	builder.setLabelSize(12);
	Entity ent;
	builder.create(ent);

	/////////////////////////////////////////
	/////// WINDOW CONSTRUCTION
	///////////////////////////////////////
	windowToModify->addEntity(errorMessageDisplayBox);
	windowToModify->addEntity(alertIcon);
	//windowToModify->addEntity(ent);
	windowToModify->setPosition(x, y);
	windowToModify = new BorderDecorator(*windowToModify);
	dynamic_cast<BorderDecorator*>(windowToModify)->addButton(buttonSheet, closeWindow);
	dynamic_cast<BorderDecorator*>(windowToModify)->setCaption("Error");
}
void ppc::spawnPromptMessage(WindowInterface*& windowToModify, InputHandler& ih, sf::Image& buttonSheet, float x, float y, std::string message) {
    if (windowToModify == nullptr) { return; }
    
    /////////////////////////////////////////
    /////// COMPONENTS
    ///////////////////////////////////////
    
    sf::Font myFont;
    myFont.loadFromFile(resourcePath() + "consola.ttf");
    int fontSize = 16;
    
    errorMessageRenderComponent* eMRC = new errorMessageRenderComponent(myFont, message,
                                                                        windowToModify->getSize().x/3,( windowToModify->getSize().y/3)-40, fontSize);
    
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
    float buttonScale = 0.25f;
    float buttonX = ((windowWidth - (alertWidth * buttonScale)) / 2);
    float buttonY = (2 * (windowHeight / 3));
    spawnPromptIcon(alertIcon, ih, buttonSheet, alertX, alertY, 0.5f);
    
    Entity errorMessageDisplayBox;
    errorMessageDisplayBox.addComponent(eMRC);
    
    // Button Test
    ButtonBuilder builder;
    builder.setButtonPosition(sf::Vector2f(buttonX, buttonY));
    builder.setInputHandle(ih);
    builder.setSize(0.25f);
    builder.setSpritesByIndicies(0, 2, 2, 1);
    builder.setSpriteSheet(buttonSheet);
    builder.setLabelMessage("Submit");
    builder.setLabelFont(myFont);
    builder.setLabelSize(12);
    Entity ent;
    builder.create(ent);
    
    
    Entity tbox;
    TextBoxBuilder tbuilder;
    tbuilder.setFont(myFont);
    tbuilder.setSize(20);
    tbuilder.setPosition(sf::Vector2f(windowToModify->getSize().x/3,50.0f));
    tbuilder.setColor(sf::Color::Black);
    tbuilder.setString("text box");
    tbuilder.setInputHandle(ih);
    tbuilder.create(tbox);
    
    
    /////////////////////////////////////////
    /////// WINDOW CONSTRUCTION
    ///////////////////////////////////////
    windowToModify->addEntity(errorMessageDisplayBox);
    windowToModify->addEntity(alertIcon);
    windowToModify->addEntity(ent);
    windowToModify->addEntity(tbox);
    windowToModify->setPosition(x, y);
    windowToModify = new BorderDecorator(*windowToModify);
    dynamic_cast<BorderDecorator*>(windowToModify)->addButton(buttonSheet, closeWindow);
    dynamic_cast<BorderDecorator*>(windowToModify)->setCaption("Prompt");
}

void ppc::spawnExplorer(Desktop& dt, WindowInterface*& windowToModify, InputHandler& ih, NodeState ns,
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

	float viewHeight = windowToModify->getSize().y / 2;

	/* Create a scroll bar if the new explorer window is greater than 100px*/
	if (viewHeight > 100.0f) {
		sf::FloatRect viewRect = {
			0.0f,
			0.0f,
			float(windowToModify->getSize().x),
			viewHeight
		};
		windowToModify = new ScrollBarDecorator(*windowToModify, buttonSheet, sf::View(viewRect));
	}

	vector<string> pwd_vector = ns.getPwdVector();
	string pwd = "C:/";

	for (auto iter = pwd_vector.begin() + 1; iter != pwd_vector.end(); ++iter) {
		pwd += *iter;
		pwd.push_back('/');
	}
	
	windowToModify->setPosition(x, y);
	windowToModify = new BorderDecorator(*windowToModify);
	dynamic_cast<BorderDecorator*>(windowToModify)->addButton(buttonSheet, closeWindow);
	dynamic_cast<BorderDecorator*>(windowToModify)->setCaption(pwd);
}

void ppc::spawnContextMenu(Desktop& dT, WindowInterface*& windowToModify, InputHandler& ih, std::vector<std::string> elementNames,
	std::vector<bool (*)(Desktop*, Event)> elementFunctions, float x, float y) {
	/* Check to make sure the window passed isn't null */
	if (windowToModify == nullptr) { return; }

	sf::Font myFont;
	myFont.loadFromFile(resourcePath() + "consola.ttf");
	int fontSize = 20;
	int windowOffset = 5;
	int contextBoxElementWidth = windowToModify->getSize().x;
	int contextBoxElementHeight = fontSize+2;
	int contextBoxPadding = 5;

	int totalElementsLoaded = 0;
	/////////////////////////////////////////
	/////// ENTITIES
	///////////////////////////////////////
	/* Create an email list element entity for each email in the inbox*/
	for (int i = 0; i < elementNames.size(); ++i) {
		Entity contextListElement;
		createContextListElement(
			contextListElement, windowToModify, dT, ih, myFont, elementNames.at(i), elementFunctions.at(i),
			0, (i * (contextBoxElementHeight + contextBoxPadding)), contextBoxElementWidth, contextBoxElementHeight,
			0, (i * (contextBoxElementHeight + contextBoxPadding)), fontSize);
		windowToModify->addEntity(contextListElement);
		++totalElementsLoaded;
	}

	int newHeight = (totalElementsLoaded)* (contextBoxElementHeight + contextBoxPadding);
	int newWidth = windowToModify->getSize().x;
	windowToModify->setSize(newWidth, newHeight+contextBoxPadding);

	/////////////////////////////////////////
	/////// WINDOW CONSTRUCTION
	///////////////////////////////////////

	windowToModify->setPosition(x, y);

}


