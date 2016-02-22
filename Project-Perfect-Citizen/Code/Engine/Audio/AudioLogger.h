#pragma once
#include "Audio.h"
#include <iostream>
#include <string>
namespace ppc {
	//////////////////////////////////////////////////
	///@brief AudioLogger class, child of ppc::Audio
	///the purpose of this class is to server as a wrapper
	///to a child of Audio. 
	///@details The class embedded in this AudioLogger
	/// behaves normally. AudioLogger logs which sound was
	///played by the logged class
	//////////////////////////////////////////////////
	class AudioLogger : public ppc::Audio {
	private:
		//////////////////////////////////////////////////
		///@brief private log function. For now, it prints
		///when a sound was played. Soon it will print what
		///specific sound is played
		///@param message: string to be printed to cout
		//////////////////////////////////////////////////
		void log(const std::string message);

		//////////////////////////////////////////////////
		///@brief Child of ppc::Audio that is currently
		///being held by AudioLogger
		//////////////////////////////////////////////////
		ppc::Audio& comfyAudio_;
	public:
		//////////////////////////////////////////////////
		///@brief AudoLogger constructor
		///@param coldAudio: my stupid name for the child
		/// of ppc::Audio to be wrapped by this AudioLogger
		///the wrapped child is logged. 
		//////////////////////////////////////////////////
		AudioLogger(ppc::Audio& coldAudio) 
			: comfyAudio_(coldAudio) {}
		//////////////////////////////////////////////////
		///@brief plays the sound and prints it to cout
		///for more information, see ppc::Audio::playSound()
		//////////////////////////////////////////////////
		virtual void playSound(int sound);
		//////////////////////////////////////////////////
		///@brief stops the sound and prints it to cout
		///for more information, see ppc::Audio::stopSound()
		//////////////////////////////////////////////////
		virtual void stopSound(int sound);
	};
}