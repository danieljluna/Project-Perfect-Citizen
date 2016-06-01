#include "../ResourceDef.h"

#include "../Engine/debug.h"
#include "createWindow.h"

#include <iostream>
#include <fstream>
#include <SFML/Main.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics/Image.hpp>
#include <sstream>
#include <algorithm>

#include "../Engine/World.h"
#include "../Engine/Window.h"
#include "../Engine/inputComponent.h"
#include "../Engine/InputHandler.h"
#include "../Engine/Entity.h"
#include "../Engine/subject.h"
#include "../Engine/BorderDecorator.h"
#include "../Engine/ScrollBarDeco.h"
#include "../Engine/FreeFunctionObserver.h"
#include "../Engine/SuspiciousFileHolder.h"
#include "../Engine/Network.h"
#include "../Engine/Edge.h"
#include "../Engine/Vertex.h"
#include "../Engine/desktop.h"

#include "../Library/json/json.h"

#include "buttonRenderComponent.h"
#include "consoleUpdateComponent.h"
#include "textInputRenderComponent.hpp"
#include "textInputKeys.hpp"
#include "textInputRenderComponent.hpp"
#include "textOutputRenderComponent.h"
#include "databaseSearchRenderComponent.h"
#include "databaseSearchInputComponent.h"
#include "databaseDisplayRenderComponent.h"

#include "Inbox.h"
#include "Email.h"
#include "errorMessageRenderComponent.h"
#include "Explorer.h"
#include "NetworkCheckFunctor.h"


#include "characterRender.hpp"

#include "PipelineDataRenderComponent.h"
#include "PipelineGraphRenderComponent.h"
#include "photoRenderComponent.hpp"
#include "textRenderComponent.hpp"
#include "textLabelComponent.hpp"

#include "NetworkRenderCmpnt.h"
#include "NetworkInputCmpnt.h"
#include "NetworkUpdateCmpnt.h"

#include "PipelineLevelBuilder.h"
#include "createListElement.h"
#include "emailExtraction.hpp"
#include "emailMessageRenderComponent.h"

#include "ButtonBuilder.h"
#include "TextDisplayBuilder.h"
#include "TextDisplayRenderComponent.h"

#include "TextBoxBuilder.h"

#include "HelpRenderComponent.hpp"
#include "readingMacDirectory.hpp"

#include "createButton.h"

#include "explorerFolderInputComponent.h"

#include "ConfirmWindowBuilder.h"
#include "flaggedFileInputComponent.h"


using namespace ppc;

const std::string PNG = ".png";
const std::string JPG = ".jpg";
const std::string TXT = ".txt";

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
    new textInputRenderComponent(myFont, 0, 0, fontSize);
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
            float(windowToModify->getSize().y / 5)
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
	Entity tab2;
    

    // Button Test
    ButtonBuilder builder;
    builder.setButtonPosition(sf::Vector2f(128, 16));
    builder.setInputHandle(ih);
    builder.setSize(0.25f);
    builder.setSpriteSheet(buttonSheet);
    builder.setLabelMessage("Console");
    builder.setLabelFont(myFont);
    builder.setLabelSize(12);

    builder.create(tab0);
    createWithEventFunc(builder, tab0, helpText1, swithTab0Fn);

    builder.setButtonPosition(sf::Vector2f(256,16));
    builder.setLabelMessage("Graph");

    builder.create(tab1);
    createWithEventFunc(builder, tab1, helpText1, swithTab1Fn);

	builder.setButtonPosition(sf::Vector2f(384, 16));
	builder.setLabelMessage("Desktops");

	createWithEventFunc(builder, tab2, helpText1, swithTab2Fn);

    
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
	windowToModify->addEntity(tab2);
    windowToModify->addEntity(help);
    
    sf::FloatRect viewRect = {
        0.0f,
        0.0f,
        float(windowToModify->getSize().x),
        float(windowToModify->getSize().y / 1.8)
    };
    windowToModify = new ScrollBarDecorator(*windowToModify, buttonSheet, sf::View(viewRect));
    
    windowToModify = new BorderDecorator(*windowToModify);
    dynamic_cast<BorderDecorator*>(windowToModify)->addButton(buttonSheet, closeWindow);
	dynamic_cast<BorderDecorator*>(windowToModify)->setCaption("DCPS Help Manual");
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
		static_cast<int>(dataWindowX), 0, fontSize, windowToModify->getSize().x, 
		windowToModify->getSize().y);

	PipelineGraphRenderComponent* graphBounds = new PipelineGraphRenderComponent(0, 0, dataWindowX,
		float(windowToModify->getSize().y));
    

    //Network* solNet = PipelineLevelBuilder::buildLevelOneNetworkSolution();
	//Desktop* currDesk = &World::getCurrDesktop();
	unsigned int netvecindex = World::getCurrDesktop().getNetVecIndex();
	Network* solNet, *playNet;
	if (netvecindex < World::getCurrDesktop().getSolVec().size()) {
		solNet = World::getCurrDesktop().getSolVec().at(netvecindex);
		playNet = World::getCurrDesktop().getPlayVec().at(netvecindex);
	} else {
		solNet = PipelineLevelBuilder::buildDefaultNetwork();
		playNet = solNet->copyNetworkByVerts();
	}


    NetworkCheckFunctor *ncf = new NetworkCheckFunctor(*solNet, *playNet);
	playNet->setCenter(-1);  //TEST THIS

	if (playNet->size() == 2) {
		playNet->vert(0).setPosition(static_cast<float>(25), static_cast<float>(25));
		playNet->vert(1).setPosition(static_cast<float>(275), static_cast<float>(25));
	}
	else {
		//std::vector<int> indexVec {0, 1, 2, 3, 4, 5, 6, 7};
		std::vector<int> indexVec;
		for (unsigned int i = 0; i < solNet->size(); ++i) {
			indexVec.push_back(i);
		}
		std::random_shuffle(indexVec.begin(), indexVec.end());

		float xcoord = 0;
		float ycoord = 0;

		for (unsigned int i = 0; i < indexVec.size(); ++i) {
			playNet->vert(indexVec[i]).setPosition(static_cast<float>(25 + 125 * xcoord),
				static_cast<float>(25 + 150 * ycoord));
			++xcoord;
			if (xcoord == 4) {
				xcoord = 0;
				++ycoord;
			}
		}
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



	/////////////////////////////////////////
	/////// WINDOW CONSTRUCTION
	///////////////////////////////////////
	windowToModify->addEntity(dataBox);
	windowToModify->addEntity(graphBox);
	if (World::getCurrDesktop().getNetVecIndex() >= World::getCurrDesktop().getNetVecSize() - 1) {
		Entity submitButton;
		float buttonScale = 0.25f;
		int buttonSize = 256;
		spawnNetworkOkayButton(playNet, submitButton, windowToModify->getInputHandler(), buttonSheet,
			((graphBounds->getLocalBounds().width - (buttonSize * buttonScale)) / 2), static_cast<float>(windowToModify->getSize().y - 50), buttonScale,
			ncf, myFont);
		windowToModify->addEntity(submitButton);
	}
	windowToModify->setPosition(x, y);
	windowToModify = new BorderDecorator(*windowToModify);
	dynamic_cast<BorderDecorator*>(windowToModify)->addButton(buttonSheet, closeWindow);
	dynamic_cast<BorderDecorator*>(windowToModify)->setCaption("DCPS Pipeline Application v.3.762");
}

