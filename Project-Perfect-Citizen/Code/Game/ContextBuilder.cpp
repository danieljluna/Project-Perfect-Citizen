#include "ContextBuilder.h"
#include "contextListElementRenderComponent.h"
#include "TextDisplayRenderComponent.h"
#include "mousePressButton.h"

ppc::ContextBuilder::ContextBuilder()
{
	containingWindow = nullptr;
	inputHandle = nullptr;

	/* List Element Label (String) */
	labelFont = sf::Font();
	label = "DEFAULT_VALUE";
	labelSize = 0;
	labelX = 0;
	labelY = 0;

	boxX = 0;
	boxY = 0;
	boxWidth = 0;
	boxHeight = 0;
}

ppc::ContextBuilder::~ContextBuilder()
{
}

void ppc::ContextBuilder::setLabelMessage(std::string l)
{
	label = l;
}

void ppc::ContextBuilder::setLabelFont(sf::Font f)
{
	labelFont = f;
}

void ppc::ContextBuilder::setLabelSize(int s)
{
	labelSize = s;
}

void ppc::ContextBuilder::setListElementPosition(float x, float y)
{
	boxX = x;
	boxY = y;
}

void ppc::ContextBuilder::setListElementPosition(sf::Vector2f pos)
{
	boxX = pos.x;
	boxY = pos.y;
}

void ppc::ContextBuilder::setListElementSize(sf::Vector2f pos)
{
	boxWidth = pos.x;
	boxHeight = pos.y;
}

void ppc::ContextBuilder::setInputHandle(ppc::InputHandler& ihndl)
{
	inputHandle = &ihndl;
}

void ppc::ContextBuilder::setContainingWindow(ppc::WindowInterface * win)
{
	containingWindow = win;
}

void ppc::ContextBuilder::create(Entity & ent)
{
	contextListElementRenderComponent* rc = new contextListElementRenderComponent(
		containingWindow, labelFont, label, boxX, boxY, boxWidth, boxHeight, labelX,
		labelY, labelSize);

	TextDisplayRenderComponent* rc2 = new TextDisplayRenderComponent(labelFont, 
		sf::Color::Black, labelX, labelY, labelSize, label);

	mousePressButton* ic = new mousePressButton(*inputHandle, rc->getListElementBoxBounds());

	ent.addComponent(rc);
	ent.addComponent(rc2);
	ent.addComponent(ic);
}
