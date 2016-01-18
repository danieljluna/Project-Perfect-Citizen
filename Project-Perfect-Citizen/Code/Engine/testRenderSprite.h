#pragma once
#include <SFML/Graphics.hpp>
#include "renderComponent.h"
#include <string>
using namespace std;
class TestRenderSprite : public RenderComponent {
private:
	int privatePlaceholder;
	sf::Sprite* sprite;
	sf::Texture* texture;
	int vectorIndex;
public:
	TestRenderSprite(string filename);
	void render(sf::RenderWindow* wnd);
	sf::Sprite* getSprite();
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const ;
	int getVectorIndex();
	~TestRenderSprite();
};