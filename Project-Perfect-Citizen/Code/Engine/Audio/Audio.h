#pragma once
#include "Sounds.h"
namespace ppc {
	class Audio {
	public:
		virtual ~Audio() {};
		virtual void playSound(int sound) = 0;
		virtual void stopSound(int sound) = 0;
	};
};