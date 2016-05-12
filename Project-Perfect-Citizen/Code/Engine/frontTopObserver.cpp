#include "frontTopObserver.h"
#include "desktop.h"

ppc::frontTopObsvr::frontTopObsvr(Desktop &d, bool prop) {
	dt = &d;
	propagate = prop;
}

void ppc::frontTopObsvr::setDesktop(Desktop &d) {
	dt = &d;
}

bool ppc::frontTopObsvr::eventHandler(Event ev) {
	if(propagate) dt->registerInputFocused(ev);

	return true;
}
