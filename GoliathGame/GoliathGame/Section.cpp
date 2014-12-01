#include "Section.h"
// include more tiles

Section::Section(int sectionNumber, std::string& s, sf::Vector2i& offset, std::vector<Enemy*> &enemyList)
	:sectionNum(sectionNumber), pathToText(s), offset(offset), startPos(-999.0, -999.0)
{
	LoadTileMap(enemyList);
}

Section::~Section()
{
	for ( int j = 0; j < gDim.x * gDim.y; j++)
	{
		delete[] grid1[j];
	}
	delete[] grid1;
}

sf::Vector2i Section::getOffset()
{
	return offset;
}

sf::Vector2i Section::getGridDim()
{
	return gDim;
}

int Section::getWidth()
{
	return gDim.y * GAME_TILE_DIM;
}

int Section::getHeight()
{
	return gDim.x * GAME_TILE_DIM;
}

int Section::getGridNum()
{
	return sectionNum;
}

sf::Vector2f Section::getStartPos()
{
	return startPos;
}

bool Section::inWindow()
{
	//std::cout << Global::GetInstance().topLeft.x << std::endl;
	if((offset.x <= Global::GetInstance().topLeft.x && offset.x + getWidth() >= Global::GetInstance().topLeft.x) || 
		(offset.x <= Global::GetInstance().topLeft.x + SCREEN_WIDTH && offset.x + getWidth() >= Global::GetInstance().topLeft.x + SCREEN_WIDTH)||
		(offset.x >= Global::GetInstance().topLeft.x && offset.x + getWidth() <= Global::GetInstance().topLeft.x + SCREEN_WIDTH))
	{
		//std::cout << sectionNum << std::endl;
		return true;
	}
	return false;
}

bool Section::checkPlayerInGrid(const BaseObject& player)
{
	return false;
}

std::vector<sf::Vector2i*> Section::getIntersectPoints(const BaseObject& rect)
{
	std::vector<sf::Vector2i*> temp;
	//If this is not the top left corner these calculations will not work
	sf::Vector2i p1 = sf::Vector2i(rect.sprite.getPosition().x / GAME_TILE_DIM, rect.sprite.getPosition().y / GAME_TILE_DIM);
	sf::Vector2i p2 = sf::Vector2i((rect.sprite.getPosition().x + GAME_TILE_DIM) / GAME_TILE_DIM, (rect.sprite.getPosition().y + GAME_TILE_DIM) / GAME_TILE_DIM);

	for(int i = p1.x; i <= p2.x; i++)
	{
		for (int j = p1.y; j <= p2.y; j++)
		{
			temp.push_back(new sf::Vector2i(j, i));
		}
	}
	return temp;
}

std::vector<sf::Vector2i*> Section::getIntersectPoints(const sf::Vector2i& p1, const sf::Vector2i& p2)
{
	std::vector<sf::Vector2i*> temp;
	sf::Vector2i p3 = sf::Vector2i(p1.x / GAME_TILE_DIM, p1.y / GAME_TILE_DIM);
	sf::Vector2i p4 = sf::Vector2i(p2.x / GAME_TILE_DIM, p2.y / GAME_TILE_DIM);

	for(int i = p3.x; i <= p4.x; i++)
	{
		for (int j = p3.y; j <= p4.y; j++)
		{
			temp.push_back(new sf::Vector2i(j, i));
		}
	}
	return temp;
}

void Section::surroundingRects(const sf::Vector2i& p1, const sf::Vector2i& p2, std::vector<Tile*>& nearTiles, bool checkHorz, bool checkVert)
{
	sf::Vector2i p3 = sf::Vector2i(p1.x / GAME_TILE_DIM, p1.y / GAME_TILE_DIM);
	sf::Vector2i p4 = sf::Vector2i(p2.x / GAME_TILE_DIM, p2.y / GAME_TILE_DIM);

	if(checkHorz)
	{
		if (p3.x >= 1)
			p3.x--;
		if (p4.x < gDim.y-1)
			p4.x++;
	}
	if (checkVert)
	{
		if (p3.y >= 1)
				p3.y--;
		if (p4.y < gDim.x-1)
				p4.y++;
	}

	for(int i = p3.x; i <= p4.x; i++)
	{
		for (int j = p3.y; j <= p4.y; j++)
		{
			if(grid1[(j*gDim.y) + i][2] == 1)
			{
				nearTiles.push_back(new Tile(sf::Vector2f(GAME_TILE_DIM * (grid1[(j*gDim.y) + i][1] % gDim.y) + offset.x, GAME_TILE_DIM * (grid1[(j*gDim.y) + i][1] / gDim.y)+ offset.y), 
								sf::Vector2f(GAME_TILE_DIM, GAME_TILE_DIM), grid1[(j*gDim.y) + i][0], grid1[(j*gDim.y) + i][2], grid1[(j*gDim.y) + i][3], grid1[(j*gDim.y) + i][4]));
			}
		}
	}

}

