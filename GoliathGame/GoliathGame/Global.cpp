#include "Global.h"

Global::Global()
{
}

Global::~Global()
{
	//for(int i = 0; i < 20; i++)
	//{
	//	delete currentTileSheet[i];
	//}
	//delete[] currentTileSheet;
}

//Call this before handling levels.
void Global::ParseLevelSizes(std::map<std::string, int>& mapToUpdate, std::string& fileName)
{
	//Get Text File
	std::ifstream ifs;
	ifs.open(fileName);
	std::string str;

	if (!ifs.good()) 
	{
		std::cout << "Level Size file not found." << std::endl;
	}

	while (!ifs.eof()) 
	{
		//Get next line
		std::getline(ifs, str);

		//Find the position of where the || starts
		std::string::size_type pos = str.find_first_of("||", 0);

		//Splits the string up.
		std::string levelName = str.substr(0, pos);
		int size = atoi(str.substr(pos+2, str.length() - pos).c_str());

		//Insert it into the map.
		mapToUpdate[levelName] = size;
	}

	ifs.close();
}

void Global::ParseLevelTileSheets() 
{
	//Get Text File
	std::ifstream ifs;
	ifs.open("media/levels/levelTileSheets.txt");
	std::string str;

	if (!ifs.good()) 
	{
		std::cout << "Level Tile Sheet file not found." << std::endl;
	}

	while (!ifs.eof()) 
	{
		//Get next line
		std::getline(ifs, str);

		//Find the position of where the || starts
		std::string::size_type pos = str.find_first_of("||", 0);

		//Splits the string up.
		std::string levelName = str.substr(0, pos);
		std::string tileSheet = str.substr(pos+2, str.length() - pos).c_str();

		//Insert it into the map.
		roomTileSheets[levelName] = tileSheet;
	}

	ifs.close();
}


bool Global::checkPoint(const sf::Vector2i& p, const sf::IntRect& r)
{
	if (p.x >= r.left && p.x < r.left + r.width && p.y >= r.top && p.y <= r.top + r.height)
		return true;
	return false;
}

void Global::calculateOffset()
{
	//grab height and width and calculate that offset
	xOffset = SCREEN_WIDTH / 5;
	yOffset = SCREEN_HEIGHT / 8;

}

void Global::SetUpTileSheet(sf::Texture* texture)
{
	float ratio = (float)GAME_TILE_DIM / 100;
	for(int i = 0; i < TileSheetRows * TileSheetCols; i ++)
	{
		delete currentTileSheet[i];
		currentTileSheet[i] = new sf::Sprite(*texture);
		sf::IntRect temp = sf::IntRect(EDITOR_TILE_WIDTH * (i % TileSheetCols),
					EDITOR_TILE_HEIGHT * (i / TileSheetCols),EDITOR_TILE_WIDTH, EDITOR_TILE_HEIGHT);
		//std::cout << "Pos x: " <<  temp.left << ". Pos Y: " << temp.top << std::endl;
		currentTileSheet[i]->setTextureRect(temp);
		currentTileSheet[i]->setScale(ratio, ratio);
	}
}