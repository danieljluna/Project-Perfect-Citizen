#pragma once
#include "Audio.h"
namespace ppc {
	class NullAudio : public Audio {
		virtual void playSound(int sound) { return; }
		virtual void stopSound(int sound) { return; }
	};
};