void ppc::spawnFile(WindowInterface*& windowToModify, InputHandler & ih, 
	float x, float y, std::string filename, std::string p) {
    if (windowToModify == nullptr) return; 
    
#ifndef WINDOWS_MARKER
        readingMacDirectory* dir = new readingMacDirectory();
        p = dir->getDirectory(p);
        delete(dir);
#endif
    
    std::string path = resourcePath() + p;
    //std::cout <<  "\n" + path +  "\n" << std::endl;
    std::string dotEnd;
    
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
        int minWindowHeight = 500;
        std::ifstream f(path);
        std::string line;
		std::string content;
        while (std::getline(f, line)){
            if(windowScrollHeight < maxWindowLines){
                ++windowScrollHeight;
                content += line + "\n";
            }
            else if(windowScrollHeight > maxWindowLines){
                break;
            }
        }
        
        
        textRenderComponent* textBox =
        new textRenderComponent(myFont, content, 0, 0, fontSize);
        newEnt.addComponent(textBox);
        windowToModify->setPosition(x, y);
        windowToModify->addEntity(newEnt);
        
        windowScrollHeight = windowScrollHeight * textMuliplier;
        if(windowScrollHeight > maxWindowScroll){
            windowScrollHeight = maxWindowScroll;
        }
        else if(windowScrollHeight < minWindowHeight){
            windowScrollHeight = minWindowHeight;

        }
        if(windowScrollHeight > minWindowHeight){
            windowToModify->setSize(windowToModify->getSize().x, windowScrollHeight);
            sf::FloatRect viewRect = {
                0.0f,
                0.0f,
                float(windowToModify->getSize().x),
                float(windowToModify->getSize().x)
            };
            windowToModify = new ScrollBarDecorator(*windowToModify, World::getCurrDesktop().getButtonSheet(), sf::View(viewRect));
        }
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
    border->addButton(World::getCurrDesktop().getButtonSheet(), closeWindow);
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
		if (inbox.getEmailAt(i)->getVisible() == false) continue;
		Entity emailListElement;
        createEmailListElement(
			emailListElement, dT, buttonSheet, ih, myFont, inbox.getEmailAt(i), 0, (totalEmailsLoaded * (emailBoxElementHeight+emailBoxPadding)),
			emailBoxElementWidth, emailBoxElementHeight, 0, static_cast<int>((totalEmailsLoaded * (1.5*emailBoxElementHeight))), fontSize);
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

void ppc::spawnEmailMessage(WindowInterface*& windowToModify, InputHandler& ih, Email* mail, sf::Image& buttonSheet, float x, float y) {
	if (windowToModify == nullptr) { return; }

	/////////////////////////////////////////
	/////// COMPONENTS
	///////////////////////////////////////
	sf::Font myFont;
	myFont.loadFromFile(resourcePath() + "consola.ttf");
	int fontSize = 20;

	std::string content = mail->getContentField();
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
	dynamic_cast<BorderDecorator*>(windowToModify)->setCaption(mail->getAbbrevSubjectField());
}


void ppc::spawnErrorMessage(WindowInterface*& windowToModify, InputHandler& ih, sf::Image& buttonSheet, float x, float y, std::string message, std::string windowCaption) {
	if (windowToModify == nullptr) { return; }

	windowToModify->setSize(300.0f, windowToModify->getSize().y);
	/////////////////////////////////////////
	/////// COMPONENTS
	///////////////////////////////////////

	sf::Font myFont;
	myFont.loadFromFile(resourcePath() + "consola.ttf");
	int fontSize = 12;

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
	spawnAlertIcon(alertIcon, ih, buttonSheet, alertX, alertY, 0.5f);

	float constantWindowWidth = 50.0f;
	float newWindowWidth = (constantWindowWidth + (256 * buttonScale)
		+ eMRC->getText()->getLocalBounds().width);

	Entity errorMessageDisplayBox;
	errorMessageDisplayBox.addComponent(eMRC);

	windowToModify->setSize(newWindowWidth, windowHeight);
	float buttonX = ((newWindowWidth - (alertWidth * buttonScale)) / 2);
	float buttonY = (2 * (windowHeight / 3));

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
	createWithEventFunc(builder, ent, windowToModify, close_window);

	/////////////////////////////////////////
	/////// WINDOW CONSTRUCTION
	///////////////////////////////////////
	windowToModify->addEntity(errorMessageDisplayBox);
	windowToModify->addEntity(alertIcon);
	windowToModify->addEntity(ent);
	windowToModify->setPosition(x, y);
	
	windowToModify = new BorderDecorator(*windowToModify);
	dynamic_cast<BorderDecorator*>(windowToModify)->addButton(buttonSheet, closeWindow);
	dynamic_cast<BorderDecorator*>(windowToModify)->setCaption(windowCaption);
	

}

void ppc::spawnSuccessMessage(WindowInterface *& windowToModify, InputHandler & ih, sf::Image & buttonSheet, float x, float y, std::string message)
{
	if (windowToModify == nullptr) { return; }

	/////////////////////////////////////////
	/////// COMPONENTS
	///////////////////////////////////////

	sf::Font myFont;
	myFont.loadFromFile(resourcePath() + "consola.ttf");
	int fontSize = 16;

	errorMessageRenderComponent* eMRC = new errorMessageRenderComponent(myFont, message,
		windowToModify->getSize().x / 3, windowToModify->getSize().y / 3, fontSize);

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
	spawnConfirmedIcon(alertIcon, ih, buttonSheet, alertX, alertY, 0.5f);
	
	float newWindowWidth = ((windowWidth)-(eMRC->getText()->getLocalBounds().width - windowWidth));

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
	createWithEventFunc(builder, ent, windowToModify, close_window);

	/////////////////////////////////////////
	/////// WINDOW CONSTRUCTION
	///////////////////////////////////////
	windowToModify->addEntity(errorMessageDisplayBox);
	windowToModify->addEntity(alertIcon);
	windowToModify->addEntity(ent);
	windowToModify->setPosition(x, y);
	//windowToModify->setSize(sf::Vector2u(newWindowWidth, windowHeight));
	windowToModify = new BorderDecorator(*windowToModify);
	dynamic_cast<BorderDecorator*>(windowToModify)->addButton(buttonSheet, closeWindow);
	dynamic_cast<BorderDecorator*>(windowToModify)->setCaption("Success");
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
	tbuilder.setTextBoxCharacterLimit(20);
    tbuilder.setPosition(sf::Vector2f(static_cast<float>(windowToModify->getSize().x)/3,50.0f));
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

void ppc::spawnUnlock(WindowInterface *& windowToModify, InputHandler & ih, sf::Image & buttonSheet, float x, float y, explorerFolderInputComponent* fldr)
{
	if (windowToModify == nullptr) { return; }

	/////////////////////////////////////////
	/////// COMPONENTS
	///////////////////////////////////////

	sf::Font myFont;
	myFont.loadFromFile(resourcePath() + "consola.ttf");
	int fontSize = 12;

	errorMessageRenderComponent* eMRC = new errorMessageRenderComponent(myFont,
		"Please enter a password:\n> Recovery Hint: '" + fldr->getFolderNodeState()->getCwd()->findElement(fldr->getFolderName())->getHint() +"'\n",
		windowToModify->getSize().x / 3, (windowToModify->getSize().y / 3) - 40, fontSize);

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
	builder.setLabelMessage("GO");
	builder.setLabelFont(myFont);
	builder.setLabelSize(12);
	Entity ent;
	createWithEventFunc(builder, ent, fldr, ppc::unlock_folder);

	Entity tbox;
	TextBoxBuilder tbuilder;
	tbuilder.setFont(myFont);
	tbuilder.setSize(20);
	tbuilder.setTextBoxCharacterLimit(24);
	tbuilder.setPosition(sf::Vector2f(static_cast<float>(windowToModify->getSize().x) / 3, 50.0f));
	tbuilder.setColor(sf::Color::Black);
	tbuilder.setString("");
	tbuilder.setInputHandle(ih);
	tbuilder.setIsMasked(true);
	tbuilder.setContainingWindow(windowToModify);
	
	createWithEventFunc(tbuilder, tbox, fldr, ppc::unlock_folder);
	fldr->setObservingTextBox(tbuilder.getTextBoxInputComponent());


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
	dynamic_cast<BorderDecorator*>(windowToModify)->setCaption("'"+ fldr->getFolderName()+ "' is Password Protected");
}

void ppc::spawnLoginPrompt(WindowInterface *& windowToModify, InputHandler & ih, sf::Image & buttonSheet, float x, float y) {
   
    if (windowToModify == nullptr) { return; }
    
    /////////////////////////////////////////
    /////// COMPONENTS
    ///////////////////////////////////////
    
    sf::Font myFont;
    myFont.loadFromFile(resourcePath() + "consola.ttf");
    int fontSize = 12;
    
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
    spawnDCPSIcon(alertIcon, ih, buttonSheet, alertX-15, alertY-8, 0.74f);
    
    Entity tbox;
    TextBoxBuilder tbuilder;
    tbuilder.setFont(myFont);
    tbuilder.setSize(20);
    tbuilder.setPosition(sf::Vector2f(static_cast<float>(windowToModify->getSize().x) / 3, 50.0f));
    tbuilder.setColor(sf::Color::Black);
	tbuilder.setTextBoxCharacterLimit(24);
    tbuilder.setString("");
    tbuilder.setInputHandle(ih);
    tbuilder.setContainingWindow(windowToModify);
	tbuilder.setIsMasked(false);
	createWithEventFunc(tbuilder, tbox, windowToModify, ppc::continue_world);
    
    Entity promptText;
    TextDisplayBuilder tdBuilder;
    tdBuilder.setFont(myFont);
    tdBuilder.setSize(20);

    tdBuilder.setPosition(sf::Vector2f(static_cast<float>(windowToModify->getSize().x) / 3, 20));
    tdBuilder.setColor(sf::Color::Black);
    tdBuilder.setString("Please Enter Your Name");
    tdBuilder.create(promptText);
    
    Entity loginButton;
    ButtonBuilder lBuilder;
    lBuilder.setInputHandle(ih);
    lBuilder.setLabelMessage("LOG IN");
    lBuilder.setSpriteSheet(buttonSheet);
    lBuilder.setButtonPosition(sf::Vector2f(static_cast<float>((2.5*windowToModify->getSize().x) / 3)-2, 95.0f));
    lBuilder.setSize(0.25f);
    lBuilder.setLabelFont(myFont);
    lBuilder.setLabelSize(12);
	createWithEventFunc(lBuilder, loginButton, windowToModify, continue_world);

	Entity settingsButton;
	lBuilder.setLabelMessage("Settings");
	lBuilder.setButtonPosition(sf::Vector2f(static_cast<float>((2.5*windowToModify->getSize().x) / 3) - 75, 95.0f));
	createWithEventFunc(lBuilder, settingsButton, windowToModify, open_settings);

	Entity creditsButton;
	lBuilder.setLabelMessage("Credits");
	lBuilder.setButtonPosition(sf::Vector2f(static_cast<float>((2.5*windowToModify->getSize().x) / 3) - 152, 95.0f));
	createWithEventFunc(lBuilder, creditsButton, windowToModify, open_credits);
  
    
    windowToModify->addEntity(alertIcon);
    windowToModify->addEntity(tbox);
    windowToModify->addEntity(promptText);
    windowToModify->addEntity(loginButton);
	windowToModify->addEntity(settingsButton);
	windowToModify->addEntity(creditsButton);
    windowToModify = new BorderDecorator(*windowToModify);

    dynamic_cast<BorderDecorator*>(windowToModify)->setCaption("Login");

}


void ppc::spawnExplorer(Desktop& dt, WindowInterface*& windowToModify, InputHandler& ih, NodeState* ns,
	sf::Image& buttonSheet, sf::Image& iconSheet, float x, float y) {
	/* Check to make sure the window passed isn't null */
	if (windowToModify == nullptr) { return; }

	/////////////////////////////////////////
	/////// COMPONENTS
	///////////////////////////////////////
	int maxCaptionCharacters = 30;
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

	float viewHeight = static_cast<float>(windowToModify->getSize().y / 1.5);
    windowToModify->setPosition(x, y);

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

	// Create the window caption and format it //
	std::vector<std::string> pwd_vector = ns->getPwdVector();
	std::string pwd = "";

	/*for (auto iter = pwd_vector.begin() + 1; iter != pwd_vector.end(); ++iter) {
		pwd += *iter;
		pwd.push_back('/');
	}*/

	for (auto iter = pwd_vector.rbegin(); iter != pwd_vector.rend(); ++iter) {
		
		if (pwd.length() > maxCaptionCharacters) {
			pwd = ".../" + pwd;
			break;
		}
		else {
			pwd = "/" + pwd;
			pwd = *iter + pwd;
		}
	}

	if (pwd.length() <= maxCaptionCharacters) {
		pwd = "C:" + pwd;
	}
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
	for (unsigned int i = 0; i < elementNames.size(); ++i) {
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

void ppc::spawnContextMenu(WindowInterface *& windowToModify, std::vector<ppc::Entity> listElements, float x, float y)
{
	int contextBoxElementWidth = windowToModify->getSize().x;
	int contextBoxElementHeight = 22; // Change this to be font size + 2
	int contextBoxPadding = 5;
	int totalElementsLoaded = 0;

	for (unsigned int i = 0; i < listElements.size(); ++i) {
		windowToModify->addEntity(listElements.at(i));
		++totalElementsLoaded;
	}

	int newHeight = (totalElementsLoaded)* (contextBoxElementHeight + contextBoxPadding);
	int newWidth = windowToModify->getSize().x;
	windowToModify->setSize(newWidth, newHeight + contextBoxPadding);
	windowToModify->setPosition(x, y);
}


void ppc::spawnFileTracker(Desktop & dt, WindowInterface *& windowToModify, InputHandler & ih, float x, float y)
{
	if (windowToModify == nullptr) { return; }

	/////////////////////////////////////////
	//// Files/Text Labels
	///////////////////////////////////////
	float fileSpacing = windowToModify->getSize().x / 3.5;
	int padding = 20;
	textLabelComponent* label;
	for (unsigned int i = 0; i < 3/*fH->getBfgVector().size()*/; ++i) {
		
		Entity fileRender;
		buttonRenderComponent* IconRender = new buttonRenderComponent(dt.getIconSheet(), 0, 0, 1, 3);
		IconRender->renderPosition(sf::Vector2f(static_cast<float>(fileSpacing*i) + padding, 5));

		if (ppc::SuspiciousFileHolder::getBFTVectorElement(i) != nullptr) {

			std::string newLabel = ppc::SuspiciousFileHolder::getBFTVectorElement(i)->getName();
			if (newLabel.size() > 20) {
				newLabel = newLabel.substr(0, 15);
				newLabel += "...";
			}
			
			label = new textLabelComponent(World::getFont(World::Consola), sf::Color::Green,
				(float)((fileSpacing*i) + padding / 2), IconRender->getSprite()->getLocalBounds().height*0.5f, 12,
				newLabel);

			mousePressButton* mpb = new mousePressButton(windowToModify->getInputHandler(), IconRender->getSprite()->getGlobalBounds());
			flaggedFileInputComponent* fIC = new flaggedFileInputComponent(&dt, windowToModify, windowToModify->getInputHandler(),
				ppc::SuspiciousFileHolder::getBFTVectorElement(i)->getName());
			fileRender.addComponent(mpb);
			fileRender.addComponent(fIC);
		}
		else {
			label = new textLabelComponent(World::getFont(World::Consola), sf::Color::Red,
				(float)((fileSpacing*i) + padding / 2), IconRender->getSprite()->getLocalBounds().height*0.5f, 12, "  [EMPTY]");
		}

		fileRender.addComponent(IconRender);
		fileRender.addComponent(label);

		windowToModify->addEntity(fileRender);
	}

	/////////////////////////////////////////
	//// Buttons
	///////////////////////////////////////
	int submitBtnX = windowToModify->getSize().x - 5;
	int submitBtnY = windowToModify->getSize().y;
	float submitBtnSize = 0.25f;

	ButtonBuilder builder;
	Entity submitBtn;
	Entity scanBtn;
	builder.setButtonPosition({ (float)(submitBtnX - (256 * submitBtnSize)), 5 });
	builder.setInputHandle(windowToModify->getInputHandler());
	builder.setLabelFont(World::getFont(World::Consola));
	builder.setLabelMessage("SUBMIT");
	builder.setLabelSize(15);
	builder.setSize(submitBtnSize);
	builder.setSpriteSheet(dt.getButtonSheet());
	createWithEventFunc(builder, submitBtn, &dt, ppc::ConfirmSubmitFiles);

	builder.setButtonPosition({ (float)(submitBtnX - (256 * submitBtnSize)), (256 * submitBtnSize) - padding });
	builder.setLabelMessage("CLEAR");
	createWithEventFunc(builder, scanBtn, &dt, clear_flagged_files);

	windowToModify->addEntity(submitBtn);
	windowToModify->addEntity(scanBtn);

	/////////////////////////////////////////
	/////// WINDOW CONSTRUCTION
	///////////////////////////////////////
	windowToModify->setSize(450, 100);
	windowToModify = new BorderDecorator(*windowToModify);
	windowToModify->setPosition({ x,y });
	//dynamic_cast<BorderDecorator*>(windowToModify)->addButton(dt.getButtonSheet(), closeWindow);
	dynamic_cast<BorderDecorator*>(windowToModify)->setCaption("Tracked Files:");
	

}

void ppc::spawnSettingsMenu(Desktop * dt, WindowInterface *& windowToModify, InputHandler & ih, float x, float y)
{

	float windowWidth = static_cast<float>(windowToModify->getSize().x);
	float windowHeight = static_cast<float>(windowToModify->getSize().y);
	sf::Font myFont = World::getFont(ppc::World::VT323Regular);
	int subHeaderSize = 20;
	int headerSize = 36;
	int buttonLetterSize = 20;
	float buttonScale = 0.25f;

	// Icon //
	Entity alertIcon;
	float alertScale = 0.5f;
	float alertWidth = 128.0;
	float alertX = windowWidth - ((alertWidth * alertScale) + (3 * (windowWidth / 4)));
	float alertY = (windowHeight - (alertWidth * alertScale)) / 8;
	spawnDCPSIcon(alertIcon, ih, dt->getButtonSheet(), alertX - 15, alertY - 8, 0.74f);
	
	ppc::TextDisplayRenderComponent* settingsText = new ppc::TextDisplayRenderComponent(myFont, sf::Color::Black,
		alertX+100, alertY, headerSize-6, "Project Perfect Citizen:\n > Game Settings");
	alertIcon.addComponent(settingsText);
	windowToModify->addEntity(alertIcon);

	ButtonBuilder builder;

	// Resolution Module //

		// Resolution Header //
		Entity resolutionText;
		ppc::TextDisplayRenderComponent* resolutionHeader = new ppc::TextDisplayRenderComponent(myFont, sf::Color::Black,
			0.0f, 0.0f, headerSize, "Resolution");
		resolutionHeader->updatePosition((windowWidth - resolutionHeader->getText()->getLocalBounds().width) / 2, 
			windowHeight/3);
		resolutionText.addComponent(resolutionHeader);
		windowToModify->addEntity(resolutionText);

		// Current Resolution
		Entity resDisplay;
		ppc::TextDisplayRenderComponent* currentRes = new ppc::TextDisplayRenderComponent(myFont, sf::Color::Black, 0.0f, 0.0f,
			subHeaderSize, std::to_string(World::getSettings().resolution.x) + " x " + std::to_string(World::getSettings().resolution.y));
		currentRes->updatePosition((windowWidth - currentRes->getText()->getLocalBounds().width) / 2,
			resolutionHeader->getTextPosition().y + 50);
		resDisplay.addComponent(currentRes);
		windowToModify->addEntity(resDisplay);

		// Decrement Button
		Entity decrementResolutionBtn;
		builder.setInputHandle(ih);
		builder.setLabelMessage("-");
		builder.setSpriteSheet(dt->getButtonSheet());
		builder.setButtonPosition((windowWidth) / 3,
			resolutionHeader->getTextPosition().y + 50);
		builder.setSize(buttonScale);
		builder.setLabelFont(myFont);
		builder.setLabelSize(buttonLetterSize);
		createWithEventFunc(builder, decrementResolutionBtn, currentRes, ppc::decrement_resolution);
		windowToModify->addEntity(decrementResolutionBtn);

		//Increment Button
		Entity incrementResolutionBtn;
		builder.setLabelMessage("+");
		builder.setButtonPosition((2 * windowWidth) / 3,
			resolutionHeader->getTextPosition().y + 50);
		createWithEventFunc(builder, incrementResolutionBtn, currentRes, ppc::increment_resolution);
		windowToModify->addEntity(incrementResolutionBtn);


	// Volume Module //

		// Volume Header //
		Entity volumeText;
		ppc::TextDisplayRenderComponent* volumeHeader = new ppc::TextDisplayRenderComponent(myFont, sf::Color::Black,
			0.0f, 0.0f, headerSize-3, "Master Volume");
		volumeHeader->updatePosition((windowWidth - volumeHeader->getText()->getLocalBounds().width) / 2,
			(2 * windowHeight) / 3 - 100);
		volumeText.addComponent(volumeHeader);
		windowToModify->addEntity(volumeText);
	
		// Current Volume
		Entity volDisplay;
		ppc::TextDisplayRenderComponent* currentVol = new ppc::TextDisplayRenderComponent(myFont, sf::Color::Black,
			0.0f, 0.0f, subHeaderSize, "50");
		currentVol->updatePosition((windowWidth - currentVol->getText()->getLocalBounds().width) / 2,
			volumeHeader->getTextPosition().y + 50);
		volDisplay.addComponent(currentVol);
		windowToModify->addEntity(volDisplay);

		// Decrement Button //
		Entity volumedecrementButton;
		builder.setLabelMessage("-");
		builder.setButtonPosition((windowWidth) / 3,
			volumeHeader->getTextPosition().y + 50);
		createWithEventFunc(builder, volumedecrementButton, currentVol, ppc::decrement_volume);
		windowToModify->addEntity(volumedecrementButton);

		// Increment Button //
		Entity volumeIncrementButton;
		builder.setLabelMessage("+");
		builder.setButtonPosition(
			(2*windowWidth)/3,
			volumeHeader->getTextPosition().y + 50);
		createWithEventFunc(builder, volumeIncrementButton, currentVol, ppc::increment_volume);
		windowToModify->addEntity(volumeIncrementButton);

	// Window Settings Module //
		// Window Settings Header //
			Entity windowText;
			ppc::TextDisplayRenderComponent* windowHeader = new ppc::TextDisplayRenderComponent(myFont, sf::Color::Black,
				0.0f, 0.0f, headerSize-2, "Window Settings");
			windowHeader->updatePosition((windowWidth - windowHeader->getText()->getLocalBounds().width) / 2,
				(2 * windowHeight) / 3);
			windowText.addComponent(windowHeader);
			windowToModify->addEntity(windowText);

		// Window Mode Button //
			Entity windowButton;
			builder.setLabelMessage("  Windowed  ");
			builder.setSize(0.45f);
			builder.setLabelSize(buttonLetterSize);
			builder.setIsToggle(true);
			std::vector<std::string> windowOptionsList;
			windowOptionsList.push_back("  Windowed  ");
			windowOptionsList.push_back(" Full Screen");
			builder.setToggleStates(windowOptionsList);
			builder.setButtonPosition(sf::Vector2f(static_cast<float>(windowToModify->getSize().x) - 300,
				windowHeader->getTextPosition().y + 50));
			builder.create(windowButton);
			attachEventFunc(builder, windowButton, builder.getTextRenderComponent(), toggle_window_settings);
			windowToModify->addEntity(windowButton);


	// Update Button //
		Entity updateButton;
		builder.setLabelMessage("Update");
		builder.setSize(0.25f);
		builder.setLabelSize(buttonLetterSize);
		builder.setIsToggle(false);
		builder.setButtonPosition(sf::Vector2f(static_cast<float>(windowToModify->getSize().x) - 100,
			static_cast<float>(windowToModify->getSize().y) -50));
		createWithEventFunc(builder, updateButton, currentRes, ppc::update_settings);
		windowToModify->addEntity(updateButton);

	windowToModify = new BorderDecorator(*windowToModify);
	dynamic_cast<BorderDecorator*>(windowToModify)->addButton(dt->getButtonSheet(), closeWindow);
	dynamic_cast<BorderDecorator*>(windowToModify)->setCaption("Settings");


}

void ppc::spawnCreditsWindow(Desktop * dt, WindowInterface *& windowToModify, InputHandler & ih, float x, float y)
{
	float windowWidth = static_cast<float>(windowToModify->getSize().x);
	float windowHeight = static_cast<float>(windowToModify->getSize().y);
	sf::Font myFont = World::getFont(ppc::World::VT323Regular);
	int subHeaderSize = 20;
	int headerSize = 36;
	float headerX = 200.0f;
	float subHeaderX = 100.0f;
	int buttonLetterSize = 20;
	float buttonScale = 0.25f;

	// Icon //
	Entity alertIcon;
	float alertScale = 0.5f;
	float alertWidth = 128.0;
	float alertX = windowWidth - ((alertWidth * alertScale) + (3 * (windowWidth / 4)));
	float alertY = (windowHeight - (alertWidth * alertScale)) / 8;
	spawnDCPSIcon(alertIcon, ih, dt->getButtonSheet(), alertX - 15, alertY - 8, 0.74f);

	ppc::TextDisplayRenderComponent* settingsText = new ppc::TextDisplayRenderComponent(myFont, sf::Color::Black,
		alertX + 100, alertY, headerSize - 6, "Project Perfect Citizen:\n > A Bad Cop Studios Game");
	alertIcon.addComponent(settingsText);
	windowToModify->addEntity(alertIcon);

	TextDisplayBuilder builder;
	builder.setColor(sf::Color::Black);
	builder.setFont(myFont);

	Entity productionHeader;
    builder.setSize(headerSize);
	builder.setPosition(sf::Vector2f(headerX-15, 200.0f));
	builder.setString("Production");
	builder.create(productionHeader);
	windowToModify->addEntity(productionHeader);

	Entity productionList;
    builder.setSize(subHeaderSize);
	builder.setPosition(sf::Vector2f(subHeaderX, 250.0f));
	builder.setString("     Alex Vincent   Project Lead");
	builder.create(productionList);
	windowToModify->addEntity(productionList);

	Entity designHeader;
    builder.setSize(headerSize);
	builder.setPosition(sf::Vector2f(headerX+10, 300.0f));
	builder.setString("Design");
	builder.create(designHeader);
	windowToModify->addEntity(designHeader);

	Entity designList;
    builder.setSize(subHeaderSize);
	builder.setPosition(sf::Vector2f(subHeaderX, 350.0f));
	builder.setString("      Mark Biundo   Lead Designer\n    Brandon Gomez   Game Designer\n    Jason Brisson   Writer/Designer");
	builder.create(designList);
	windowToModify->addEntity(designList);

	Entity programmerHeader;
    builder.setSize(headerSize);
	builder.setPosition(sf::Vector2f(headerX-15, 450.0f));
	builder.setString("Programming");
	builder.create(programmerHeader);
	windowToModify->addEntity(programmerHeader);

	Entity programmerList;
    builder.setSize(subHeaderSize);
	builder.setPosition(sf::Vector2f(subHeaderX, 500.0f));
	builder.setString("       Daniel Luna   Lead Developer\n       Nader Sleem   Game Programmer\n John 'Andy' Baden   Game Programmer/Designer");
	builder.create(programmerList);
	windowToModify->addEntity(programmerList);

	Entity artHeader;
    builder.setSize(headerSize);
	builder.setPosition(sf::Vector2f(headerX-10, 600.0f));
	builder.setString("Art & Sound");
	builder.create(artHeader);
	windowToModify->addEntity(artHeader);

	Entity artList;
    builder.setSize(subHeaderSize);
	builder.setPosition(sf::Vector2f(subHeaderX, 650.0f));
	builder.setString("      Michael Lowe   Lead Technical Artist\n      Austin Enoch   Character Artist\n    Pilar Costabal   User Interface Artist");
	builder.create(artList);
	windowToModify->addEntity(artList);

	Entity thanksHeader;
    builder.setSize(headerSize);
	builder.setPosition(sf::Vector2f(headerX-30, 750.0f));
	builder.setString("Special Thanks");
	builder.create(thanksHeader);
	windowToModify->addEntity(thanksHeader);

	Entity thanksList;
    builder.setSize(subHeaderSize);
	builder.setPosition(sf::Vector2f(subHeaderX, 800.0f));
	builder.setString("     Jim Whitehead   Senior Advisor\n    Michael Mateas   Senior Advisor\n        James Ryan   Advisor\n      Jessica Fong   Trailer Voice Over\n\n         UCSC Games & Playable Media");
	builder.create(thanksList);
	windowToModify->addEntity(thanksList);

	windowToModify->setSize(windowWidth, 1000.0f);
	sf::FloatRect viewRect = {
		0.0f,
		0.0f,
		float(windowToModify->getSize().x),
		float(windowToModify->getSize().y / 2)
	};

	windowToModify = new ScrollBarDecorator(*windowToModify, World::getCurrDesktop().getButtonSheet(), sf::View(viewRect));
    windowToModify->move(0, 200);
    
	windowToModify = new BorderDecorator(*windowToModify);
	dynamic_cast<BorderDecorator*>(windowToModify)->addButton(dt->getButtonSheet(), closeWindow);
	dynamic_cast<BorderDecorator*>(windowToModify)->setCaption("Credits");
}

bool ppc::close_window(WindowInterface * w, ppc::Event ev)
{
	w->close();
	return false;
}

bool ppc::open_settings(WindowInterface *w, ppc::Event ev) {
	WindowInterface* settingsWindow = new ppc::Window(500, 600, sf::Color(170, 170, 170));
	spawnSettingsMenu(&World::getCurrDesktop(), settingsWindow, settingsWindow->getInputHandler(), 500.0f, 500.0f);
	settingsWindow->setPosition(sf::Vector2f{ 200.0f, 200.0f });
	World::getCurrDesktop().addWindow(settingsWindow);
	return true;
}

bool ppc::open_credits(WindowInterface * w, ppc::Event ev)
{
	WindowInterface* creditsWindow = new ppc::Window(500, 600, sf::Color(170, 170, 170));
	spawnCreditsWindow(&World::getCurrDesktop(), creditsWindow, creditsWindow->getInputHandler(), 500.0f, 500.0f);
	creditsWindow->setPosition(sf::Vector2f{ 200.0f, 200.0f });
	World::getCurrDesktop().addWindow(creditsWindow);
	return true;
}

bool ppc::continue_world(WindowInterface* w, ppc::Event ev) {
    World::quitDesktop();
    return false;
}

bool ppc::increment_resolution(ppc::TextDisplayRenderComponent* ptr, ppc::Event ev)
{
    // Iterate up to next settings menu down
	std::string resolutionText = ptr->getString();
    sf::Vector2u resolution;
    resolution.x = std::atoi(resolutionText.substr(0, resolutionText.find_first_of(" ")).c_str());
    resolution.y = std::atoi(resolutionText.substr(resolutionText.find_last_of(" ") + 1).c_str());


    //------------------------------------
    //This section only allows searches through the fullscreen modes.
    //This hampers our aspect ratio currently

    auto possibleModes = sf::VideoMode::getFullscreenModes();

    //Search for current fullscreen mode
    auto it = possibleModes.begin();
    while (it != possibleModes.end()) {
        if ((it->width == resolution.x) && (it->height == resolution.y)) {
            break;
        }
        ++it;
    }

    //If we are on the first item or we couldn't find the current:
    if ((it == possibleModes.end()) || (it == possibleModes.begin())) {
        it = possibleModes.begin();
    } else {
        --it;
    }

    //------------------------------------

    // Uncomment the line below when the resolutions are loaded.
    ptr->updateString(std::to_string(it->width) + " x " +
        std::to_string(it->height));
    return true;
}

bool ppc::decrement_resolution(ppc::TextDisplayRenderComponent * ptr, ppc::Event ev)
{
	// Iterate up to next settings menu down
	std::string resolutionText = ptr->getString();
    sf::Vector2u resolution;
    resolution.x = std::atoi(resolutionText.substr(0, resolutionText.find_first_of(" ")).c_str());
    resolution.y = std::atoi(resolutionText.substr(resolutionText.find_last_of(" ") + 1).c_str());

    
    //------------------------------------
    //This section only allows searches through the fullscreen modes.
    //This hampers our aspect ratio currently
    
    auto possibleModes = sf::VideoMode::getFullscreenModes();
    //Search for current fullscreen mode
    auto it = possibleModes.begin();
    auto depth = it->bitsPerPixel;
    while (it != possibleModes.end()) {
        if (it->bitsPerPixel != depth) {
            it = possibleModes.end();
            break;
        }
        if ((it->width == resolution.x) && (it->height == resolution.y)) {
            break;
        }
        ++it;
    }

    //If we are not on the last item or we couldn't find the current:
    //If we are on the first item or we couldn't find the current:
    if (it == possibleModes.end()) {
        it = possibleModes.begin();
        while (it->bitsPerPixel == depth) {
            ++it;
        }
        --it;
    } else {
        ++it;
    }

    if (it->bitsPerPixel != depth) {
        --it;
    }

    //------------------------------------

	// Uncomment the line below when the resolutions are loaded.
	ptr->updateString(std::to_string(it->width) + " x " + 
                      std::to_string(it->height));
	return true;
}

bool ppc::increment_volume(ppc::TextDisplayRenderComponent * ptr, ppc::Event ev)
{
	int incrementBy = 5;
	int newVolumeVal = std::stoi(ptr->getString()) + incrementBy;

	if (newVolumeVal > 100) return false;
	else {
		// Update the audio engine with newVolumeVal here


		ptr->updateString(std::to_string(newVolumeVal));
	}
	return true;
}

bool ppc::decrement_volume(ppc::TextDisplayRenderComponent * ptr, ppc::Event ev)
{
	int decrementBy = 5;
	int newVolumeVal = std::stoi(ptr->getString()) - decrementBy;

	if (newVolumeVal < 0) return false;
	else {

		// Update the audio engine with newVolumeVal here

		ptr->updateString(std::to_string(newVolumeVal));
	}
	
	return true;
}

bool ppc::toggle_window_settings(TextDisplayRenderComponent * ptr, ppc::Event ev)
{
	ptr->incrementRenderState();

	// Danny: Do something with this string
	// It'll either be Windowed or Full Screen
	std::string targetWindowMode = ptr->getString();
	std::cout << targetWindowMode;
	return ptr;
}

bool ppc::update_settings(ppc::TextDisplayRenderComponent * ptr, ppc::Event ev)
{
	std::string resolutionText = ptr->getString();
	// Parse resolution x and y into resX and resY
    sf::Vector2u resolution;
    resolution.x = std::atoi(resolutionText.substr(0, resolutionText.find_first_of(" ")).c_str());
    resolution.y = std::atoi(resolutionText.substr(resolutionText.find_last_of(" ") + 1).c_str());

    Setting settings = World::getSettings();
    settings.resolution = resolution;
    World::setSettings(settings);
	
	// Set the new resolution using resX, resY;
	return true;
}


