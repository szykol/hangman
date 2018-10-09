#include "Game.h"

#include "Application.h"
#include "Managers/CacheSystem.h"
#include "GuessWord.h"

Game::Game()
{
	m_welcome = std::make_unique<sen::Text>("Welcome");
	m_welcome->setPosition((sf::Vector2f)Application::getInitialWindowSize() / 2.f);
	m_background = sen::CacheSystem::get<sf::Texture>("res/Images/chair.jpeg");
	Application::setBackgroundImage(*m_background);

	auto pos = sf::Vector2f{ 50.f, 500.f };
	for (char z = 'A'; z <= 'Z'; ++z)
	{
		auto button = sen::Button{ z };

		button.setPosition(pos);
		button.setSize(sf::Vector2f(45.f, 45.f));
		pos.x += 70.f;

		button.addListener(sen::ButtonEvent::CLICK, [this](sen::Button& b) {
			char znak = b.getTextObject().getString().toAnsiString().at(0);
			m_guessWord.checkInput(znak);
		});

		m_buttons.push_back(std::move(button));

	}
}

void Game::update(float deltaTime, sf::RenderWindow & window)
{
	for (auto& b : m_buttons)
		b.update(deltaTime);
}

void Game::render(sf::RenderTarget & target)
{
	m_welcome->render(target);
	m_guessWord.render(target);

	for (auto& b : m_buttons)
		b.render(target);
}

void Game::input(sf::RenderWindow & window)
{
	
}

Game::~Game()
{
	Application::disableBackgroundImage();
}

