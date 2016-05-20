#pragma once


#include "../Engine/observer.h"

namespace ppc {
	class Window;
	class ReportEndObsvr : public ppc::BaseObserver {

	private:

		Window* w_;

	public:

		ReportEndObsvr();
		virtual ~ReportEndObsvr();

		ReportEndObsvr(Window&);

		void setEntity(Window&);

		bool eventHandler(Event ev) override;

	};

};