#include "LoginInputCmpnt.h"
#include "../Engine/event.h"
#include "TextBoxInputComponent.h"
#include "../Engine/Window.h"
#include "ConfirmWindowBuilder.h"
#include "../Engine/World.h"
#include "../Engine/desktop.h"
#include "createWindow.h"
#include "Save.h"
#include "../ResourceDef.h"


#include <fstream>

using namespace ppc;

LoginInputCmpnt::LoginInputCmpnt(WindowInterface& ownerWin, 
                                 TextBoxInputComponent* textBox) :
    currWindow_(&ownerWin), textBox_(textBox) {
}

void LoginInputCmpnt::setTextBox(TextBoxInputComponent& tBox) {
    textBox_ = &tBox;
}

bool LoginInputCmpnt::registerInput(Event ev) {
    return false;
}

void LoginInputCmpnt::loadSave() {
    Save sav;

    sav.importSave(textBox_->getString());
    World::currSave = sav;

    World::quitDesktop();

}


bool LoginInputCmpnt::findSave() {
    bool result = false;
    if (textBox_ != nullptr) {
        std::ifstream inTest(resourcePath() + "Saves/" + textBox_->getString() + ".sav");
        result = inTest.good();
    }

    return result;
}


void LoginInputCmpnt::createSave() {
    WindowInterface* loginConfirm =
        new Window(400, 110, sf::Color(170, 170, 170));

    ConfirmWindowBuilder builder;
    builder.setButtonLabelFont(World::getFont(World::FontList::Consola));
    builder.setCancelButtonLabel("No");
    builder.setConfirmButtonLabel("Yes");
    builder.setConfirmMessage("Are you sure you want to create \na new user?\n(This will create a new save file)");
    builder.setMessageFont(World::getFont(World::FontList::Consola));
    builder.setMessageFontSize(12);
    builder.setPosition(currWindow_->getPosition() + sf::Vector2f(25, 50));
    builder.setSpriteSheet(World::getCurrDesktop().getButtonSheet());
    builder.setWindowCaption("");
    createWithEventFunc(builder, loginConfirm, this, ppc::create_save);

    currWindow_->createNotifWindow(loginConfirm);
}



bool ppc::registerLogIn(LoginInputCmpnt* loginCmpnt, ppc::Event ev) {
    if (loginCmpnt->findSave()) {
        loginCmpnt->loadSave();
    } else {
        loginCmpnt->createSave();
    }

    return false;
}



bool ppc::create_save(LoginInputCmpnt* loginCmpnt, ppc::Event) {
    Save sav;
    sav.exportSave(loginCmpnt->textBox_->getString());
    World::currSave = sav;

    World::quitDesktop();

    return false;
}