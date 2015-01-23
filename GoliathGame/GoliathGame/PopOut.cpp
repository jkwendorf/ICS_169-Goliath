#include "PopOut.h"

PopOut::PopOut()
	:active(false),
	background(sf::Sprite(*TextureManager::GetInstance().retrieveTexture("PopOut"), sf::IntRect(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 720, 360)))
{

}
	
PopOut::PopOut(std::string& text, std::function<void()> onPressButton1)
	:active(true),
	background(sf::Sprite(*TextureManager::GetInstance().retrieveTexture("PopOut"), sf::IntRect(0, 0, 720, 360)))
{
	background.setOrigin(background.getLocalBounds().width/2, background.getLocalBounds().height/2);
	background.setPosition(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
	f = new sf::Font();
	if(f->loadFromFile("media/fonts/arial.ttf"))
	{
		bM = new ButtonManager(sf::Vector2f(SCREEN_WIDTH/2 - 200, SCREEN_HEIGHT/2 + 50), 15, sf::Vector2f(400, 100), TextureManager::GetInstance().retrieveTexture("ButtonTest"), f); 
		bM->createButton("Ok", onPressButton1);
	}
	mtext = sf::Text(text, *f, (unsigned) 35);
	mtext.setColor(sf::Color::White);
	mtext.setPosition(background.getPosition().x - background.getGlobalBounds().width/4, 
		background.getPosition().y - background.getGlobalBounds().height/4);
}

PopOut::PopOut(std::string& text, std::function<void()> onPressButton1, std::function<void()> onPressButton2)
	:active(true),
	background(sf::Sprite(*TextureManager::GetInstance().retrieveTexture("PopOut"), sf::IntRect(0, 0, 720, 360)))
{
	background.setOrigin(background.getLocalBounds().width/2, background.getLocalBounds().height/2);
	background.setPosition(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
	f = new sf::Font();

	if(f->loadFromFile("media/fonts/arial.ttf"))
	{
		bM = new ButtonManager(sf::Vector2f(SCREEN_WIDTH/2+200, SCREEN_HEIGHT/2 + 200), 1, 15, sf::Vector2f(200, 100), TextureManager::GetInstance().retrieveTexture("ButtonTest"), f); 
		bM->createButton("Yes", onPressButton1);
		bM->createButton("No", onPressButton2);
	}
	mtext = sf::Text(text, *f, (unsigned) 35);
	mtext.setColor(sf::Color::White);
	mtext.setPosition(background.getPosition().x - background.getGlobalBounds().width/4, 
		background.getPosition().y - background.getGlobalBounds().height/4);
}
	
PopOut::~PopOut()
{
	delete f;
	if(bM)
		delete bM;
}

bool PopOut::checkActive()
{
	return active;
}
	
void PopOut::update(float deltaTime)
{
	if(active)
	{
		if((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Joystick::getAxisPosition(0, sf::Joystick::Y) < -25) && !isPressedUp)
		{
			bM->scrollUp();
			isPressedUp = true;
		}
		else if((!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Joystick::getAxisPosition(0, sf::Joystick::Y) > -25) && isPressedUp)
			isPressedUp = false;
	
		if((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Joystick::getAxisPosition(0, sf::Joystick::Y) > 25) &&!isPressedDown)
		{
			bM->scrollDown();
			isPressedDown = true;
		}
		else if((!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sf::Joystick::getAxisPosition(0, sf::Joystick::Y) < 25) && isPressedDown)
			isPressedDown = false;

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return) || sf::Joystick::isButtonPressed(0, 0))
		{
			bM->pressSelectedButton();
			active = false;
		}
	}
}
	
void PopOut::draw(sf::RenderWindow& window)
{
	if(active)
	{
		window.draw(background);
		window.draw(mtext);
		bM->draw(window);
	}
}