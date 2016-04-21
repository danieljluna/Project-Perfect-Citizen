#ifdef WINDOWS_MARKER
#define resourcePath() string("Resources/")
#else
#include "ResourcePath.hpp"
#endif

#include "../Engine/debug.h"
#include "createIcon.h"
#include "../Game/emailExtraction.hpp"
#include "notifcationRenderComponent.h"
using namespace ppc;

void ppc::spawnFolderIcon(Entity& entityToModify, Desktop& dT, InputHandler& ih, Database& db, sf::Image& iconSheet, sf::Image& buttonSheet, float x, float y, float size, float animSpeed, ppc::Inbox* inbox) {

    // Label Component //
    sf::Font font;
    //font.loadFromFile(resourcePath() + "consola.ttf");
	font.loadFromFile(resourcePath() + "VT323-Regular.ttf");
    textLabelComponent* label = new textLabelComponent(font,sf::Color::White, x, y + size*128, 20, "Folder");
    
    buttonRenderComponent* IconRender = new buttonRenderComponent(iconSheet, 0, 0, 1, 4);
	IconRender->setImageScale(size, size);
	IconRender->renderPosition(sf::Vector2f(x, y));
    IconRender->setButtonType("ICON");

    
	animatorComponent* animator = new animatorComponent(*IconRender, animSpeed);
	mousePressButton* mpbFolder = new mousePressButton(ih, IconRender->getSprite()->getGlobalBounds(), "folderIcon");
	iconInputComponent* iconInputComp = new iconInputComponent(dT, &db, *inbox, buttonSheet, iconSheet);

	entityToModify.addComponent(IconRender);
    entityToModify.addComponent(label);
	entityToModify.addComponent(iconInputComp);
	entityToModify.addComponent(animator);
	entityToModify.addComponent(mpbFolder);
}

void ppc::spawnSettingsIcon(Entity& entityToModify, Desktop& dT, InputHandler& ih, Database& db, sf::Image& iconSheet, sf::Image& buttonSheet, float x, float y, float size, float animSpeed, ppc::Inbox* inbox) {
    

    // Label Component //
    sf::Font font;
    //font.loadFromFile(resourcePath() + "serife.ttf");
	font.loadFromFile(resourcePath() + "VT323-Regular.ttf");
    textLabelComponent* label = new textLabelComponent(font, sf::Color::White, x, y + size*128, 20, "Settings");
    
	/// Render Component ///
	buttonRenderComponent* IconRender = new buttonRenderComponent(iconSheet, 0, 1, 1, 2);
	IconRender->setImageScale(size, size);
	IconRender->renderPosition(sf::Vector2f(x, y));
    IconRender->setButtonType("ICON");


	// Animator (Update) Component ///
	animatorComponent* animator = new animatorComponent(*IconRender, animSpeed);

	/// Input Component ///
	mousePressButton* mpbIcon = new mousePressButton(ih, IconRender->getSprite()->getGlobalBounds(), "settingsIcon");
	iconInputComponent* iconInputComp = new iconInputComponent(dT, &db, *inbox, buttonSheet, iconSheet);

	entityToModify.addComponent(IconRender);
    entityToModify.addComponent(label);
	entityToModify.addComponent(iconInputComp);
	entityToModify.addComponent(animator);
	entityToModify.addComponent(mpbIcon);

}

