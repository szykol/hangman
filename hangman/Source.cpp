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
	//auto temp = std::make_unique<Menu>();
	
	//sen::StateManager::pushState(std::move(temp));
	sen::StateManager::pushState<Menu>();
	Application::run();

    return 0;
}
