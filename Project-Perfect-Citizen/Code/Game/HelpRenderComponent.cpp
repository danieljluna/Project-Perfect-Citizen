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
#include "../Engine/event.h"

using namespace ppc;

HelpWindowRenderComponent::HelpWindowRenderComponent(sf::Font& f, int x, int y, int size) : font(f) {
    
    this->contentText = new sf::Text();
    contentText->setFont(font);
    contentText->setColor(sf::Color::Black);
    contentText->setCharacterSize(size-1);
    contentText->setPosition(static_cast<float>(x), static_cast<float>(y));
    
    tab = 0;


    consoleHelpString = "--------------------- CONSOLE REFERENCE --------------------\n";
    consoleHelpString += "\n\n Commands \n\n pwd : prints the current working directory";
    consoleHelpString += "\n\n pwd : Prints the current working directory";
    consoleHelpString += "\n\n cd [path] : changes the current directory";
    consoleHelpString += "\n\n ls : lists the contents of the current directory";
    consoleHelpString += "\n\n unlock [path] [password] : Unlocks the directory at the \n specified path";
    consoleHelpString += "\n\n help : Displays a list of possible console commands";
    


    graphHelpString = "--------------------- GRAPH REFERENCE --------------------\n";
    graphHelpString += "Node Selection: Left Click on a node, node will be highlighted.\n (Edges will be deselected)\n Edge Selection: Left click on an edge (Nodes will be deselected)\n\n  Node Position: Click and drag a node to reposition it.\n Edges are updated automatically.\n Node position is to help you work towards a solution,\n and does not affect correctness.\n\n Change Color of Selected Edge: \n Z - Black,\n X - Red,\n  C - Green,\n Space - Cycle Color.  \n  \n Edge Color Significance:\n Black - Unknown,\n Red - Suspicious,\n Green - Clean.\n\n Create an Edge: Select a node, then right click the node\n you want to connect it to.\n \n  Delete an Edge:\n Select the edge, press DEL Mark Center of Graph\n - S Submit for Approval\n - Okay Button For this first trial you will simply be searching\nfor the person with the highest total number of connections.\n You must still fill out the rest of the network\nwith high accuracy to receive approval.";
 

    contentText->setString(consoleHelpString);
    
   /* helpContentBox.setPosition(sf::Vector2f(0.0f, 0.0f));
    helpContentBox.setFillColor(sf::Color::White);
    helpContentBox.setSize(sf::Vector2f(float(winWidth+size), float(winHeight-100)));*/
}

HelpWindowRenderComponent::~HelpWindowRenderComponent() {
}

void HelpWindowRenderComponent::setTab(int t) {
    tab = t;
    switch (tab) {
        case 0:
            contentText->setString(consoleHelpString);
            break;
        case 1:
            contentText->setString(graphHelpString);
            break;
        default:
            break;
    }
}

void HelpWindowRenderComponent::draw(sf::RenderTarget& target,
                                       sf::RenderStates states) const {
    target.draw(this->helpContentBox, states);
    target.draw(*(this->contentText), states);
}

void HelpWindowRenderComponent::recieveMessage(msgType code) {

}


bool ppc::swithTab0Fn(HelpWindowRenderComponent* h, Event ev){
    h->setTab(0);
    return true;
}
bool ppc::swithTab1Fn(HelpWindowRenderComponent* h, Event ev){
    h->setTab(1);
    return true;
}

