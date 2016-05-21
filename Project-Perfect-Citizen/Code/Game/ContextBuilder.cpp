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

void ppc::ContextBuilder::setLabelPosition(sf::Vector2f pos)
{
	labelX = static_cast<int>(pos.x);
	labelY = static_cast<int>(pos.y);
}

void ppc::ContextBuilder::setListElementPosition(float x, float y)
{
	boxX = static_cast<int>(x);
	boxY = static_cast<int>(y);
}

void ppc::ContextBuilder::setListElementPosition(sf::Vector2f pos)
{
	boxX = static_cast<int>(pos.x);
	boxY = static_cast<int>(pos.y);
}

void ppc::ContextBuilder::setListElementSize(sf::Vector2f pos)
{
	boxWidth = static_cast<int>(pos.x);
	boxHeight = static_cast<int>(pos.y);
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
		sf::Color::Black, static_cast<float>(labelX), static_cast<float>(labelY), labelSize, label);

	mousePressButton* ic = new mousePressButton(*inputHandle, rc->getListElementBoxBounds());

	ent.addComponent(rc);
	ent.addComponent(rc2);
	ent.addComponent(ic);
}
