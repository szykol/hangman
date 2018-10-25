#include "Menu.h"

#include "Managers/StateManager.h"
#include "Game.h"
#include "Managers/CacheSystem.h"
#include "Languages.h"

Menu::Menu(int language)
	: m_text("HANGMAN"), m_difficulty("Choose Your Difficulty")
{
	auto center = (sf::Vector2f)Application::getInitialWindowSize() / 2.f;

	m_text.setPosition(center.x, center.y - 250.f);
	m_text.setCharacterSize(50U);

	m_difficulty.setPosition(center.x, center.y - 150.f);
	m_difficulty.setCharacterSize(30U);

	std::vector<const char*> levels;

	if (language == Language::ENGLISH) 
		levels = std::vector<const char*>{ "Easy", "Medium", "Hard" };
	else
	{
		levels = std::vector<const char*>{ "Latwy", "Sredni", "Trudny" };
		m_difficulty.setString("Wybierz poziom trudnosci");
	}


	for (int i = Level::EASY; i <= Level::HARD; ++i)
	{
		auto temp = std::make_shared<sen::Button>(levels[i]);

		temp->setOnClickCallback([i, language] {
			sen::StateManager::pushState<Game>(i, language);
		});

		m_bc.pushButtons(temp);
		m_bc.placeButtons();
	}
	m_bc.setButtonFixedSize(sf::Vector2f(120.f, 50.f));
}

void Menu::update(float deltaTime, sf::RenderWindow & window)
{
	m_bc.update(deltaTime);
}

void Menu::render(sf::RenderTarget & target)
{
	m_bc.render(target);
	m_difficulty.render(target);
	m_text.render(target);
}

void Menu::input(sf::RenderWindow & window)
{
}
