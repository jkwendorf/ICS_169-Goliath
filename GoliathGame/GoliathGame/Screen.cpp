#include "Screen.h"
#include "GroundTile.h"
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

}


void Screen::LoadTileMap()
{
	int currentRow = 0;
	level.open(pathToText);
	std::string str;

	//if(!level.good())
		//std::cout << "Level text file did not load!" << std::endl; 
		

	getline(level, str);
	std::vector <std::string> token;
	Tokenize(str, token, ", ");

	//Sets up the txtWidth, txtHeight, and tileSheet with the 
	// values in the level.txt

	//*TextureManager::GetInstance().retrieveTexture(token[6], "Tiles");	
	//AddTexture("Images/Blank.png", "Blank");

	token.clear();

	while(!level.eof()) 
	{
		getline(level, str);
		Tokenize(str, token);
		//for(int i = 0; i < token.size(); i++)
		//{
			//tileMap[currentRow][i] = new Tile(atoi(token[i].c_str()), i * TILE_HEIGHT, currentRow * TILE_WIDTH);
		//}
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