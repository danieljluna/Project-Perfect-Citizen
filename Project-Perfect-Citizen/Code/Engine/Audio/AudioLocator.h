#pragma once
#include "Audio.h"
#include "NullAudio.h"
namespace ppc {
	
	class AudioLocator {
	private:
		static ppc::Audio* service_;
		static ppc::NullAudio nullService_;
	public:
		static ppc::Audio* getAudio();
		static void assign(ppc::Audio* service);
		static void initialize();
	};
};