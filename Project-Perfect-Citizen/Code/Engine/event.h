#pragma once
//Programmed by Andy

namespace ppc {
	//This is the event struct. You can add events here
	//if you need them. Nothing here is final except
	//the template. 
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