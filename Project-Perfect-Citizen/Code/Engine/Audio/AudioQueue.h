#pragma once
#include "Audio.h"
#include <queue>

//Prototypes///////////////
namespace sf {
    class SoundBuffer;
    class Sound;
};
///////////////////////////

namespace ppc {

class AudioQueue : public Audio {
private:
	typedef std::vector < std::pair<bool, sf::SoundBuffer>> bVec;
	typedef std::vector < std::pair<std::string, sf::SoundBuffer>> ssVector;
	typedef std::vector < std::pair<bool, sf::Sound>> bsVector;
	ssVector bufferStorage;
	bsVector soundStorage;
	bVec bufferVector;
	int maxSounds = 5;
	int soundCount = 0;
	std::queue<int> soundQueue;
	std::string filepath = "Code/Engine/Audio/Sounds/";
protected:
	sf::Sound* findOpenSound();
public:
	AudioQueue(int number);
	virtual void playSound(int sound);
	virtual void stopSound(int sound);
	void popAndPlay();
	int addSound(std::string name, std::string filename);
};


};  //End namespace ppc

