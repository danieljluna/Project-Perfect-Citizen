#pragma once
#include "Audio.h"
#include <iostream>
namespace ppc {
	class DesktopAudio : public Audio {
	public:
		DesktopAudio();
		virtual void playSound(int sound);
		virtual void stopSound(int sound);
	};
};