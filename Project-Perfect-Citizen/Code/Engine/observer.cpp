#include "observer.h"
//this would be virtual of course, but this is just an example
void Observer::exampleEventHandler(Event event)
{
	int test = 0;
	int testTwo = 0;
	int testThree = 0;
	switch (event.type) {
	case Event::RENDER:
		
		test += 10;
		break;

	case Event::INPUT:
		test += 5000;
		//call some crazy function related to the child class
		break;
	case Event::UPDATE:
		test += 69;
		test += 80085;
		break;
	default:
		return;
	}
	return;
}
