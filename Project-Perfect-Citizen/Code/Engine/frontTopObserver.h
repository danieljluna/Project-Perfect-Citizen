#pragma once

#include "observer.h"

namespace ppc {
	class Desktop;

	class frontTopObsvr : public BaseObserver {
	
	private:

		Desktop* dt;

	public:

		frontTopObsvr(Desktop&);

		void setDesktop(Desktop&);

		bool eventHandler(Event ev) override;
	};

};
