#include "../debug.h"
#include "AudioQueue.h"
#include "SFML/Audio.hpp"
#include <string>
#include <iostream>
#include <utility>
#include <queue>


using namespace ppc;

std::pair<int, sf::Sound*> AudioQueue::findOpenSound()
{
	int i = 0;
	std::pair<int, sf::Sound*> returnPair;
	for (auto iter = soundStorage.begin(); iter != soundStorage.end(); iter++) {
		if (iter->first == false) {
			iter->first = true;
			returnPair.first = i;
			returnPair.second = &(iter->second);
			return returnPair;
		}
		i++;
	}
	returnPair.first = -1;
	returnPair.second = nullptr;
	return returnPair;
}
void ppc::AudioQueue::releaseSound(int element)
{
	soundStorage.at(element).first = false;
}
AudioQueue::AudioQueue(int number)
{
	int tempNumber = number;
	if (tempNumber > maxSounds) {
		tempNumber = maxSounds;
		std::cout << "max sounds exceeded defaulting to maximum number" << std::endl;
	}
	for (int i = 0; i < tempNumber; i++) {
		std::pair<bool, sf::Sound> newSoundPair;
		sf::Sound newSound;
		newSoundPair.first = false;
		newSoundPair.second = newSound;
		this->soundStorage.push_back(newSoundPair);
	}
}
void AudioQueue::playSound(int sound)
{
	soundQueue.push(sound);
}
void AudioQueue::readySound(int sound) {
	soundQueue.push(sound);
}

void AudioQueue::stopSound(int sound)
{

}

void AudioQueue::stopAllSounds() {
	for (auto iter = soundStorage.begin(); iter != soundStorage.end(); iter++) {
		iter->second.stop();
	}
}

void AudioQueue::popAndPlay()
{
	int front = soundQueue.front();
	std::pair<int, sf::Sound*> findPair;
	findPair = findOpenSound();
	if (findPair.second == nullptr) {
		return;
	}
	findPair.second->setBuffer(bufferStorage.at(front).second);
	findPair.second->play();
	soundQueue.pop();
	releaseSound(findPair.first);

}

int AudioQueue::addSound(std::string name, std::string filename)
{
	if (soundCount >= maxSounds) {
		std::cerr << "too many sounds. Talk to Andy about increasing the limit" << std::endl;
		return -1;
	}

	sf::SoundBuffer newBuffer;
	std::pair<std::string, sf::SoundBuffer> newPair;

	newBuffer.loadFromFile(filepath + filename);
	newPair.first = name;
	newPair.second = newBuffer;
	bufferStorage.push_back(newPair);
	int tempInt = this->soundCount;
	soundCount++;
	return tempInt;
}

bool ppc::AudioQueue::addBgm(std::string filename)
{
	if (!bgm.openFromFile(this->filepath + filename))
		return false; // error
	 //SoundTrack_Extraction.ogg
	return true;
}

void ppc::AudioQueue::playBgm()
{
	bgm.play();
}


