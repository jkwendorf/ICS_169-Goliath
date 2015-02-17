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
	window.setVerticalSyncEnabled(true);
	StateManager::getInstance().addState(MAIN_MENU, new MainMenuState(), true);
	StateManager::getInstance().addState(LEVEL_SELECT, new LevelSelectState());
	//StateManager::getInstance().addState(GAME, new GameState());
	//StateManager::getInstance().addState(END_GAME, new EndGameState());

	int frame = 0;
	float time = 0;

	sf::Clock deltaTimer;
    while (window.isOpen())
    {
		float deltaTime = deltaTimer.restart().asSeconds();
		/*time += deltaTime;
		frame++;
		
		if(time >= 1.0f)
		{
			time -= 1.0f;
			std::cout << "Frames: " << frame << std::endl;
			frame = 0;
		}*/

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
			if (event.type == sf::Event::GainedFocus)
			{
				infocus = true;
				deltaTime = deltaTimer.restart().asSeconds();
			}
			if (event.type == sf::Event::LostFocus)
			{
				infocus = false;
				std::cout << "Lost Focus" << std::endl;
			}

			//infocus = event.type == sf::Event::GainedFocus ? true: false;
			StateManager::getInstance().getCurrentState()->handleEvent(event);
        }

		if(infocus)
		{
			StateManager::getInstance().getCurrentState()->update(deltaTime);
		}

		window.clear(sf::Color::Black);
		StateManager::getInstance().getCurrentState()->draw(window);
		window.display();

		if(StateManager::getInstance().shouldQuit())
			window.close();
		if(StateManager::getInstance().shouldResetTime())
		{
			deltaTimer.restart();
			StateManager::getInstance().setTimeReset(false);
		}
    }

	window.close();

	StateManager::getInstance().DeleteAllStates();
	
	Global::GetInstance().SavePlayer();
	Global::GetInstance().CleanUp();

	std::cout << "\n Press ENTER to continue...";
	std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );

    return 0;
}