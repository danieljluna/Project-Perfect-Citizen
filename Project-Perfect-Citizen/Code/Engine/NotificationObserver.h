#pragma once
#include "observer.h"


namespace ppc {
	class notificationRenderComponent;

	class NotificationObserver : public ppc::BaseObserver {
	private:
		unsigned int value;
		const notificationRenderComponent* nrc;
		
	public:
		NotificationObserver() = delete;
		NotificationObserver(const ppc::notificationRenderComponent& nrComp);
		virtual bool eventHandler(Event ev);
		unsigned int getNotificationValue();
	};
}