
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
    
    bool shouldDraw_;
    
    float scale;
    
    static sf::Texture texture;
    static bool textureIsLoaded;
    
    
    ///// Body //////
    sf::Sprite body;
    sf::Sprite shirt;
    
    sf::Sprite hair;
    
    ///// Eyes //////
    sf::Sprite irisL;
    sf::Sprite irisR;
    sf::Sprite eyeL;
    sf::Sprite eyeR;
    
    sf::Sprite browL;
    sf::Sprite browR;
    ///// Mouth //////
    sf::Sprite mouth;
    
    ///// Mouth //////
    sf::Sprite nose;

	// (2*window.width)/3
	sf::Vector2f origin;

    // A vector that holds all possible skin tones
    std::vector<sf::Color> skinTones;
    std::vector<sf::Color> hairTones;
    std::vector<sf::Color> lipTones;
    
    static const int grid_size = 128;
    static const int combinations = 3;
    
    float bodyScale,eyeScale,mouthScale,noseScale;
    sf::Vector2f hairPos;
    sf::Vector2f eyeLPos;
    sf::Vector2f eyeRPos;
    sf::Vector2f browLPos;
    sf::Vector2f browRPos;
    sf::Vector2f mouthPos;
    sf::Vector2f nosePos;
    
public:
    ////////////////////////////////////////////////////////////////////
    /// @brief Constructor for buttonRenderComponent
    /// @param image is the String of a file path of a .png file
    /// @param s is the scale of the render
    ////////////////////////////////////////////////////////////////////
    characterRender(sf::Image& image);
    
    ~characterRender();
    
    bool shouldDraw() const {return shouldDraw_;}
    
    void setShouldDraw(bool d);
    
	void setOrigin(float x, float y);
    
    ////////////////////////////////////////////////////////////////////
    /// @brief Applies the randomly generated values to drawable sprites
	/// @param myCharacter is a Pipeline Character passed in from the 
	///					   Database.
    ////////////////////////////////////////////////////////////////////
    void applyCharacterValues(PipelineCharacter& myCharacter);
    
 
	////////////////////////////////////////////////////////////////////
	/// @brief initializes vector of skin, hair, and lip tones
	////////////////////////////////////////////////////////////////////
    void initializeTones();
    
    
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


/*
 
 Constants Small
 
 Body Scale = 0.16f
 Body Position = Origin
 
 Shirt Scale = 0.16f
 Shirt Position = Origin
 
 
 Hair Scale = 0.16f
 Hair Position = +18, +2
 
 
 IrisL Scale = 0.12f
 IrisL Position = +32, + 32
 
 IrisR scale = 0.12f
 IrisR Position = +52, +32
 
 EyeL Scale = .012f
 EyeL Position = +32, +32
 
 EyeR Scale = 0.12f
 EyeR Position = +52, +32
 
 BrowR Scale = 0.12f
 BrowR Position = +52, + 25
 
 BrowL Scale = 0.12f
 BrowL Position = +32, +25
 
 
 Mouth Scale = 0.08f
 Mouth Position = 40, 55
 
 Nose Scale = 0.09f
 Nose Position = 56, 36
 

 */

