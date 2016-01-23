#pragma once
//Another possible solution

/*union Event {
	enum eventType { RENDER, INPUT, UPDATE };
	eventType type;
	struct renderStruct
	{
		int testRenderInt;
	};
	struct inputStruct {
		int testInputInt;
	};
	struct updateStruct {
		int testUpdateStruct;
	};
};
*/

/*struct dannyStruct {
	enum dannyType{ HAPPY, SAD, ANGRY_AT_ANDY};
	dannyType dType;
	union dannyData {
		struct hello {
			int testHappy;
		};
		struct {
			double testHappyDouble;
			char testHappyChar;
		};
	};
};

struct secondTestStruct {
	int stStructInt;
	char firstLetter;
	double secondDouble;
};

struct secondTestStructA {
	int stStructIntA;
	char firstLetterA;
	
};

struct secondTestStructB {
	int stStructIntB;
	double secondDoubleB;
};

struct secondTestStructC {
	char firstLetterC;
	double secondDoubleC;
};


union monkey {
	secondTestStruct blah;
	secondTestStructA a;
	secondTestStructB b;
	secondTestStructC c;
};


//{
///	enum Blash {};
	//Blah type;
	//monkey;
//}
*/
namespace ppc {
	struct Event
	{
		struct RenderStruct {
			int testRenderEventInt;
			double testRenderEventDouble;
		};

		struct InputStruct {
			char testInputEventChar;
			float testInputEventFloat;
		};

		struct UpdateStruct {
			int testUpdateInt;
			int testUpdateIntTwo;
		};

		enum EventTypes
		{
			RenderEventType,
			InputEventType,
			UpdateEventType,

			Count
		};

		EventTypes type;

		union {
			RenderStruct renderStruct;
			InputStruct inputStruct;
			UpdateStruct updateStruct;
		};
	};
} //end of ppc namespace