#include "DesktopAudio.h"
#include "../debug.h"
ppc::DesktopAudio::DesktopAudio()
{
	soundSprite = new sf::Sound;
	gunshotSound = new sf::SoundBuffer;
	gunshotSound->loadFromFile(soundDirectory + "gunshots.wav");
}

void ppc::DesktopAudio::playSound(int sound)
{
	switch (sound)
	{
	case ppc::Sounds::gunshot:
		soundSprite->setBuffer(*gunshotSound);
		break;
	default:
		break;
	}
	soundSprite->play();
}

void ppc::DesktopAudio::stopSound(int sound)
{
	soundSprite->stop();
	return;
}
