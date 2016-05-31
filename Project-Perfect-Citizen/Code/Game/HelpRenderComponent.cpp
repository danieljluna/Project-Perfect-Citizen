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


    consoleHelpString = "--------------------- CONSOLE REFERENCE --------------------";
    consoleHelpString += "\n\n pwd : Prints the current working directory";
    consoleHelpString += "\n\n cd [path] : changes the current directory";
    consoleHelpString += "\n\n ls : lists the contents of the current directory";
    consoleHelpString += "\n\n unlock [path] [password] : Unlocks the directory at the \n specified path";
    consoleHelpString += "\n\n help : Displays a list of possible console commands";
    


    graphHelpString = "------------------------ GRAPH REFERENCE --------------------\n\n";
	graphHelpString += " Node Selection: Left Click on a node, node will be highlighted.\n";
	graphHelpString += " (Edges will be deselected)\n\n";
	graphHelpString += " Edge Selection : Left click on an edge(Nodes will be deselected)\n\n";
	graphHelpString += " Node Position : Click and drag a node to reposition it.\n";
	graphHelpString += " Edges are updated automatically.\n";
	graphHelpString += " Node position is to help you work towards a solution, \n";
	graphHelpString += " and does not affect correctness.\n\n";
	graphHelpString += " Change Color of Selected Edge : \n";
	graphHelpString += "   A - Black, \n";
	graphHelpString += "   S - Red, \n";
	graphHelpString += "   D - Green, \n";
	graphHelpString += "   Space - Cycle Color.\n\n";
	graphHelpString += " Edge Color Significance : \n";
	graphHelpString += "   Black - Unknown, \n";
	graphHelpString += "   Red - Suspicious, \n";
	graphHelpString += "   Green - Clean.\n\n";
	graphHelpString += " Create an Edge : Select a node, then right click the node\n ";
	graphHelpString += " you want to connect it to.\n\n";
	graphHelpString += " Delete an Edge : Select the edge, press Z\n\n";
	graphHelpString += " Mark Center of Graph : Select a node, press C\n\n";
	graphHelpString += " Submit : Use the botton at the bottom\n\n";
	graphHelpString += "--------------- ADVANCED PIPELINE CONTROLS ----------------\n\n";
	graphHelpString += " To create an edge of a specific color, hold :\n";
	graphHelpString += "   Alt - Black\n";
	graphHelpString += "   Shift - Red\n";
	graphHelpString += "   Ctrl - Green\n";
	graphHelpString += " While creating an edge.\n";
 

	desktopsHelpString = "-------------- DESKTOP EXTRACTION REFERENCE ---------------\n\n";
	desktopsHelpString += " Your job at the DCPS will involve you piping into virtual machines\n";
	desktopsHelpString += "of live desktops in order to find what you believe to be malicious\n";
	desktopsHelpString += "content. Your goal is to 'flag' the three most suspicious files you\n";
	desktopsHelpString += "find on the desktop. \n\n";
	desktopsHelpString += " To do this, simply right click a file and select 'Flag' \n\n";
	desktopsHelpString += " Notice your file will appear in the window with three file icons.\n";
	desktopsHelpString += "This 'Suspicious File Holder' window will track your progess.\n";
	desktopsHelpString += "Remember, you may only flag three files per Desktop extraction and \n";
	desktopsHelpString += "no file can be flagged more than once. \n\n";
	desktopsHelpString += " If you're unsure of the suspiciousness of a file, right click it\n";
	desktopsHelpString += "and select 'Scan'. \n\n";
	desktopsHelpString += " The virtual machine will compare the file against our database\n";
	desktopsHelpString += "of known criminal data and deliver you a suspiciousness report\n";
	desktopsHelpString += "ranging from 1-10. 1's are considered the least suspicious reports \n";
	desktopsHelpString += "while 10's are considered extremely dangerous. Please note that in \n"; 
	desktopsHelpString += "order to prevent a security breach on SecureNet servers, the DCPS \n";
	desktopsHelpString += "will only grant 3 scans per Desktop Extraction. Use them wisely!\n\n";
	desktopsHelpString += " When you are done, click 'Submit' in the file holder to complete\n";
	desktopsHelpString += "your desktop extraction. \n\n";
	desktopsHelpString += " Note: The DCPS recommends looking at all potential files before\n";
	desktopsHelpString += "submitting your evidence. Non-suspicious evidence may result in\n";
	desktopsHelpString += "delayed sentencing or unrightful exoneration. \n";

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
		case 2:
			contentText->setString(desktopsHelpString);
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
bool ppc::swithTab2Fn(HelpWindowRenderComponent* h, Event ev) {
	h->setTab(2);
	return true;
}

