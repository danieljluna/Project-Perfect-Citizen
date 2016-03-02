#include "../debug.h"
#include "AudioQueue.h"
#include <string>
sf::Sound* AudioQueue::findOpenSound()
{

	for (auto iter = soundStorage.begin(); iter != soundStorage.end(); iter++) {
		if (iter->first == false) {
			return &(iter->second);
		}
	}
	return nullptr;
}
AudioQueue::AudioQueue(int number)
{
	for (int i = 0; i < number; i++) {
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

void AudioQueue::stopSound(int sound)
{
}

void AudioQueue::popAndPlay()
{
	int front = soundQueue.front();
	sf::Sound* tempSound = findOpenSound();
	if (tempSound == nullptr) {
		return;
	}
	tempSound->setBuffer(this->bufferStorage.at(front).second);
	tempSound->play();
	soundQueue.pop();

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

