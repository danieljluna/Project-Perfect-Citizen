#include "ReportEndObsvr.h"
#include "../Engine/Window.h"
#include "TextDisplayRenderComponent.h"
#include "../Engine/World.h"
#include "../Engine/debug.h"

ppc::ReportEndObsvr::ReportEndObsvr() {
	w_ = nullptr;
}

ppc::ReportEndObsvr::~ReportEndObsvr() {
}

ppc::ReportEndObsvr::ReportEndObsvr(Window &w) {
	w_ = &w;
}

void ppc::ReportEndObsvr::setEntity(Window &w) {
	w_ = &w;
}

bool ppc::ReportEndObsvr::eventHandler(Event ev) {
	if (ev.type == Event::AnimationType) {
		TextDisplayRenderComponent* t = new TextDisplayRenderComponent(
			World::getFont(World::FontList::Consola), 
			sf::Color::Red,
			400, 
			500,
			20,
			"Click to Continue");
		
		w_->addRenderComponent(t);
	}
	return true;
}


