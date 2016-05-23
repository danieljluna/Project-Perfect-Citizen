#include <SFML/Graphics/RenderTarget.hpp>

#include "../Engine/debug.h"
#include "../Engine/event.h"
#include "../Engine/World.h"
#include "../Engine/desktop.h"
#include "../Engine/Entity.h"
#include "startBarRenderComponent.hpp"
#include <iomanip>
#include <sstream>
#include <ctime>
#include <cstdio>

using namespace ppc;

startBarRenderComponent::startBarRenderComponent(sf::Font& font) {
    dateFont = font;
    dateText.setFont(dateFont);
    dateText.setCharacterSize(12);
    dateText.setColor(sf::Color::Black);
    dateText.setPosition({static_cast<float>(World::getGameScreen().getSize().x-180),30});
    std::string d_string = getCurrentTime();
    dateText.setString(d_string);
    
    
    startBar.setFillColor(sf::Color(170,170,170));
    startBar.setSize({static_cast<float>(World::getGameScreen().getSize().x),65});
    startBar.setPosition(0,0);
    
    blackBorder.setFillColor(sf::Color::Black);
    blackBorder.setSize({static_cast<float>(World::getGameScreen().getSize().x),75});
    blackBorder.setPosition(0,-2);
    
    blackBorder.setFillColor(sf::Color::White);
    blackBorder.setSize({static_cast<float>(World::getGameScreen().getSize().x),75});
    blackBorder.setPosition(0,-4);
    
    
}

startBarRenderComponent::~startBarRenderComponent() {
    
}

std::string startBarRenderComponent::getCurrentTime() {
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::stringstream buffer;
    buffer << std::put_time(&tm, "%a %b %d %H:%M:%S");
    return buffer.str();
}

void startBarRenderComponent::renderPosition(sf::Vector2f pos) {
    startBar.setPosition(pos.x, pos.y);
    blackBorder.setPosition(pos.x, pos.y-2);
    whiteBorder.setPosition(pos.x, pos.y-4);
}

void startBarRenderComponent::animate() {
    std::string d_string = getCurrentTime();
    dateText.setString(d_string);
}

void startBarRenderComponent::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(whiteBorder, states);
    target.draw(blackBorder, states);
    target.draw(startBar, states);
    target.draw(dateText, states);
    }

void startBarRenderComponent::recieveMessage(ppc::Event ev) {
    
}