void ppc::spawnChatIcon(Entity& entityToModify, Desktop& dT, InputHandler& ih, Database& db, sf::Image& iconSheet, sf::Image& buttonSheet, float x, float y, float size, float animSpeed, ppc::Inbox* inbox) {
    
    // Label Component //
    sf::Font font;
    //font.loadFromFile(resourcePath() + "consola.ttf");
	font.loadFromFile(resourcePath() + "VT323-Regular.ttf");
    textLabelComponent* label = new textLabelComponent(font, sf::Color::White, x, y + size*128, 20, "Chat");
    
    
	/// Render Component ///
	buttonRenderComponent* IconRender = new buttonRenderComponent(iconSheet, 0, 2, 1, 2);
	IconRender->setImageScale(size, size);
	IconRender->renderPosition(sf::Vector2f(x, y));
    IconRender->setButtonType("ICON");


	// Animator (Update) Component ///
	animatorComponent* animator = new animatorComponent(*IconRender, animSpeed);

	/// Input Component ///
	mousePressButton* mpbIcon = new mousePressButton(ih, IconRender->getSprite()->getGlobalBounds(), "chatIcon");
	iconInputComponent* iconInputComp = new iconInputComponent(dT, &db, *inbox, buttonSheet, iconSheet);

	entityToModify.addComponent(IconRender);
    entityToModify.addComponent(label);
	entityToModify.addComponent(iconInputComp);
	entityToModify.addComponent(animator);
	entityToModify.addComponent(mpbIcon);
}

void ppc::spawnSearchIcon(Entity& entityToModify, Desktop& dT, InputHandler& ih, Database* db, sf::Image& iconSheet, sf::Image& buttonSheet, float x, float y, float size, float animSpeed, ppc::Inbox* inbox) {
    
    /// Label Component ///
    sf::Font font;
    //font.loadFromFile(resourcePath() + "consola.ttf");
	font.loadFromFile(resourcePath() + "VT323-Regular.ttf");
    textLabelComponent* label = new textLabelComponent(font, sf::Color::White, x, y + size*128, 20, "Database");
    
	/// Render Component ///
	buttonRenderComponent* IconRender = new buttonRenderComponent(iconSheet, 0, 3, 1, 2);
	IconRender->setImageScale(size, size);
	IconRender->renderPosition(sf::Vector2f(x, y));
    IconRender->setButtonType("ICON");


	// Animator (Update) Component ///
	animatorComponent* animator = new animatorComponent(*IconRender, animSpeed);

	/// Input Component ///
	mousePressButton* mpbIcon = new mousePressButton(ih, IconRender->getSprite()->getGlobalBounds(), "searchIcon");
	iconInputComponent* iconInputComp = new iconInputComponent(dT, db, *inbox, buttonSheet, iconSheet);

	entityToModify.addComponent(IconRender);
    entityToModify.addComponent(label);
	entityToModify.addComponent(iconInputComp);
	entityToModify.addComponent(animator);
	entityToModify.addComponent(mpbIcon);
}

void ppc::spawnDataGraphIcon(Entity& entityToModify, Desktop& dT, InputHandler& ih, Database& db, sf::Image& iconSheet, sf::Image& buttonSheet, float x, float y, float size, float animSpeed, ppc::Inbox* inbox) {
    
    // Label Component //
    sf::Font font;
    //font.loadFromFile(resourcePath() + "consola.ttf");
	font.loadFromFile(resourcePath() + "VT323-Regular.ttf");
    textLabelComponent* label = new textLabelComponent(font, sf::Color::White, x, y + size*128, 20, "Graph");
    
	/// Render Component ///
	buttonRenderComponent* IconRender = new buttonRenderComponent(iconSheet, 0, 4, 1, 2);
	IconRender->setImageScale(size, size);
	IconRender->renderPosition(sf::Vector2f(x, y));
    IconRender->setButtonType("ICON");


	// Animator (Update) Component ///
	animatorComponent* animator = new animatorComponent(*IconRender, animSpeed);

	/// Input Component ///
	mousePressButton* mpbIcon = new mousePressButton(ih, IconRender->getSprite()->getGlobalBounds(), "dataGraphIcon");
	iconInputComponent* iconInputComp = new iconInputComponent(dT, &db, *inbox, buttonSheet, iconSheet);

	entityToModify.addComponent(IconRender);
    entityToModify.addComponent(label);
	entityToModify.addComponent(iconInputComp);
	entityToModify.addComponent(animator);
	entityToModify.addComponent(mpbIcon);
}

