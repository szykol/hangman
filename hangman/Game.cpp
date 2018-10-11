#include "Game.h"

#include "Application.h"
#include "Managers/CacheSystem.h"
#include "GuessWord.h"
#include "Util/Random.h"

#include <fstream>

void Game::handleEvents(sf::Event & evnt)
{
	if (!m_game) return;
	
	char z = toupper((char)evnt.text.unicode);

	if (std::find(m_letters.begin(), m_letters.end(), z) != m_letters.end()) return;

	if (evnt.type == sf::Event::TextEntered)
	{
		//std::cout << (char)evnt.text.unicode << std::endl;
		if (m_guessWord.checkInput(z))
		{
			m_welcome->setString("Correct!");
			m_welcome->setFillColor(sf::Color::Green);
			
			auto button = m_buttons.find(z);
			if (button != m_buttons.end())
			{
				button->second.setOutlineColor(sf::Color::Green);
				button->second.setActive(false);
				m_letters.push_back(z);
			}
			//b.setOutlineColor(sf::Color::Green);
		}
		else
		{
			m_welcome->setString("Wrong!");
			m_welcome->setFillColor(sf::Color::Red);
			auto button = m_buttons.find(z);
			if(button != m_buttons.end())
			{
				button->second.setOutlineColor(sf::Color::Red);
				button->second.getTextObject().setFillColor(sf::Color::Red);
				button->second.setActive(false);
				m_letters.push_back(z);
			}
			m_lives--;
		}
	}
}

Game::Game()
{
	m_welcome = std::make_unique<sen::Text>("Welcome");
	m_welcome->setPosition((sf::Vector2f)Application::getInitialWindowSize() / 2.f);
	m_background = sen::CacheSystem::get<sf::Texture>("res/Images/chair.jpeg");
	Application::setBackgroundImage(*m_background);
	
	getWords();
	loadRandomWord();

	auto pos = sf::Vector2f{ 50.f, 500.f };
	for (char z = 'A'; z <= 'Z'; ++z)
	{
		if (z > 'Q' && z < 'S')
		{
			pos = sf::Vector2f{ 300.f, 600.f };
		}

		auto button = sen::Button{ z };

		button.setPosition(pos);
		button.setSize(sf::Vector2f(45.f, 45.f));
		pos.x += 70.f;


		button.addListener(sen::ButtonEvent::CLICK, [this](sen::Button& b) {
			char z = b.getTextObject().getString().toAnsiString()[0];
			if (m_guessWord.checkInput(z))
			{
				m_welcome->setString("Correct!");
				m_welcome->setFillColor(sf::Color::Green);
				b.setOutlineColor(sf::Color::Green);
				b.setActive(false);
			}
			else
			{
				m_welcome->setString("Wrong!");
				m_welcome->setFillColor(sf::Color::Red);
				b.setOutlineColor(sf::Color::Red);
				b.getTextObject().setFillColor(sf::Color::Red);
				b.setActive(false);
				m_lives--;
			}
			m_letters.push_back(z);
		});

		m_buttons.insert(std::pair<char, sen::Button>(z, std::move(button) ));
	}
}

void Game::update(float deltaTime, sf::RenderWindow & window)
{
	if (m_reloadButton)
		m_reloadButton->update(deltaTime);

	if (!m_game) 
	{
		//m_welcome->setFillColor(sf::Color::Green);
		if (!m_reloadButton)
		{
			m_reloadButton = std::make_unique<sen::Button>("Reload");
			m_reloadButton->setPosition(sf::Vector2f(500.f, 100.f));
			m_reloadButton->setOnClickCallback([this]{
				resetGame();
			});
			//m_welcome->setString("You've won");
		}
		return;
	}

	for (auto& b : m_buttons)
		b.second.update(deltaTime);

	

	if (m_shouldPopReloadButton)
	{
		m_reloadButton = nullptr;
		m_shouldPopReloadButton = false;
	}

	if (m_lives == 0)
	{
		m_welcome->setString("You've lost");
		m_game = false;
	}
}

void Game::render(sf::RenderTarget & target)
{
	m_welcome->render(target);
	m_guessWord.render(target);

	for (auto& b : m_buttons)
		b.second.render(target);


	if (m_reloadButton)
		m_reloadButton->render(target);
}

Game::~Game()
{
	Application::disableBackgroundImage();
}

void Game::getWords()
{
	std::ifstream f("words.txt");

	std::string temp;
	while (std::getline(f, temp))
	{
		if (temp.find('#') == std::string::npos)
			m_words.push_back(temp);
	}

}

void Game::loadRandomWord()
{
	auto index = sen::Random::get<int>(0, m_words.size() + 1);

	m_guessWord.reset(m_words[index]);
}

void Game::resetGame()
{
	loadRandomWord();
	m_letters.clear();
	m_shouldPopReloadButton = true;
	m_welcome->setString("");
	for (auto&x : m_buttons)
	{
		x.second.setActive(true);
	}
	m_game = true;
	m_lives = 11;
}

