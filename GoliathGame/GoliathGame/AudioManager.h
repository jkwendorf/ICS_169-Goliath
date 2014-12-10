#pragma once

#include <SFML\Audio.hpp>
#include <map>

class AudioManager
{
public:
	static AudioManager& GetInstance()
	{
		static AudioManager instance;
		return instance;
	}

	void SetupMap(const std::map<std::string, sf::SoundBuffer*>& s);
	sf::SoundBuffer* retrieveSound(std::string& sound);

private:
	AudioManager() {};
	~AudioManager();

	AudioManager(const AudioManager&);
	AudioManager& operator =(const AudioManager&);

	std::map<std::string, sf::SoundBuffer*> soundBufferManager;
};