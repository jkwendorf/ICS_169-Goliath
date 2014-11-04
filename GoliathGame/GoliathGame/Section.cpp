#include "Section.h"
// include more tiles

Section::Section(std::string s, sf::Vector2i sectionOffSet)
	: pathToText(s), sOffSet(sectionOffSet)
{
	LoadTileMap();
	Global::GetInstance().ParseLevelSizes();
}

Section::~Section()
{

}

//Screen height is how many cols of tiles are in the screen * the width of the tiles
int Section::getScreenWidth()
{
	return width /** TILE_WIDTH*/;
}

//Screen height is how many rows of tiles are in the screen * the height of the tiles
int Section::getScreenHeight()
{
	return height /** TILE_HEIGHT*/;
}

bool Section::inWindow(int offSetX, int offSetY)
{
	/*
	if(sOffSet- screenOffSet <= screenWidth && sectionOffSet + width - screenOffSet >= 0)
	{
		return true;
	}
	return false;
	*/
	return true;
}

void Section::update(float deltaTime)
{

}

void Section::draw(sf::RenderWindow& w)
{
	for(int i = 0; i < numOfTiles; i++)
	{
		tiles[i].draw(w);
	}
}

//Loading is the text file from the given file path
//Parses the first line of the file to get information about the rest of the file.
//Continues through the file until it hits the end of the file and creates tiles based off information parsed in
void Section::LoadTileMap()
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
	float ratioX = (float)GAME_TILE_WIDTH / 100;
	float ratioY = SCREEN_HEIGHT / width;
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
			
			tiles[current++] = GroundTile(atoi(tileToken[0].c_str()), sf::Vector2i(atoi(tileToken[2].c_str()) * GAME_TILE_WIDTH, atoi(tileToken[1].c_str()) * ((SCREEN_HEIGHT / width))), sOffSet, sf::Vector2f(ratioX, ratioY), texture);
		}
		token.clear();
	}
	ifs.close();
}

void Section::Tokenize(const std::string& str,
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