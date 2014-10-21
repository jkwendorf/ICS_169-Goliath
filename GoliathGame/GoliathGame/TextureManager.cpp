#include "TextureManager.h"

TextureManager::TextureManager()
{
	
}

//need to deallocate
TextureManager::~TextureManager()
{

}

sf::Texture* TextureManager::retrieveTexture(std::string& tex)
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
	sf::Texture* newTex;

	//If you can load a texture
	//	Store that in texManager
	//	Return the texture
	if(newTex->loadFromFile(tex))
	{
		texManager.emplace(tex, newTex);
		return newTex;
	}

	//Return placeholder texture if all else fails
	//	need to add placeholder texture
	return newTex;
}