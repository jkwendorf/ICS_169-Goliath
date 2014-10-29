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

int Screen::getMapWidth()
{
	return 1;
}

int Screen::getMapHeight()
{
	return 1;
}

void Screen::update(float deltaTime)
{

}

void Screen::draw(sf::RenderWindow* w)
{
	for(int i = 0; i < 20; i++)
	{

	}
}


void Screen::LoadTileMap()
{
	int currentRow = 0;
	level.open("media/art/" + pathToText);
	std::string str;

	if(!level.good())
		std::cout << "Level text file did not load!" << std::endl; 
		return;
		

	getline(level, str);
	std::vector <std::string> token;
	Tokenize(str, token, ", ");

	//Sets up the txtWidth, txtHeight, and tileSheet with the 
	// values in the level.txt
	std::cout << "Token[2]" << token[3] << std::endl; 
	int screenRows = atoi(token[0].c_str());
	int screenCols = atoi(token[1].c_str());
	numOfTiles = atoi(token[2].c_str());
	sf::Texture* texture = TextureManager::GetInstance().retrieveTexture(token[3]);
	
	tiles = new GroundTile[20];
	//*TextureManager::GetInstance().retrieveTexture(token[6], "Tiles");	
	//AddTexture("Images/Blank.png", "Blank");

	token.clear();

	while(!level.eof()) 
	{
		getline(level, str);
		Tokenize(str, token, "||");
		
		for(int i = 0; i < token.size(); i++)
		{
			std::string singleTile;
			std::vector <std::string> tileToken;
			Tokenize(token[i], tileToken, ",");
			
			tiles[currentRow] = GroundTile(atoi(tileToken[i].c_str()), sf::Vector2i(i * TILE_HEIGHT, currentRow * TILE_WIDTH), screenRows, screenCols, texture);
		}
		currentRow++;
		token.clear();
	}
	level.close();
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