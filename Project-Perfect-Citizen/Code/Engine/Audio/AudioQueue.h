#pragma once
#include "Audio.h"
#include "SFML/Audio.hpp"
#include <iostream>
#include <utility>
#include <queue>
class AudioQueue : public ppc::Audio {
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