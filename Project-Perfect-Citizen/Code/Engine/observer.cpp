#include "observer.h"
#include <iostream>

// for now, we want every child of observer to at least have the
// base behavior of... doing nothing with an event. You can always
// define it in the base class if you need something specifically 
// done.
void Observer::eventHandler(sf::Event event)
{
	cout << "The event type is " << event.type << endl;

	/*
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
	*/
}


