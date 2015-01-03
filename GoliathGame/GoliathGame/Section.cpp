#include "Section.h"
// include more tiles

Section::Section(int sectionNumber, std::string& s, sf::Vector2f& offset, std::vector<std::shared_ptr<Enemy>> &enemyList)
	:sectionNum(sectionNumber), pathToText(s), offset(offset), startPos(-999.0, -999.0)
{
	LoadTileMap(enemyList);
}

Section::~Section()
{
	for ( int j = 0; j < gDim.x * gDim.y; j++)
	{
		delete grid1[j];
	}
	delete[] grid1;
}

sf::Vector2f Section::getOffset()
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
		return true;
	}
	return false;
}

bool Section::checkPlayerInGrid(const BaseObject& player)
{
	return false;
}

std::vector<sf::Vector2f> Section::getIntersectPoints(const BaseObject& rect)
{
	std::vector<sf::Vector2f> temp;
	//If this is not the top left corner these calculations will not work
	sf::Vector2f p1 = sf::Vector2f(rect.sprite.getPosition().x / GAME_TILE_DIM, rect.sprite.getPosition().y / GAME_TILE_DIM);
	sf::Vector2f p2 = sf::Vector2f((rect.sprite.getPosition().x + GAME_TILE_DIM) / GAME_TILE_DIM, (rect.sprite.getPosition().y + GAME_TILE_DIM) / GAME_TILE_DIM);

	for(int i = p1.x; i <= p2.x; i++)
	{
		for (int j = p1.y; j <= p2.y; j++)
		{
			temp.push_back(sf::Vector2f(j, i));
		}
	}
	return temp;
}

std::vector<sf::Vector2f> Section::getIntersectPoints(const sf::Vector2f& p1, const sf::Vector2f& p2)
{
	std::vector<sf::Vector2f> temp;
	sf::Vector2f p3 = sf::Vector2f(p1.x / GAME_TILE_DIM, p1.y / GAME_TILE_DIM);
	sf::Vector2f p4 = sf::Vector2f(p2.x / GAME_TILE_DIM, p2.y / GAME_TILE_DIM);

	for(int i = p3.x; i <= p4.x; i++)
	{
		for (int j = p3.y; j <= p4.y; j++)
		{
			temp.push_back(sf::Vector2f(j, i));
		}
	}
	return temp;
}

void Section::surroundingRects(const sf::Vector2f& p1, const sf::Vector2f& p2, std::vector<Tile*>& nearTiles, bool checkHorz, bool checkVert)
{
	sf::Vector2f p3 = sf::Vector2f(p1.x / GAME_TILE_DIM, p1.y / GAME_TILE_DIM);
	sf::Vector2f p4 = sf::Vector2f(p2.x / GAME_TILE_DIM, p2.y / GAME_TILE_DIM);

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
			//if(grid1[(j*gDim.y) + i]->getCollidable())
			if(grid1[(j*gDim.y) + i]->getFlags() & TILE::COLLIDABLEMASK)
			{
				nearTiles.push_back(grid1[(j*gDim.y) + i]);
			}
		}
	}

}

void Section::checkGrapple(const sf::Vector2f& p1, const sf::Vector2f& p2, std::vector<Tile*>& nearTiles)
{
	sf::Vector2f p3 = sf::Vector2f(p1.x / GAME_TILE_DIM, p1.y / GAME_TILE_DIM);
	sf::Vector2f p4 = sf::Vector2f(p2.x / GAME_TILE_DIM, p2.y / GAME_TILE_DIM);

	for(int i = p3.x; i <= p4.x; i++)
	{
		for (int j = p3.y; j <= p4.y; j++)
		{
			//if(grid1[(j*gDim.y) + i]->getCollidable() || grid1[(j*gDim.y) + i]->getGrappleable() )
			if((grid1[(j*gDim.y) + i]->getFlags() & TILE::COLLIDABLEMASK) || 
				(grid1[(j*gDim.y) + i]->getFlags() & TILE::GRAPPLEABLEMASK))
				nearTiles.push_back(grid1[(j*gDim.y) + i]);
		}
	}
}

