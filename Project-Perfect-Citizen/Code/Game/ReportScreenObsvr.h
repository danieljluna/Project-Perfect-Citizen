#pragma once


#include "../Engine/observer.h"

namespace ppc {
	class Desktop;

	class ReportScreenObsvr: public ppc::BaseObserver {
	private:

		Desktop* dt;

	public:

		ReportScreenObsvr();
		~ReportScreenObsvr();

		ReportScreenObsvr(Desktop&);

		void setDesktop(Desktop&);

		bool eventHandler(Event ev) override;
	};

};
