#include "AudioLocator.h"
#include "../debug.h"
ppc::Audio* ppc::AudioLocator::service_;
ppc::NullAudio ppc::AudioLocator::nullService_;

ppc::Audio * ppc::AudioLocator::getAudio()
{
	return service_;
}

void ppc::AudioLocator::assign(Audio* service)
{
	if (service == nullptr) {
		service_ = &nullService_;
	}
	else {
		service_ = service;
	}
}

void ppc::AudioLocator::initialize()
{
	service_ = &nullService_;
}
