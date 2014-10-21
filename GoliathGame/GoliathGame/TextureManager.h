#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <map>

class TextureManager
{
public:
	std::map<std::string, sf::Texture*> texManager;

	TextureManager();
	~TextureManager();

	sf::Texture* retrieveTexture(std::string& tex);
};