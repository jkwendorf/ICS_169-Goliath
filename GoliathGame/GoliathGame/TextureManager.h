#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <map>

class TextureManager
{
public:
	static TextureManager& GetInstance()
	{
		static TextureManager instance;
		return instance;
	}

	sf::Texture* retrieveTexture(std::string tex);

private:
	TextureManager() {};
	~TextureManager();

	TextureManager(const TextureManager&);
	TextureManager& operator =(const TextureManager&);

	std::map<std::string, sf::Texture*> texManager;
};