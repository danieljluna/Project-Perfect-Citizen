#pragma once
//Another possible solution

union Event {
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
