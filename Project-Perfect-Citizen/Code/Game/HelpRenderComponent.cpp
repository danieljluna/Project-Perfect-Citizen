//
//  HelpRenderComponent.cpp
//  Project-Perfect-Citizen
//
//  Created by Michael Lowe on 4/15/16.
//  Copyright © 2016 Hyperfocus Games. All rights reserved.
//

#include "HelpRenderComponent.hpp"


#include "emailMessageRenderComponent.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

using namespace ppc;

HelpWindowRenderComponent::HelpWindowRenderComponent(sf::Font& f, int x, int y, int size) : font(f) {
    
    this->contentText = new sf::Text();
    contentText->setFont(font);
    contentText->setColor(sf::Color::Black);
    contentText->setCharacterSize(size-1);
    contentText->setPosition(x, y);
    
    tab = 0;


    consoleHelpString = "--------------------- CONSOLE REFERENCE --------------------\n";
    consoleHelpString += "\n\n Commands \n\n pwd : prints the current working directory";
    consoleHelpString += "\n\n cd [path] : changes the current directory";
    consoleHelpString += "\n\n ls : lists the contents of the current directory";
    consoleHelpString += "\n\n make [filename][contents] : creates a new text file";
    consoleHelpString += "\n\n mkdir [name] : creates a new directory";


    
    contentText->setString(consoleHelpString);
    
   /* helpContentBox.setPosition(sf::Vector2f(0.0f, 0.0f));
    helpContentBox.setFillColor(sf::Color::White);
    helpContentBox.setSize(sf::Vector2f(float(winWidth+size), float(winHeight-100)));*/
}

HelpWindowRenderComponent::~HelpWindowRenderComponent() {
}

void HelpWindowRenderComponent::setTab(int t) {
    tab = t;
}


void HelpWindowRenderComponent::draw(sf::RenderTarget& target,
                                       sf::RenderStates states) const {
    target.draw(this->helpContentBox, states);
    target.draw(*(this->contentText), states);
}

void HelpWindowRenderComponent::recieveMessage(msgType code) {

}