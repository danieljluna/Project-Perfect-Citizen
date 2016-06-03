#pragma once


#include "../Engine/observer.h"

namespace ppc {
	class Window;
	class ReportEndObsvr : public ppc::BaseObserver {

	private:

		Window* w_;
		float x_;
		float y_;
	public:

		ReportEndObsvr();
		virtual ~ReportEndObsvr();

		ReportEndObsvr(Window&);

		void setEntity(Window&);
		
		void setPos(float, float);

		bool eventHandler(Event ev) override;

	};

};