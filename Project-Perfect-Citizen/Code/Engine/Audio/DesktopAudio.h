#pragma once
#include "Audio.h"
#include <iostream>
#include "SFML/Audio.hpp"
namespace ppc {
	//////////////////////////////////////////////////
	///@brief Pretty much an example child class of
	///ppc::Audio. However, since we do have desktops,
	///I envisioned that we could reuse this class 
	///down the line
	//////////////////////////////////////////////////
	class DesktopAudio : public Audio {
	private:
		//////////////////////////////////////////////////
		///@brief sound object that is played by
		///playSound();
		///@details in SFML sf::sound acts much the same as 
		///sf::Sprite. Therefore I named it this way to 
		///hopefully perpetuate the understanding of 
		///how the audio engine works
		//////////////////////////////////////////////////
		sf::Sound* soundSprite;
		//////////////////////////////////////////////////
		///@brief soundbuffer for a test sound
		///for now, all sounds are frontloaded into memory
		///and therefore each need a seperate soundBuffer
		///@details think of soundbuffer as the equivalent
		///to sf::texture in a texture/sprite pair. A sound
		///needs to be assigned a "texture" (soundbuffer) to
		///be played
		//////////////////////////////////////////////////
		sf::SoundBuffer* gunshotSound;
		//////////////////////////////////////////////////
		///@brief string representation of where sounds are
		///stored in the IRL file structure of our program
		///@details setting it up this way allows us to change
		///less lines of code should the location of the sound
		///files change
		//////////////////////////////////////////////////
		std::string soundDirectory = "Code/Engine/Audio/Sounds/";
	public:
		//////////////////////////////////////////////////
		///@brief Desktop Constructor
		//////////////////////////////////////////////////
		DesktopAudio();
		//////////////////////////////////////////////////
		///@brief plays a sound. See ppc::Audio::playSound()
		///for details
		//////////////////////////////////////////////////
		virtual void playSound(int sound);
		//////////////////////////////////////////////////
		///@brief stops a sound. See ppc::Audio::stopSound()
		///for details
		//////////////////////////////////////////////////
		virtual void stopSound(int sound);
	};
};