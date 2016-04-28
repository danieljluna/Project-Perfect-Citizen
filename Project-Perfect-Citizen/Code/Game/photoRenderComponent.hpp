#ifndef photoRenderComponent_hpp
#define photoRenderComponent_hpp

#include <SFML/Graphics.hpp>
#include "../Engine/renderComponent.h"


namespace ppc {

///////////////////////////////////////////////////////////////////////
/// @brief Designated Render Component for a generic window 'X' button
/// @author Brandon Gomez
/// @details The photoRenderComponent is a basic packaged subclass
///     extension of RenderComponent, make specifically to handle
///     all generic "X" button related drawing parts that
///     also broadcast and recieve messages from an input handler.
///		Stick this onto an entity to give it this functionality.
///////////////////////////////////////////////////////////////////////
class photoRenderComponent : public ppc::RenderComponent{
private:
    sf::Sprite* sprite;
    sf::Texture* texture;
    sf::Image& image;

public:
    ///////////////////////////////////////////////////////////////////////
    /// @brief Constructor for photoRenderComponent
    /// @param image is the String of a file path of an image
    ///////////////////////////////////////////////////////////////////////
    photoRenderComponent(sf::Image& image);
    
    ///////////////////////////////////////////////////////////////////////
    /// @brief Sets the X/Y scale of the square image texture of the photo
    ///////////////////////////////////////////////////////////////////////
    void setImageScale(float ScaleX, float ScaleY);
    
    ///////////////////////////////////////////////////////////////////////
    /// @brief The main draw function that was inheirted from RenderComponent.
    /// @details You need to define this to create a child of RenderComponent
    /// @param target: This is almost always going to be a sf::renderWindow. states:
    /// This is used to dictate certain states that the object can be rendered in.
    /// For now this can be safely "ignored" Just created a RenderStates object and
    /// shove it in there.
    ///////////////////////////////////////////////////////////////////////
    virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
    
};


};

#endif /* photoRenderComponent_hpp */
