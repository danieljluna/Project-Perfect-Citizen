#include "ReportEndObsvr.h"
#include "../Engine/Window.h"
#include "TextDisplayRenderComponent.h"
#include "../Engine/World.h"
#include "../Engine/debug.h"

ppc::ReportEndObsvr::ReportEndObsvr() {
	w_ = nullptr;
	x_ = 400.f;
	y_ = 500.f;
}

ppc::ReportEndObsvr::~ReportEndObsvr() {
}

ppc::ReportEndObsvr::ReportEndObsvr(Window &w) {
	w_ = &w;
}

void ppc::ReportEndObsvr::setEntity(Window &w) {
	w_ = &w;
}

void ppc::ReportEndObsvr::setPos(float x, float y) {
	x_ = x;
	y_ = y;
}

bool ppc::ReportEndObsvr::eventHandler(Event ev) {
	if (ev.type == Event::AnimationType) {
		TextDisplayRenderComponent* t = new TextDisplayRenderComponent(
			World::getFont(World::FontList::Consola), 
			sf::Color::Red, x_, y_, 20, "Click to Continue");
		
		w_->addRenderComponent(t);
	}
	return true;
}


