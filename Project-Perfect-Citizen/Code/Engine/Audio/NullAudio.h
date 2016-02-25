#pragma once
#include "Audio.h"
namespace ppc {
	//////////////////////////////////////////////////
	///@brief NullAudio class. All functions do nothing
	///@details. This is so you can plug NullAudio
	///into the AudioLogger in order to stop all sound
	///from playing. Also used to ensure that 
	///AudioLogger::getAudio() will return a non null
	///value;
	//////////////////////////////////////////////////
	class NullAudio : public Audio {
		virtual void playSound(int sound) { return; }
		virtual void stopSound(int sound) { return; }
	};
};