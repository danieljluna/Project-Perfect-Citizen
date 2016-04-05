#pragma once
#include "Audio.h"
#include <queue>
//Prototypes///////////////
//namespace sf {
    //class SoundBuffer;
  //  class Sound;
//};
///////////////////////////

namespace ppc {

class AudioQueue : public Audio {
private:
	//typedef std::vector < std::pair<bool, sf::SoundBuffer>> bVec;
	typedef std::vector < std::pair<std::string, sf::SoundBuffer>> ssVector;
	typedef std::vector < std::pair<bool, sf::Sound>> bsVector;
	ssVector bufferStorage;
	bsVector soundStorage;
	//bVec bufferVector;
	int maxSounds = 5;
	int soundCount = 0;
	std::queue<int> soundQueue;
	std::string filepath = "Code/Engine/Audio/Sounds/";
	sf::Music bgm;
protected:
	std::pair<int, sf::Sound*> findOpenSound();
	void releaseSound(int element);
public:
	AudioQueue(int number);
	virtual void playSound(int sound);
	void readySound(int sound);
	virtual void stopSound(int sound);
	void popAndPlay();
	int addSound(std::string name, std::string filename);
	bool addBgm(std::string filename);
	void playBgm();
};


};  //End namespace ppc