void Section::checkInteractable(const sf::Vector2f& p1, const sf::Vector2f& p2, std::vector<Tile*>& nearTiles)
{
	sf::Vector2f p3 = sf::Vector2f(p1.x / GAME_TILE_DIM, p1.y / GAME_TILE_DIM);
	sf::Vector2f p4 = sf::Vector2f(p2.x / GAME_TILE_DIM, p2.y / GAME_TILE_DIM);

	for(int i = p3.x; i <= p4.x; i++)
	{
		for (int j = p3.y; j <= p4.y; j++)
		{
			//if(grid1[(j*gDim.y) + i]->getInteractable())
			if((grid1[(j*gDim.y) + i]->getFlags() & TILE::INTERACTABLEMASK) != 0)
			{
				nearTiles.push_back(grid1[(j*gDim.y) + i]);
			}
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
		if(grid1[i]->getTileNum() >= 0)
		{
			g.currentTileSheet[grid1[i]->getTileNum()]->setPosition(sf::Vector2f(grid1[i]->left, grid1[i]->top));
			w.draw(*g.currentTileSheet[grid1[i]->getTileNum()]);
		}
		//if(grid[i]->objectNum != -999)
		//	grid[i]->draw(w);
	}
}

void Section::print()
{
	for(int i = 0; i < gDim.x * gDim.y; i++)
	{
		std::cout << grid1[i]->getTileNum() << std::endl;
	}
}


//Loading is the text file from the given file path
//Parses the first line of the file to get information about the rest of the file.
//Continues through the file until it hits the end of the file and creates tiles based off information parsed in
void Section::LoadTileMap(std::vector<std::shared_ptr<Enemy>> &enemyList)
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
	gDim = sf::Vector2i(atoi(token[0].c_str()), atoi(token[1].c_str()));

	numOfTiles = atoi(token[2].c_str());
	
	try
	{
		grid1 = new Tile*[gDim.x * gDim.y];
		for (int i = 0; i < gDim.x * gDim.y; i++)
		{
			grid1[i] = new Tile();
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

	while(!ifs.eof()) 
	{
		std::getline(ifs, str);
		Tokenize(str, token, "||");
		
		for(int i = 0; i < token.size(); i++)
		{
			std::vector <std::string> tileToken;
			Tokenize(token[i], tileToken, ",");
			
			int tileType = atoi(tileToken[0].c_str());
			int x = atoi(tileToken[2].c_str());
			int y = atoi(tileToken[1].c_str());

			switch(tileType)
			{
			//Ranged enemy
			case -4:
				enemyList.push_back(std::shared_ptr<Enemy>(new Enemy("Test", x * GAME_TILE_DIM + offset.x, y * GAME_TILE_DIM + offset.y, 10)));
				break;
			case -3:
				enemyList.push_back(std::shared_ptr<Enemy>(new Enemy("Test", x * GAME_TILE_DIM + offset.x, y * GAME_TILE_DIM + offset.y)));
				break;
			case -1:
				startPos = sf::Vector2f(x * GAME_TILE_DIM + offset.x, y * GAME_TILE_DIM + offset.y);
				break;
			case 5:
			case 6:
				//Grappleable
				delete grid1[(y*gDim.y) + x];
				grid1[(y*gDim.y) + x] = new Tile(sf::Vector2f(x * GAME_TILE_DIM + offset.x, y * GAME_TILE_DIM + offset.y), 
					tileType, 0x02, false, true);
		
				break;
			case 7:
				//Grappleable and collidable
				delete grid1[(y*gDim.y) + x];
				grid1[(y*gDim.y) + x] = new Tile(sf::Vector2f(x * GAME_TILE_DIM + offset.x, y * GAME_TILE_DIM + offset.y), 
					tileType, 0x03, true, true);
				break;
			case 17:
				//Treasure
				delete grid1[(y*gDim.y) + x];
				grid1[(y*gDim.y) + x] = new Tile(sf::Vector2f(x * GAME_TILE_DIM + offset.x, y * GAME_TILE_DIM + offset.y), 
					tileType, 0x09, true, false, true);
				break;
			case 18:
			case 19:
				//Interactable
				delete grid1[(y*gDim.y) + x];
				grid1[(y*gDim.y) + x] = new Tile(sf::Vector2f(x * GAME_TILE_DIM + offset.x, y * GAME_TILE_DIM + offset.y), 
					tileType, 0x04, false, false, true);
				break;
			default:
				delete grid1[(y*gDim.y) + x];
				grid1[(y*gDim.y) + x] = new Tile(sf::Vector2f(x * GAME_TILE_DIM + offset.x, y * GAME_TILE_DIM + offset.y), 
					tileType, 0x01);
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