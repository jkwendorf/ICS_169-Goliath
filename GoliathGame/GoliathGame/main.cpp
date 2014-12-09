#include "StateManager.h"
#include "Global.h"
//#include <vld.h>

int main()
{
	bool infocus = true;
	Global::GetInstance().ParseLevelXML();
	Global::GetInstance().calculateOffset();
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Goliath Game");
	// JW: Setting the framerate to 30, but this should be set by a global variable
	window.setFramerateLimit(FPS);
	
	StateManager::getInstance().addState(GAME, new GameState(), true);
	StateManager::getInstance().addState(MAIN_MENU, new MainMenuState());

	float maxTime = 1.f/FPS;
	sf::Clock deltaTimer;
    while (window.isOpen())
    {
		float deltaTime = deltaTimer.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape)
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
			window.clear();
			StateManager::getInstance().getCurrentState()->draw(window);
			window.display();
		}

    }

	window.close();
	Global::GetInstance().CleanUp();
	//std::cout << "\n Press ENTER to continue...";
	//std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );

	StateManager::getInstance().DeleteAllStates();
    return 0;
}