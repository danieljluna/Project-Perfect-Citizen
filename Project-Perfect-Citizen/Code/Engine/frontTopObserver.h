#pragma once

#include "observer.h"

namespace ppc {
	class Desktop;

	class frontTopObsvr : public BaseObserver {
	
	private:

		Desktop* dt;
		bool propagate = true;

	public:

		frontTopObsvr(Desktop&, bool prop = true);

		void setDesktop(Desktop&);

		bool eventHandler(Event ev) override;
	};

};
