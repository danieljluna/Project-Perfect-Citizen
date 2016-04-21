#include "NotificationObserver.h"
#include "../Game/notifcationRenderComponent.h"
#include "event.h"

ppc::NotificationObserver::NotificationObserver(const ppc::notificationRenderComponent & nrComp)
{
	nrc = &nrComp;
}

bool ppc::NotificationObserver::eventHandler(Event ev)
{
	if (ev.type == ppc::Event::EventTypes::NotificationType) {
		value = ev.notification.count;
		nrc->updateText(value);
	}
	return true;
}

unsigned int ppc::NotificationObserver::getNotificationValue()
{
	return value;
}
