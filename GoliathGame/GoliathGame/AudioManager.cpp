#include "AudioManager.h"
/*
AudioManager::~AudioManager()
{
	for(std::map<std::string, sf::SoundBuffer*>::iterator iterator = soundBufferManager.begin(); iterator != soundBufferManager.end(); iterator++) 
	{
		delete iterator->second;
	}
}

void AudioManager::SetupMap(const std::map<std::string, sf::SoundBuffer*>& s)
{
	soundBufferManager = s;
	for(int i = 0; i < soundBufferManager.size(); i++)
	{
		
	}
}

sf::Sound* AudioManager::retrieveSound(std::string tex)
{
	std::map<std::string, sf::Sound*>::iterator it = soundManager.begin(); 
	it = texManager.find(tex);

	//If you find the Audio
	//	return that Audio
	if(it != texManager.end())
	{
		return it->second;
	}

	//Create new Audio
	sf::Sound* newSound = new sf::Sound();

	std::stringstream fileAppender;
	fileAppender << "media/art/" << tex << ".png";
	std::string name = fileAppender.str();
	// JW: We first need to set the string as empty, then clear.  It's strange like that.
	fileAppender.str("");
	fileAppender.clear();

	//If you can load a Audio
	//	Store that in texManager
	//	Return the Audio
	if(!newSound->loadFromFile(name))
		newSound->loadFromFile("media/art/FileNotFound.png");

	texManager.emplace(tex, newTex);

	//Return placeholder Audio if all else fails
	//	need to add placeholder Audio
	return newTex;
}
*/