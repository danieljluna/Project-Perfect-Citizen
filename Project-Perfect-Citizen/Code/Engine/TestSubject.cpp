#include "TestSubject.h"
void TestSubject::testEventSituation()
{
	int arbitraryInt = 5;
	double arbitraryDouble = 3.14;

	ppc::Event exampleRenderEvent;
	exampleRenderEvent.type = ppc::Event::EventTypes::RenderEventType;
	exampleRenderEvent.renderStruct.testRenderEventInt = arbitraryInt;
	exampleRenderEvent.renderStruct.testRenderEventDouble = arbitraryDouble;
	this->sendEvent(exampleRenderEvent);
}
