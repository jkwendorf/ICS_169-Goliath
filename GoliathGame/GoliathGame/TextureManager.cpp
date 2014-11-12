#include "TextureManager.h"
#include <sstream>
#include <iostream>


TextureManager::~TextureManager()
{
	std::cout << "Deleting textures" << std::endl;
	for(std::map<std::string, sf::Texture*>::iterator iterator = texManager.begin(); iterator != texManager.end(); iterator++) 
	{
		delete iterator->second;
	}
}


sf::Texture* TextureManager::retrieveTexture(std::string tex)
{
	std::map<std::string, sf::Texture*>::iterator it = texManager.begin(); 
	it = texManager.find(tex);

	//If you find the texture
	//	return that texture
	if(it != texManager.end())
	{
		return it->second;
	}

	//Create new texture
	sf::Texture* newTex = new sf::Texture();

	std::stringstream fileAppender;
	fileAppender << "media/art/" << tex << ".png";
	std::string name = fileAppender.str();
	// JW: We first need to set the string as empty, then clear.  It's strange like that.
	fileAppender.str("");
	fileAppender.clear();

	//If you can load a texture
	//	Store that in texManager
	//	Return the texture
	if(!newTex->loadFromFile(name))
		newTex->loadFromFile("media/art/FileNotFound.png");

	texManager.emplace(tex, newTex);

	//Return placeholder texture if all else fails
	//	need to add placeholder texture
	return newTex;
}