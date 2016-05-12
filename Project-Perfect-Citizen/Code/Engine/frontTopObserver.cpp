#include "frontTopObserver.h"
#include "desktop.h"

	propagate = prop;
	dt = &d;
}

void ppc::frontTopObsvr::setDesktop(Desktop &d) {
	dt = &d;
}

bool ppc::frontTopObsvr::eventHandler(Event ev) {
	if(propagate) dt->registerInputFocused(ev);

	return true;
}
