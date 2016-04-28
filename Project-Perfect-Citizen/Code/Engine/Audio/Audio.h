#pragma once
#include <SFML/Audio.hpp>
namespace ppc {

	//////////////////////////////////////////////////
	///@brief Abstract base class for the Audio Engine
	///@details This class is an abstract class. Its 
	///in charge of creating an interface that will be
	///used in all children. It should never be instantiated.
	///Children of audio would theoretically be created
	///for each "theme" of sounds, i.e. Desktop sounds
	///pipeline sounds etc. 
	/////////////////////////////////////////////////
	class Audio {
	public:
		virtual ~Audio() {};
		//////////////////////////////////////////////////
		///@brief plays the chosen sound
		///param sound: The chosen sound that will be played
		///Sound is of type ppc::Sounds which is of type
		///enum
		/////////////////////////////////////////////////
		virtual void playSound(int sound) = 0;
		//////////////////////////////////////////////////
		///@brief stops the chosen sound
		///param sound: The chosen sound that will be stopped
		///Sound is of type ppc::Sounds which is of type
		///enum
		/////////////////////////////////////////////////
		virtual void stopSound(int sound) = 0;
	};
};