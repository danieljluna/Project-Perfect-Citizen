
#ifndef characterRender_hpp
#define characterRender_hpp

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "../Engine/renderComponent.h"
#include <string>
#include <vector>
#include "PipelineCharacter.h"

using namespace ppc;

///////////////////////////////////////////////////////////////////////
/// @brief Character Generator class for use by the PCG system.
/// @author Micahel Lowe
/// @details Character Generator class to create modular / proceedural
///           characters for use by the pipeline game.
///////////////////////////////////////////////////////////////////////
class characterRender : public ppc::RenderComponent{
private:
    
    sf::Texture* texture;
    sf::Image& faceImage;
    
    
    ///// Body //////
    sf::Sprite* body;
    sf::Sprite* shirt;
    
    sf::Sprite* hair;
    
    ///// Eyes //////
    sf::Sprite* irisL;
    sf::Sprite* irisR;
    sf::Sprite* eyeL;
    sf::Sprite* eyeR;
    
    sf::Sprite* browL;
    sf::Sprite* browR;
    ///// Mouth //////
    sf::Sprite* mouth;
    
    ///// Mouth //////
    sf::Sprite* nose;

    // A vector that holds all possible skin tones
    std::vector<sf::Color> skinTones;
    std::vector<sf::Color> hairTones;
    std::vector<sf::Color> lipTones;
    
    // The skin tone of the character.
    // A randomly selected element from skinTones

   // sf::Color shirtColor;
    
    /*
    int eyeType, browType, mouthType, noseType, skinType, lipType, hairStyle, hairType;
    sf::Color eyeColor;*/
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
    /// @brief Applies the randomly generated values to drawable sprites
    ////////////////////////////////////////////////////////////////////
    void applyCharacterValues(PipelineCharacter& myCharacter);
    
    
    ////////////////////////////////////////////////////////////////////
    /// @brief Generates a random set of character values
    ////////////////////////////////////////////////////////////////////
  //  void generateCharacterValues();
    
    ////////////////////////////////////////////////////////////////////
    /// @brief initializes vector of skin tones
    ////////////////////////////////////////////////////////////////////
    void initializeSkinTones();
    
    void initializeHairTones();
    
    
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
