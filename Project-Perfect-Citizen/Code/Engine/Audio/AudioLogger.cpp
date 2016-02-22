#include "AudioLogger.h"

void ppc::AudioLogger::log(const std::string message)
{
	std::cout << message << std::endl;
}

void ppc::AudioLogger::playSound(int sound)
{
	switch (sound)
	{
	case ppc::Sounds::gunshot:
		this->log("Playing sound: gunshots");
	default:
		break;
	}
	this->comfyAudio_.playSound(sound);
}

void ppc::AudioLogger::stopSound(int sound)
{
}
