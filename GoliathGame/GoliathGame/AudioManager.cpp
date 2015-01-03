#include "AudioManager.h"

AudioManager::~AudioManager()
{
	for(std::map<std::string, sf::SoundBuffer*>::iterator iterator = soundBufferManager.begin(); iterator != soundBufferManager.end(); iterator++) 
	{
		delete iterator->second;
	}
}

sf::SoundBuffer* AudioManager::retrieveSound(std::string& sound)
{
	std::map<std::string, sf::SoundBuffer*>::iterator it = soundBufferManager.begin(); 
	it = soundBufferManager.find(sound);

	//If you find the Audio
	//	return that Audio
	if(it != soundBufferManager.end())
	{
		return it->second;
	}

	//Create new Audio
	sf::SoundBuffer* newSound = new sf::SoundBuffer();

	//std::stringstream fileAppender;
	//fileAppender << "media/sound/" << sound << ".wav";
	std::string name = "media/sound/" + sound + ".wav";
	// JW: We first need to set the string as empty, then clear.  It's strange like that.
	//fileAppender.str("");
	//fileAppender.clear();
	if(!newSound->loadFromFile(name))
		newSound->loadFromFile("media/sound/Default.wav");

	soundBufferManager.emplace(sound, newSound);

	//Return placeholder Audio if all else fails
	//	need to add placeholder Audio
	return newSound;
}
