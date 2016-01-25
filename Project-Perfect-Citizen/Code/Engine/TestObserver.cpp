#include "TestObserver.h"

void TestObserver::eventHandler(ppc::Event event)
{
	if (event.type != ppc::Event::EventTypes::RenderEventType) {
		return;
	}

	cout << "The double in this event is " << 
		event.renderStruct.testRenderEventDouble << endl;

	cout << "The integer in this event is " <<
		event.renderStruct.testRenderEventInt << endl;
}
