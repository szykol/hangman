#include "Menu.h"

#include "Managers/StateManager.h"
#include "Game.h"

Menu::Menu()
{
	m_into = std::make_unique<sen::Button>("GAME");
	m_into->setPosition((sf::Vector2f)Application::getInitialWindowSize() / 2.f);

	m_into->setOnClickCallback([] {
		sen::StateManager::pushState<Game>();
	});

}

void Menu::update(float deltaTime, sf::RenderWindow & window)
{
	m_into->update(deltaTime);
}

void Menu::render(sf::RenderTarget & target)
{
	m_into->render(target);
}

void Menu::input(sf::RenderWindow & window)
{
}
