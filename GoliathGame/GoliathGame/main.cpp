#include "StateManager.h"
#include "Global.h"
#include <vld.h>

int main()
{
	srand (time (NULL));
	Global::GetInstance().ParseXML();
	bool infocus = true;
	Global::GetInstance().calculateOffset();
	Global::GetInstance().LoadEnemyAttributes();
	Global::GetInstance().LoadPlayerAttribtues();
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Goliath Game");
	// JW: Setting the framerate to 30, but this should be set by a global variable
	window.setFramerateLimit(FPS);
	StateManager::getInstance().addState(MAIN_MENU, new MainMenuState(), true);
	StateManager::getInstance().addState(LEVEL_SELECT, new LevelSelectState());
	//StateManager::getInstance().addState(GAME, new GameState());
	//StateManager::getInstance().addState(END_GAME, new EndGameState());

	float maxTime = 1.f/FPS;
	sf::Clock deltaTimer;
    while (window.isOpen())
    {
		float deltaTime = deltaTimer.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
			if (event.type == sf::Event::GainedFocus)
				infocus = true;
			if (event.type == sf::Event::LostFocus)
				infocus = false;
			//infocus = event.type == sf::Event::GainedFocus ? true: false;
			StateManager::getInstance().getCurrentState()->handleEvent(event);
        }
		deltaTime = min(deltaTime, maxTime);
		//std::cout<< deltaTime << std::endl;
		if(infocus)
		{
			StateManager::getInstance().getCurrentState()->update(deltaTime);
		}

		window.clear(sf::Color::White);
		StateManager::getInstance().getCurrentState()->draw(window);
		window.display();

		if(StateManager::getInstance().shouldQuit())
			window.close();
    }

	window.close();

	StateManager::getInstance().DeleteAllStates();
	
	Global::GetInstance().SavePlayer();
	Global::GetInstance().CleanUp();

	std::cout << "\n Press ENTER to continue...";
	std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );

    return 0;
}