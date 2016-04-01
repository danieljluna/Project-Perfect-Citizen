#include "IconBuilder.h"

#include "../Game/animatorComponent.hpp"
#include "../Game/textLabelComponent.hpp"
#include "../Game/iconInputComponent.h"

ppc::IconBuilder::IconBuilder() {

	dt = nullptr;
	ih = nullptr;
	db = nullptr;
	ib = nullptr;
	buttonSheet = nullptr;

	font = nullptr;
	fontColor = sf::Color::White;

	label = "";
	isBeingPressed = "";

	sheetX = 0;
	sheetY = 0;
	width = 0;
	frames = 0;

	size = 0.f;
	animationSpeed = 0.f;

	posX = 0.f;
	posY = 0.f;

}

ppc::IconBuilder::~IconBuilder() {
}

void ppc::IconBuilder::setSpritebyIndicies(int x, int y, int r, int f) {

	sheetX = x;
	sheetY = y;
	width = r;
	frames = f;
}

void ppc::IconBuilder::setSprites(sf::Sprite &, sf::Sprite &) {
}

void ppc::IconBuilder::setSize(float s) {
	size = s;
}

void ppc::IconBuilder::setDesktop(ppc::Desktop &d) {
	dt = &d;
}

void ppc::IconBuilder::setInputHandle(ppc::InputHandler &handle) {
	ih = &handle;
}

void ppc::IconBuilder::setButtonSheet(sf::Image &bsheet) {
	this->buttonSheet = &bsheet;
}

void ppc::IconBuilder::setDatabase(ppc::Database &dbase) {
	db = &dbase;
}

void ppc::IconBuilder::setInbox(ppc::Inbox &ibox) {
	ib = &ibox;
}

void ppc::IconBuilder::setText(std::string name, sf::Font &f , 
	sf::Color col = sf::Color::White ) {

	label = name;
	font = &f;
	fontColor = col;
}

void ppc::IconBuilder::setAnimSpeed(float spd) {
	animationSpeed = spd;
}

void ppc::IconBuilder::setPosition(float x, float y) {
	posX = x;
	posY = y;
}

void ppc::IconBuilder::setPosition(sf::Vector2f pos) {

	posX = pos.x;
	posY = pos.y;
}

void ppc::IconBuilder::create(Entity &e) {
	textLabelComponent* textLabel = new textLabelComponent(*font, fontColor, posX, posY + size * 128, 20, label);

	buttonRenderComponent* IconRender = new buttonRenderComponent(*dt->getIconSheet(), sheetX, sheetY, width, frames);
	IconRender->setImageScale(size, size);
	IconRender->renderPosition({ posX, posY });
	animatorComponent* animator = new animatorComponent(*IconRender, animationSpeed);
	mousePressButton* mpbFolder = new mousePressButton(*ih, IconRender->getSprite()->getGlobalBounds(), "folderIcon");
	iconInputComponent* iconInputComp = new iconInputComponent(*dt, db, *ib, *buttonSheet, *dt->getIconSheet());

	e.addComponent(IconRender);
	e.addComponent(textLabel);
	e.addComponent(iconInputComp);
	e.addComponent(animator);
	e.addComponent(mpbFolder);

}
