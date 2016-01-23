#include "observer.h"
#include <iostream>
//this would be virtual of course, but this is just an example

void Observer::eventHandler(ppc::Event event)
{
	int test = 0;
	int testTwo = 0;
	int testThree = 0;
	switch (event.type) {
	case ppc::Event::EventTypes::RenderEventType:
		test += 10;
		break;

	case ppc::Event::EventTypes::InputEventType:
		test += 5000;
		//call some crazy function related to the child class
		break;
	case ppc::Event::EventTypes::UpdateEventType:
		test += 69;
		test += 80085;
		break;
	default:

		return;
	}
	cout << "the value of test is " << test << endl;
	cout << "the value of testTwo is " << testTwo << endl;
	cout << "the value of testThree is " << testThree << endl;
	return;
}


