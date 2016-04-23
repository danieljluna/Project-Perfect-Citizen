#include "frontTopObserver.h"
#include "desktop.h"

ppc::frontTopObsvr::frontTopObsvr(Desktop &d) {
	dt = &d;
}

void ppc::frontTopObsvr::setDesktop(Desktop &d) {
	dt = &d;
}

bool ppc::frontTopObsvr::eventHandler(Event ev) {

	dt->registerInputFocused(ev);

	return false;
}
