#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../Engine/renderComponent.h"
#include "../Engine/NodeState.h"
#include <string>

using namespace std;

///////////////////////////////////////////////////////////////////////
/// @brief Designated Render Component for an Text Input Box
/// @author Michael Lowe / Alex Vincent
/// @details write this later
///////////////////////////////////////////////////////////////////////
class textInputRenderComponent : public ppc::RenderComponent{
private:
	ppc::NodeState& fileTree_;
    sf::Sprite* sprite;
    sf::Text* text;
    sf::Font font;
    string str;
    int textSize_;

public:
    
    textInputRenderComponent(ppc::NodeState& fT, sf::Font& f, int x, int y, int size);
    
    ~textInputRenderComponent();
    
    sf::Sprite* getSprite() const {return sprite;}
    
    ////////////////////////////////////////////////////////////////////
    /// @brief updateString recieves a string from an input component to
    ///        display.
    /// @param s is the string recieved from the input component
    ////////////////////////////////////////////////////////////////////
    void updateString(string s);

	////////////////////////////////////////////////////////////////////
	/// @brief Updates the console prompt position in the window based
	/// on the amount of current lines
	/// @param integer specifying the amount of currently displayed 
	/// lines. This will draw it one line below these number of lines
	////////////////////////////////////////////////////////////////////
	void updatePosition(int currentLineNum);

    virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
    
    virtual void recieveMessage(msgType code) override;

};