#pragma once

#include "inputComponent.h"

namespace ppc{
	///////////////////////////////////////////////////////////////////
	///@brief Faux-Decorator class that logs Input Cmpnts.
	///@details Normally, Decorators would handle the deletion of the
	/// object they are decoration, but this is ins't a real decorator
	/// deletion of input components rely on the user instead of the
	/// decorator.
	///@author Nader Sleem
	///////////////////////////////////////////////////////////////////
	class inputCmpntLogger: public InputComponent {

	private:

		InputComponent* iCmpntHandle_;
		std::ostream& out_;

	public:

		inputCmpntLogger() = delete;
		inputCmpntLogger(InputComponent& inputPtr, std::ostream& out);
		~inputCmpntLogger();

		Entity* getEntity();
		void setEntity(Entity*);
		void recieveMessage(msgType message);
		bool registerInput(Event ev);
	};
};