#include "Screen.h"
// include more tiles

Screen::Screen(std::string s)
	: pathToText(s)
{
	LoadTileMap();
}

Screen::~Screen()
{

}

int Screen::getScreenWidth()
{
	return width * TILE_WIDTH;
}

int Screen::getScreenHeight()
{
	return height * TILE_HEIGHT;
}

void Screen::update(float deltaTime)
{

}

void Screen::draw(sf::RenderWindow& w)
{
	for(int i = 0; i < numOfTiles; i++)
	{
		tiles[i].draw(w);
	}
}


void Screen::LoadTileMap()
{
	
	std::ifstream ifs;
	ifs.open("media/levels/" + pathToText + ".txt");
	std::string str;

	if(!ifs.good())
	{
		std::cout << "Level text file did not load!" << std::endl; 
		return;
	}
		
	std::getline(ifs, str);
	std::vector <std::string> token;
	Tokenize(str, token, ", ");

	//Sets up the txtWidth, txtHeight, and tileSheet with the 
	// values in the level.txt
	//std::cout << "Token[2] " << token[2] << std::endl; 
	width = atoi(token[0].c_str());
	height = atoi(token[1].c_str());
	numOfTiles = atoi(token[2].c_str());
	sf::Texture* texture = TextureManager::GetInstance().retrieveTexture(token[3]);
	//std::cout << "Token[3] " << token[3] << std::endl; 
	
	tiles = new GroundTile[numOfTiles];
	int current = 0;
	//*TextureManager::GetInstance().retrieveTexture(token[6], "Tiles");	
	//AddTexture("Images/Blank.png", "Blank");

	token.clear();
	int ratioX = SCREEN_WIDTH / width;
	int ratioY = SCREEN_HEIGHT / height;
	//std::cout << "RatioX: " << ratioX << " RatioY: " << ratioY << std::endl; 

	while(!ifs.eof()) 
	{
		std::getline(ifs, str);
		Tokenize(str, token, "||");
		
		for(int i = 0; i < token.size(); i++)
		{
			std::vector <std::string> tileToken;
			Tokenize(token[i], tileToken, ",");
			//std::cout << "Tiletype: " << atoi(tileToken[0].c_str()) << ". X: " << atoi(tileToken[2].c_str()) << ". Y: " << atoi(tileToken[1].c_str()) << std::endl; 
			
			tiles[current++] = GroundTile(atoi(tileToken[0].c_str()), sf::Vector2i(atoi(tileToken[2].c_str()) * ratioX, atoi(tileToken[1].c_str()) * ratioY), sf::Vector2i(ratioX, ratioY), texture);
		}
		token.clear();
	}
	ifs.close();
}

void Screen::Tokenize(const std::string& str,
                      std::vector<std::string>& tokens,
                      const std::string& delimiters)
{
    // Skip delimiters at beginning.
    std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    // Find first "non-delimiter".
    std::string::size_type pos = str.find_first_of(delimiters, lastPos);

    while (std::string::npos != pos || std::string::npos != lastPos)
    {
        // Found a token, add it to the vector.
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of(delimiters, pos);
        // Find next "non-delimiter"
        pos = str.find_first_of(delimiters, lastPos);
    }
}