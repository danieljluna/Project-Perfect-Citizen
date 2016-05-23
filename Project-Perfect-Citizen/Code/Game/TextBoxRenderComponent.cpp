#include "../Engine/debug.h"
#include "../Engine/event.h"
#include "../Engine/Entity.h"
#include "TextBoxRenderComponent.h"



using namespace ppc;

TextBoxRenderComponent::TextBoxRenderComponent(sf::Font& f, sf::Color c,
	float x,
	float y,
	int s,
	std::string str) : font(f) {

	this->text = new sf::Text();
	this->outline = new sf::Text();

	labelString = str;

	size_t pos = 0;

	for (unsigned int i = 0, j = 0; i < labelString.size(); ++i, ++j) {
		if (labelString.at(i) == '_' && j > 5) {
			labelString.insert(i, "\n");
			i++;
			j = 0;
		}
	}

	text->setFont(font);
	text->setPosition(x, y);
	text->setCharacterSize(s);
	text->setColor(c);
	text->setString(labelString);

	outline->setFont(font);
	outline->setPosition(x + 2, y);
	outline->setCharacterSize(s);
	if (text->getColor() == sf::Color::Black)
		outline->setColor(sf::Color::White);
	else outline->setColor(sf::Color::Black);
	outline->setString(labelString);

}

TextBoxRenderComponent::~TextBoxRenderComponent() {
	delete text;
	delete outline;
}

void TextBoxRenderComponent::updateLabelPosition(float x, float y) {
	text->setPosition(x, y);
}

void TextBoxRenderComponent::updateLabelSize(int s) {
	text->setCharacterSize(s);
}

void TextBoxRenderComponent::setIsMasked(bool m)
{
	isMasked = m;
}

void ppc::TextBoxRenderComponent::toggleCursorRender()
{
	renderCursor = !renderCursor;
}

void ppc::TextBoxRenderComponent::setCursorRender(bool r)
{
	renderCursor = r;
}

std::string ppc::TextBoxRenderComponent::getString()
{
	return labelString;
}

void TextBoxRenderComponent::updateLabelString(std::string str) {
	labelString = str;

	if (isMasked) labelString.replace(0, str.length(), str.length(), '*');

	if (renderCursor)
		outline->setString(labelString+"|");
	else 
		outline->setString(labelString);
}

void TextBoxRenderComponent::draw(sf::RenderTarget& target,
	sf::RenderStates states) const {

	target.draw(*(this->outline), states);
	//target.draw(*(this->text), states);
}


bool ppc::blink_cursor(TextBoxRenderComponent * tbr, ppc::Event ev)
{
	tbr->toggleCursorRender();
	tbr->updateLabelString(tbr->getString());
	ev.type = Event::EventTypes::TimerType;
	ev.timer.action = Event::TimerEv::timerState::Reset;
	tbr->getEntity()->broadcastMessage(ev);
	return true;
}
