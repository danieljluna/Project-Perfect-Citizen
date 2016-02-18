#pragma once
#include "Audio.h"
namespace ppc {
	class DesktopAudio : public Audio {
	public:
		virtual void playSound(int sound);
		virtual void stopSound(int sound);
	};
};