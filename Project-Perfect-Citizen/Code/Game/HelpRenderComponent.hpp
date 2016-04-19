#pragma once

#include "../Engine/renderComponent.h"
#include "Email.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace sf {
    class Sprite;
    class Text;
};

///////////////////////////////////////////////////////////////////////
/// @brief Help Window Render Component
/// @author Michael
/// @details basically a tab view
///////////////////////////////////////////////////////////////////////

namespace ppc {
    

    class HelpWindowRenderComponent : public ppc::RenderComponent {
    private:
        
        ///////////////////////////////////////////////////////////////////////
        /// @brief The bounding box containing the emails contents
        ///////////////////////////////////////////////////////////////////////
        sf::RectangleShape helpContentBox;
        
        ///////////////////////////////////////////////////////////////////////
        /// @brief The rendered text for the emails contents
        ///////////////////////////////////////////////////////////////////////
        std::string consoleHelpString;
        std::string graphHelpString;
        sf::Text* contentText;
        
        sf::Font font;
        
        int tab;
    
        
    public:
        
        ///////////////////////////////////////////////////////////////////////
        /// @brief Constructor
        /// @param The font of the text to be rendered
        /// @param The x position of the rendered text
        /// @param The y position of the rendered text
        ///////////////////////////////////////////////////////////////////////
        HelpWindowRenderComponent(sf::Font& f, int x, int y, int size);
        
        ~HelpWindowRenderComponent();
        
        void setTab(int t);
        
        virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
        
        virtual void recieveMessage(msgType code) override;
        
        
    };
    
    bool swithTab0Fn(HelpWindowRenderComponent*, Event);
    bool swithTab1Fn(HelpWindowRenderComponent*, Event);
    
};