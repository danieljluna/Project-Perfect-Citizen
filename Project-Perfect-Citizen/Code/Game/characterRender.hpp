
#ifndef characterRender_hpp
#define characterRender_hpp

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "../Engine/renderComponent.h"
#include <string>

using namespace std;

///////////////////////////////////////////////////////////////////////
/// @brief Character Generator class for use by the PCG system.
/// @author Micahel Lowe
/// @details Character Generator class to create modular / proceedural
///           characters for use by the pipeline game.
///////////////////////////////////////////////////////////////////////
class characterRender : public ppc::RenderComponent{
private:
    
    ///// Eyes //////
    sf::Sprite* irisL;
    sf::Sprite* irisR;
    sf::Sprite* eyeL;
    sf::Sprite* eyeR;
    
    sf::Texture* texture;
    sf::Image& faceImage;
    int height, xIndex, yIndex;
    static const int grid_size = 128;
    static const int combinations = 3;
    
public:
    ////////////////////////////////////////////////////////////////////
    /// @brief Constructor for buttonRenderComponent
    /// @param image is the String of a file path of a .png file
    ////////////////////////////////////////////////////////////////////
    characterRender(sf::Image& image);
    
    ~characterRender();
    
    
    ////////////////////////////////////////////////////////////////////
    /// @brief Generates The Character's Eye
    /// @details Recieves a color from generateEyeColor
    /// Recieves an integer from generateEyeType, which corresponds to a
    /// location on the texture grid.
    ////////////////////////////////////////////////////////////////////
    void setCharacterEye();
    
    ////////////////////////////////////////////////////////////////////
    /// @brief Returns a color for the characters eye
    ////////////////////////////////////////////////////////////////////
    sf::Color generateEyeColor();
    
    
    ////////////////////////////////////////////////////////////////////
    /// @brief Returns an integer to be read as a y location on texture
    ////       grid.
    /// @details As of now the range of possible types is 0-3
    ////////////////////////////////////////////////////////////////////
    int generateEyeType();
     
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


#endif /* characterGenerator_hpp */
