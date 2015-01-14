#include "Global.h"

Global::Global()
	:inventory(new PlayerInventory())
{
	test = sf::Sound(*AudioManager::GetInstance().retrieveSound(std::string("GainItem")));
}

Global::~Global()
{
	//for(int i = 0; i < 20; i++)
	//{
	//	delete currentTileSheet[i];
	//}
	//delete[] currentTileSheet;
	
}

void Global::CleanUp()
{
	for(int i = 0; i < 20; i++)
	{
		delete currentTileSheet[i];
	}
	delete inventory;
}

void Global::ParseXML() {
	pugi::xml_document doc;

	pugi::xml_parse_result result = doc.load_file("Levels.xml");
	std::cout << result.description() << std::endl;

	pugi::xml_node gameNode = doc.child("Game");

	for(pugi::xml_node level = gameNode.child("Level"); level; level = level.next_sibling("Level")) {
		std::cout << "Level Number: " << level.attribute("number").value() << std::endl;
		//std::string str = "Level ";st
		std::string levelNumber = level.attribute("number").as_string();
		std::string str = "Level " + levelNumber;
		std::string tilesheetName = level.attribute("tilesheet").as_string();
		//str += levelNumber;
		
		int levelSize = level.attribute("size").as_int();
		levelSizes[str] = levelSize;
		//std::cout << str << std::endl;
		for (pugi::xml_node room = level.child("Room"); room; room = room.next_sibling("Room")) {
			std::cout << "Room Number: " << room.attribute("number").value() << std::endl;
			std::string roomNumber = room.attribute("number").as_string();
			std::string str2 = "Room " + roomNumber;
			int roomSize = room.attribute("size").as_int();
			roomSizes[str2] = roomSize;
			roomTileSheets[str2] = tilesheetName;
			//std::cout << std::endl;
		}
	}

	std::map<std::string, sf::SoundBuffer*> temp;
	result = doc.load_file("Sounds.xml");
	
	for(pugi::xml_node sound = doc.child("Sound"); sound; sound = doc.next_sibling("Sound"))
	{
		temp[sound.attribute("name").as_string()] = new sf::SoundBuffer();
		temp[sound.attribute("name").as_string()]->loadFromFile(sound.attribute("path").as_string());
	}
	//AudioManager::GetInstance().SetupMap(temp);
	result = doc.load_file("PlayerStats.xml");

	pugi::xml_node playerXML = doc.child("Player");
	
	pugi::xml_node baseStats = playerXML.child("BaseStats");
	int i=0;

	for(auto& att : baseStats.attributes())
	{
		basePlayerStats[i] = att.as_float();
		i++;
	}
	
	baseStats = playerXML.child("Augments");

	for (pugi::xml_node a : baseStats.children("a"))
	{
		std::vector<float> temp;
		temp.push_back(a.attribute("bonusHealth").as_float());
		temp.push_back(a.attribute("bonusStamina").as_float());
		temp.push_back(a.attribute("bonusMelee").as_float());
		temp.push_back(a.attribute("bonusRangeDmg").as_float());
		temp.push_back(a.attribute("bonusAttSpeed").as_float());
		temp.push_back(a.attribute("bonusHookshoot").as_float());
		std::string tempStr = a.attribute("name").as_string();
		augments.emplace(tempStr, temp);
	}

	//for (auto& a : augments)
	//{
	//	std::cout << a[0] << "," << a[1] << "," << a[2] << "," << a[3] << "," << a[4] << std::endl;
	//}

	baseStats = playerXML.child("PlayerInventory");
	
	i=0;
	for (pugi::xml_node a : baseStats.children("item"))
	{
		std::cout << a.attribute("name").as_string() << ", " << a.attribute("amount").as_int() << std::endl;
		//PlayerInventory[i] = att.as_int();
		inventory->addItem(a.attribute("name").as_string(), a.attribute("amount").as_int());
		//std::cout << PlayerInventory[i] << std::endl;
		//i++;
	}

}

void Global::SavePlayer() {
	std::cout << "Saving the player" << std::endl;
	pugi::xml_document doc;

	pugi::xml_parse_result result = doc.load_file("PlayerStats.xml");
	std::cout << result << std::endl;
	pugi::xml_node playerNode = doc.child("Player");
	pugi::xml_node playerInventory = playerNode.child("PlayerInventory");
	
	int i = 0;
	for (auto& att: playerInventory.attributes()) {

		//std::cout << "Old value: " << att.name() << " " << att.as_int() << std::endl;
		//att.set_value(1);
		//std::cout << "New value: " << att.as_int() << std::endl;

		//Uncomment this to save PlayerInventory augmenets
		//att.set_value(PlayerInventory[i]);

	}
	//doc.save_file(std::cout);
	doc.save_file("PlayerStats.xml");
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

		std::cout << levelName << std::endl;
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


bool Global::checkPoint(const sf::Vector2f& p, const sf::FloatRect& r)
{
	if (p.x >= r.left && p.x < r.left + r.width && p.y >= r.top && p.y <= r.top + r.height)
		return true;
	return false;
}

void Global::calculateOffset()
{
	//grab height and width and calculate that offset
	xOffset = SCREEN_WIDTH / 2;
	yOffset = SCREEN_HEIGHT / 2;

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