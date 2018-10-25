#include "Languages.h"

#include "Managers/CacheSystem.h"
#include "Managers/StateManager.h"

#include "Menu.h"

Languages::Languages()
	:m_text("HANGMAN")
{
	auto center = (sf::Vector2f)Application::getInitialWindowSize() / 2.f;

	m_text.setPosition(center.x, center.y - 250.f);
	m_text.setCharacterSize(50U);


	const char* names[3] = { "English", "Polski"};
	for (int i = 0; i < 2; ++i)
	{
		auto temp = std::make_shared<sen::Button>(names[i]);

		temp->setOnClickCallback([i] {
			sen::StateManager::pushState<Menu>(i);
		});

		m_bc.pushButtons(temp);
		m_bc.placeButtons();
	}
	m_bc.setButtonFixedSize(sf::Vector2f(120.f, 50.f));
}

void Languages::update(float deltaTime, sf::RenderWindow & window)
{
	m_bc.update(deltaTime);
}

void Languages::render(sf::RenderTarget & target)
{
	m_bc.render(target);
}

void Languages::input(sf::RenderWindow & window)
{
}
