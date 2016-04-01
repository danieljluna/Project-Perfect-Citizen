#include "ButtonBuilder.h"
#include "buttonRenderComponent.h"
#include "../Game/mousePressButton.h"
#include <ostream>

ppc::ButtonBuilder::ButtonBuilder() 
{
	sheetX = 0;
	sheetY = 0;
	width = 0;
	frames = 0;
	size = 1;

	posX = 0.f;
	posY = 0.f;

}

ppc::ButtonBuilder::~ButtonBuilder()
{
}

void ppc::ButtonBuilder::setSpritesByIndicies(int x, int y, int r, int f)
{
	sheetX = x;
	sheetY = y;
	width = r;
	frames = f;
}

void ppc::ButtonBuilder::setSprites(sf::Sprite&, sf::Sprite&)
{

}

void ppc::ButtonBuilder::setButtonPosition(float x, float y)
{
	posX = x;
	posY = y;
}

void ppc::ButtonBuilder::setButtonPosition(sf::Vector2f pos)
{
	posX = pos.x;
	posY = pos.y;
}

void ppc::ButtonBuilder::setSpriteSheet(sf::Image& sheet)
{
	spriteSheet = &sheet;
}

void ppc::ButtonBuilder::setInputHandle(ppc::InputHandler& ih)
{
	inputHandle = &ih;
}

void ppc::ButtonBuilder::create(Entity& e)
{
	buttonRenderComponent* buttonRender = 
		new buttonRenderComponent(*spriteSheet, sheetX, sheetY, width, frames);

	buttonRender->setImageScale(size, size);
	buttonRender->renderPosition(sf::Vector2f(posX, posY));

	/* Input Component*/
	mousePressButton* mpb = new mousePressButton(*inputHandle, buttonRender->getSprite()->getGlobalBounds(), "startButton");

	e.addComponent(buttonRender);
	e.addComponent(mpb);
	buttonRender->renderPosition(sf::Vector2f(posX, posY));

	std::cout << "built!";

}

