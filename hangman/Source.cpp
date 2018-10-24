#include <SFML/Graphics.hpp>

#include "fwk/Application.h"
#include "Managers/StateManager.h"
#include "States/FrameworkSplashScreen.h"
#include "Managers/CacheSystem.h"

#include <memory>

#include "Menu.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1200, 800), "hangman"/*,sf::Style::Fullscreen*/);
	window.setFramerateLimit(0U);

	Application::init(&window);

	auto bg = sen::CacheSystem::get<sf::Texture>("res/Images/bg.jpeg");
	Application::setBackgroundImage(*bg);
	
	sen::StateManager::pushState<Menu>();
	Application::run();

    return 0;	
}