void ppc::spawnHelpIcon(Entity& entityToModify, Desktop& dT, InputHandler& ih, Database& db, sf::Image& iconSheet, sf::Image& buttonSheet, float x, float y, float size, float animSpeed, ppc::Inbox* inbox) {
    
    // Label Component //
    sf::Font font;
    //font.loadFromFile(resourcePath() + "consola.ttf");
	font.loadFromFile(resourcePath() + "VT323-Regular.ttf");
    textLabelComponent* label = new textLabelComponent(font, sf::Color::White, x, y + size*128, 20, "Help");
    
	/// Render Component ///
	buttonRenderComponent* IconRender = new buttonRenderComponent(iconSheet, 0, 5, 1, 2);
	IconRender->setImageScale(size, size);
	IconRender->renderPosition(sf::Vector2f(x, y));
    IconRender->setButtonType("ICON");


	// Animator (Update) Component ///
	animatorComponent* animator = new animatorComponent(*IconRender, animSpeed);

	/// Input Component ///
	mousePressButton* mpbIcon = new mousePressButton(ih, IconRender->getSprite()->getGlobalBounds(), "helpIcon");
	iconInputComponent* iconInputComp = new iconInputComponent(dT, &db, *inbox, buttonSheet, iconSheet);

	entityToModify.addComponent(IconRender);
    entityToModify.addComponent(label);
	entityToModify.addComponent(iconInputComp);
	entityToModify.addComponent(animator);
	entityToModify.addComponent(mpbIcon);
}

void ppc::spawnBrowserIcon(Entity& entityToModify, Desktop& dT, InputHandler& ih, Database& db, sf::Image& iconSheet, sf::Image& buttonSheet, float x, float y, float size, float animSpeed, ppc::Inbox* inbox) {
    
    // Label Component //
    sf::Font font;
    //font.loadFromFile(resourcePath() + "consola.ttf");
	font.loadFromFile(resourcePath() + "VT323-Regular.ttf");
    textLabelComponent* label = new textLabelComponent(font, sf::Color::White, x, y + size*128, 20, "Internet");
    
	/// Render Component ///
	buttonRenderComponent* IconRender = new buttonRenderComponent(iconSheet, 0, 6, 1, 1);
	IconRender->setImageScale(size, size);
	IconRender->renderPosition(sf::Vector2f(x, y));
    IconRender->setButtonType("ICON");


	// Animator (Update) Component ///
	animatorComponent* animator = new animatorComponent(*IconRender, animSpeed);

	/// Input Component ///
	mousePressButton* mpbIcon = new mousePressButton(ih, IconRender->getSprite()->getGlobalBounds(), "browserIcon");
	iconInputComponent* iconInputComp = new iconInputComponent(dT, &db, *inbox, buttonSheet, iconSheet);

	entityToModify.addComponent(IconRender);
    entityToModify.addComponent(label);
	entityToModify.addComponent(iconInputComp);
	entityToModify.addComponent(animator);
	entityToModify.addComponent(mpbIcon);
}

void ppc::spawnHardDriveIcon(Entity& entityToModify, Desktop& dT, InputHandler& ih, Database& db, sf::Image& iconSheet, sf::Image& buttonSheet, float x, float y, float size, float animSpeed, ppc::Inbox* inbox) {
    
    // Label Component //
    sf::Font font;
    //font.loadFromFile(resourcePath() + "consola.ttf");
	font.loadFromFile(resourcePath() + "VT323-Regular.ttf");
    textLabelComponent* label = new textLabelComponent(font, sf::Color::White, x, y + size*128, 20, "My Files");
    
	/// Render Component ///
	buttonRenderComponent* IconRender = new buttonRenderComponent(iconSheet, 0, 7, 1, 1);
	IconRender->setImageScale(size, size);
	IconRender->renderPosition(sf::Vector2f(x, y));
    IconRender->setButtonType("ICON");

	// Animator (Update) Component ///
	animatorComponent* animator = new animatorComponent(*IconRender, animSpeed);

	/// Input Component ///
	mousePressButton* mpbIcon = new mousePressButton(ih, IconRender->getSprite()->getGlobalBounds(), "hardDriveIcon");
	iconInputComponent* iconInputComp = new iconInputComponent(dT, &db, *inbox, buttonSheet, iconSheet);


	entityToModify.addComponent(IconRender);
    entityToModify.addComponent(label);
	entityToModify.addComponent(iconInputComp);
	entityToModify.addComponent(animator);
	entityToModify.addComponent(mpbIcon);
}

