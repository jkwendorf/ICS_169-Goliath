#include "StateManager.h"

int main()
{
	// JW: Our window is set to 200x200, these should be set by global variables
    sf::RenderWindow window(sf::VideoMode(200, 200), "Goliath Game");
	// JW: Setting the framerate to 30, but this should be set by a global variable
	window.setFramerateLimit(30);
	StateManager sM;

	sf::Clock deltaTimer;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape)
                window.close();

			// JW: We might want to have the StateManager process any events in here
        }
		sM.update(deltaTimer.restart().asSeconds());

        window.clear();
		sM.draw(window);
        window.display();
    }

    return 0;
}