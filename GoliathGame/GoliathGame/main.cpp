#include "StateManager.h"
#include "Global.h"
//#include <vld.h>

int main()
{
	Global::GetInstance().ParseLevelXML();
	Global::GetInstance().calculateOffset();
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Goliath Game");
	// JW: Setting the framerate to 30, but this should be set by a global variable
	window.setFramerateLimit(FPS);
	StateManager* sM = new StateManager();
	
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

			sM->handleEvent(event);
        }
		deltaTime = min(deltaTime, maxTime);
		//std::cout<< deltaTime << std::endl;
		sM->update(deltaTime);

        window.clear();
		sM->draw(window);
        window.display();
    }

	window.close();
	delete sM;
	Global::GetInstance().CleanUp();
	//std::cout << "\n Press ENTER to continue...";
	//std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );

    return 0;
}