void ppc::spawnConsoleIcon(Entity& entityToModify, Desktop& dT, InputHandler& ih, Database& db, sf::Image& iconSheet, sf::Image& buttonSheet, float x, float y, float size, float animSpeed, ppc::Inbox* inbox) {
    
    
    /// Label Component ///
    sf::Font font;
    //font.loadFromFile(resourcePath() + "consola.ttf");
	font.loadFromFile(resourcePath() + "VT323-Regular.ttf");
    
    textLabelComponent* label = new textLabelComponent(font, sf::Color::White, x, y + size*128, 20, "Console");

	/// Render Component ///
	buttonRenderComponent* IconRender = new buttonRenderComponent(iconSheet, 0, 8, 1, 1);
	IconRender->setImageScale(size, size);
	IconRender->renderPosition(sf::Vector2f(x, y));
    IconRender->setButtonType("ICON");

	// Animator (Update) Component ///
	animatorComponent* animator = new animatorComponent(*IconRender, animSpeed);

	/// Input Components ///
	mousePressButton* mpbIcon = new mousePressButton(ih, IconRender->getSprite()->getGlobalBounds(), "consoleIcon");
	iconInputComponent* iconInputComp = new iconInputComponent(dT, &db, *inbox, buttonSheet, iconSheet);
	entityToModify.addComponent(IconRender);
    entityToModify.addComponent(label);
	entityToModify.addComponent(animator);
	entityToModify.addComponent(mpbIcon);
	entityToModify.addComponent(iconInputComp);


}

void ppc::spawnEmailIcon(Entity& entityToModify, Desktop& dT, InputHandler& ih, Database& db, sf::Image& iconSheet, sf::Image& buttonSheet, float x, float y, float size, float animSpeed, ppc::Inbox* inbox) {


	/// Label Component ///
	sf::Font font;
	//font.loadFromFile(resourcePath() + "consola.ttf");
	font.loadFromFile(resourcePath() + "VT323-Regular.ttf");

	textLabelComponent* label = new textLabelComponent(font, sf::Color::White, x, y + size * 128, 20, "Email");

	/// Render Component ///
	buttonRenderComponent* IconRender = new buttonRenderComponent(iconSheet, 0, 10, 1, 2);
	IconRender->setImageScale(size, size);
	IconRender->renderPosition(sf::Vector2f(x, y));
    IconRender->setButtonType("ICON");


    ppc::notificationRenderComponent* notiRenderComp = new ppc::notificationRenderComponent();
    ppc::NotificationObserver* test = &notiRenderComp->getNotiObserver();
    dT.getInbox().getInboxSubject().addObserver(test);
    notiRenderComp->setPosition({ x, y });

	// Animator (Update) Component ///
	animatorComponent* animator = new animatorComponent(*IconRender, animSpeed);

	/// Input Components ///
	mousePressButton* mpbIcon = new mousePressButton(ih, IconRender->getSprite()->getGlobalBounds(), "emailIcon");
	iconInputComponent* iconInputComp = new iconInputComponent(dT, &db, *inbox, buttonSheet, iconSheet);
	entityToModify.addComponent(IconRender);
	entityToModify.addComponent(label);
	entityToModify.addComponent(animator);
	entityToModify.addComponent(mpbIcon);
	entityToModify.addComponent(iconInputComp);
    entityToModify.addComponent(notiRenderComp);

}