void Section::checkGrapple(const sf::Vector2i& p1, const sf::Vector2i& p2, std::vector<Tile*>& nearTiles)
{
	sf::Vector2i p3 = sf::Vector2i(p1.x / GAME_TILE_DIM, p1.y / GAME_TILE_DIM);
	sf::Vector2i p4 = sf::Vector2i(p2.x / GAME_TILE_DIM, p2.y / GAME_TILE_DIM);

	for(int i = p3.x; i <= p4.x; i++)
	{
		for (int j = p3.y; j <= p4.y; j++)
		{
			if(grid1[(j*gDim.y) + i][2] == 1 || grid1[(j*gDim.y) + i][3] == 1 )
				nearTiles.push_back(new Tile(sf::Vector2f(GAME_TILE_DIM * (grid1[(j*gDim.y) + i][1] % gDim.y) + offset.x, GAME_TILE_DIM * (grid1[(j*gDim.y) + i][1] / gDim.y)+ offset.y), 
								sf::Vector2f(GAME_TILE_DIM, GAME_TILE_DIM), grid1[(j*gDim.y) + i][0], grid1[(j*gDim.y) + i][2], grid1[(j*gDim.y) + i][3], grid1[(j*gDim.y) + i][4]));
		}
	}
}

void Section::checkInteractable(const sf::Vector2i& p1, const sf::Vector2i& p2, std::vector<Tile*>& nearTiles)
{
	sf::Vector2i p3 = sf::Vector2i(p1.x / GAME_TILE_DIM, p1.y / GAME_TILE_DIM);
	sf::Vector2i p4 = sf::Vector2i(p2.x / GAME_TILE_DIM, p2.y / GAME_TILE_DIM);

	for(int i = p3.x; i <= p4.x; i++)
	{
		for (int j = p3.y; j <= p4.y; j++)
		{
			if(grid1[(j*gDim.y) + i][4] == 1)
				nearTiles.push_back(new Tile(sf::Vector2f(GAME_TILE_DIM * (grid1[(j*gDim.y) + i][1] % gDim.y) + offset.x, GAME_TILE_DIM * (grid1[(j*gDim.y) + i][1] / gDim.y)+ offset.y), 
								sf::Vector2f(GAME_TILE_DIM, GAME_TILE_DIM), grid1[(j*gDim.y) + i][0], grid1[(j*gDim.y) + i][2], grid1[(j*gDim.y) + i][3], grid1[(j*gDim.y) + i][4]));
		}
	}
}


void Section::update(float deltaTime)
{

}

void Section::draw(sf::RenderWindow& w)
{
	Global g = Global::GetInstance();
	for(int i = 0; i < gDim.x * gDim.y; i++)
	{
		if(grid1[i][0] >= 0)
		{
			g.currentTileSheet[grid1[i][0]]->setPosition(GAME_TILE_DIM * (grid1[i][1] % gDim.y) + offset.x,
				GAME_TILE_DIM * (grid1[i][1] / gDim.y)+ offset.y);
			w.draw(*g.currentTileSheet[grid1[i][0]]);
		}
		//if(grid[i]->objectNum != -999)
		//	grid[i]->draw(w);
	}
}

void Section::print()
{
	for(int i = 0; i < gDim.x * gDim.y; i++)
	{
		std::cout << grid1[i][0] << std::endl;
	}
}


//Loading is the text file from the given file path
//Parses the first line of the file to get information about the rest of the file.
//Continues through the file until it hits the end of the file and creates tiles based off information parsed in
void Section::LoadTileMap(std::vector<Enemy*> &enemyList)
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
	gDim = sf::Vector2i(atoi(token[0].c_str()), atoi(token[1].c_str()));

	numOfTiles = atoi(token[2].c_str());
	//std::cout << "Token[3] " << token[3] << std::endl; 
	
	try
	{
		grid1 = new int*[gDim.x * gDim.y];
		for (int i = 0; i < gDim.x * gDim.y; i++)
		{
			int* t = new int[5];
			for (int j = 0; j < 5; j++)
			{
				t[j] = -999;
			}
			grid1[i] = t;
		}
	} 
	catch(std::bad_alloc ex)
	{
		std::cout << "Allocation Failure" << std::endl;
		return;
	}


	//*TextureManager::GetInstance().retrieveTexture(token[6], "Tiles");	
	//AddTexture("Images/Blank.png", "Blank");

	token.clear();
	float ratio = (float)GAME_TILE_DIM / 100;
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
			int tileType = atoi(tileToken[0].c_str());
			int x = atoi(tileToken[2].c_str());
			int y = atoi(tileToken[1].c_str());
			grid1[(y*gDim.y) + x][0] = tileType;
			grid1[(y*gDim.y) + x][1] = (y*gDim.y) + x;
			switch(tileType)
			{
			//Ranged enemy
			case -4:
				enemyList.push_back(new Enemy("Test", x * GAME_TILE_DIM + offset.x, y * GAME_TILE_DIM + offset.y, 10));
				break;
			case -3:
				enemyList.push_back(new Enemy("Test", x * GAME_TILE_DIM + offset.x, y * GAME_TILE_DIM + offset.y));
				break;
			case -1:
				startPos = sf::Vector2f(x * GAME_TILE_DIM + offset.x, y * GAME_TILE_DIM + offset.y);
				grid1[(y*gDim.y) + x][2] = 0;
				grid1[(y*gDim.y) + x][3] = 0;
				grid1[(y*gDim.y) + x][4] = 0;
				break;
			case 5:
			case 6:
			case 7:
				//Grappleable
				grid1[(y*gDim.y) + x][2] = 0;
				grid1[(y*gDim.y) + x][3] = 1;
				grid1[(y*gDim.y) + x][4] = 0;
				break;
			case 18:
			case 19:
				//Interactable
				grid1[(y*gDim.y) + x][2] = 0;
				grid1[(y*gDim.y) + x][3] = 0;
				grid1[(y*gDim.y) + x][4] = 1;
				break;
			default:
				grid1[(y*gDim.y) + x][2] = 1;
				grid1[(y*gDim.y) + x][3] = 0;
				grid1[(y*gDim.y) + x][4] = 0;
			}
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