#include "Global.h"

Global::Global()
{
}

Global::~Global()
{

}

//Call this before handling levels.
void Global::ParseLevelSizes() 
{
	//Get Text File
	std::ifstream ifs;
	ifs.open("media/levels/levelSizes.txt");
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
		levelSizes[levelName] = size;
	}

	ifs.close();
}

void Global::setScreenSize(int w, int h)
{
	y = h;
	x = w;
	calculateOffset();
}

void Global::setFPS(int f)
{
	fps = f;
}

void Global::calculateOffset()
{
	//grab height and width and calculate that offset
}