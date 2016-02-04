#pragma once
#include <SFML/Graphics.hpp>
#include "renderComponent.h"
#include <string>

using namespace std;

/////////////////////////////////////////////////////////////
/// @brief and example class inheiritng from RenderComponent!
/// @details I made this class to help anyone in creating a 
/// renderComponent child Class. Dont be afraid to ask questions
/// and use this as a template!
/////////////////////////////////////////////////////////////
class TestRenderSprite : public ppc::RenderComponent {
private:
	sf::Sprite* sprite;
    //TODO: Remove unique texture: Let the Sprite refernce the correct 
    ///     one
	sf::Texture* texture;
    static const int size = 128;

public:

///////////////////////////////////////////////////////////////////////
/// @brief Constructor for TestRenderSprite
/// @param filname is the String of a file path of a .png file
///////////////////////////////////////////////////////////////////////
    TestRenderSprite(sf::Image& image, int x, int y, int r);

	~TestRenderSprite();

    void renderPosition(sf::Vector2f pos);

///////////////////////////////////////////////////////////////////////
/// @brief Returns a pointer to sprite
///////////////////////////////////////////////////////////////////////
	sf::Sprite* getSprite();

///////////////////////////////////////////////////////////////////////
/// @brief The main draw function that was inheirted from RenderComponent.
/// @details You need to define this to create a child of RenderComponent
/// @param target: This is almost always going to be a sf::renderWindow. states:
/// This is used to dictate certain states that the object can be rendered in. 
/// For now this can be safely "ignored" Just created a RenderStates object and
/// shove it in there. 
///////////////////////////////////////////////////////////////////////
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const ;



};
