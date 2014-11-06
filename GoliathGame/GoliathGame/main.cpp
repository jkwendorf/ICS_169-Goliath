#include "StateManager.h"
#include "Global.h"

int main()
{
	Global::GetInstance().ParseLevelSizes();
	// JW: Our window is set to 200x200, these should be set by global variables
	Global::GetInstance().setFPS(30);
	Global::GetInstance().setScreenSize(1280, 720);
	static sf::RenderWindow window(sf::VideoMode(Global::GetInstance().x, Global::GetInstance().y), "Goliath Game");
	// JW: Setting the framerate to 30, but this should be set by a global variable
	window.setFramerateLimit(Global::GetInstance().fps);
	StateManager sM;
	

	sf::Clock deltaTimer;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape)
                window.close();

			sM.handleEvent(event);
        }
		sM.update(deltaTimer.restart().asSeconds());

        window.clear();
		sM.draw(window);
        window.display();
    }

    return 0;
}