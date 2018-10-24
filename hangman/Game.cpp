#include "Game.h"

#include "Application.h"
#include "Managers/CacheSystem.h"
#include "GuessWord.h"
#include "Util/Random.h"
#include "Menu.h"

#include <fstream>

void Game::handleEvents(sf::Event & evnt)
{
	if (!m_game || evnt.type != sf::Event::TextEntered) return;
	
	char z = toupper((char)evnt.text.unicode);

	if (z >= 'A' && z <= 'Z' && std::find(m_letters.begin(), m_letters.end(), z) == m_letters.end())
	{
		checkLetter(z);
	}
}

Game::Game(int level)
{
	if (level == Level::EASY)
		m_bounds = std::make_pair(3, 5);
	else if (level == Level::MEDIUM)
		m_bounds = std::make_pair(6, 10);
	else if (level == Level::HARD)
		m_bounds = std::make_pair(11, 14);

	sf::Vector2f center = (sf::Vector2f)Application::getInitialWindowSize() / 2.f;
	m_resultText = std::make_unique<sen::Text>("");
	m_resultText->setPosition(center);
	m_resultText->move(sf::Vector2f(0.f, 40.f));
	m_resultText->setCharacterSize(40U);

	m_background = sen::CacheSystem::get<sf::Texture>("res/Images/bg.jpeg");
	Application::setBackgroundImage(*m_background);
	
	getWords();
	loadRandomWord();

	//auto pos = sf::Vector2f{ 50.f, 500.f };
	for (char z = 'A'; z <= 'Z'; ++z)
	{
		auto button = sen::Button{ z };

		//button.setPosition(pos);
		button.setSize(sf::Vector2f(45.f, 45.f));
		//pos.x += 70.f;


		button.addListener(sen::ButtonEvent::CLICK, [this](sen::Button& b) {
			char z = b.getTextObject().getString().toAnsiString()[0];
			checkLetter(z);
		});

		m_buttons.insert(std::pair<char, sen::Button>(z, std::move(button) ));
	}

	float pos = Application::getInitialWindowSize().y - 300.f;
	placeButtons('a', 'g', pos);
	placeButtons('h', 'r', pos+70);
	placeButtons('s', 'z', pos+140);
	//placeButtons('p', 'z');

	m_livesText = std::make_unique<sen::Text>("Lives:\n  " + std::to_string(m_lives));
	m_livesText->setPosition(sf::Vector2f(Application::getInitialWindowSize().x - 100.f, 100.f));
	m_livesText->setCharacterSize(40U);

	m_texture = sen::CacheSystem::get<sf::Texture>("res/Images/hangman.png");
	m_animation = std::make_unique<sen::Animation>(*m_texture, sf::Vector2u(12, 1), 0.5);
	m_sprite.setTexture(*m_texture);
	m_sprite.setTextureRect(m_animation->getTextureRect());
	//m_sprite.setPosition(Application::getInitialWindowSize().x - 350.f, 50.f);
	m_sprite.scale(sf::Vector2f(2.f, 2.f));

	auto bounds = m_sprite.getLocalBounds();
	m_sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	m_sprite.setPosition(Application::getInitialWindowSize().x / 2.f, Application::getInitialWindowSize().y - 200.f);
	
	spawnReloadButton();
}

void Game::update(float deltaTime, sf::RenderWindow & window)
{
	if (m_reloadButton)
		m_reloadButton->update(deltaTime);

	if (m_game) 
	{
		for (auto& b : m_buttons)
			b.second.update(deltaTime);

		checkResult();
	}
}

void Game::render(sf::RenderTarget & target)
{
	if(!m_game)
		m_resultText->render(target);

	target.draw(m_sprite);

	m_guessWord.render(target);
	//m_livesText->render(target);

	for (auto& b : m_buttons)
		b.second.render(target);

	if (m_reloadButton)
		m_reloadButton->render(target);
}

void Game::checkResult()
{
	if (m_lives == 0)
	{
		m_resultText->setString("You've lost");
		m_resultText->setFillColor(sf::Color::Red);
		m_guessWord.reveal();
		m_game = false;
	}

	if (m_guessWord.correct())
	{
		m_resultText->setString("You've won");
		m_resultText->setFillColor(sf::Color::Green);
		m_game = false;
	}
}

void Game::spawnReloadButton()
{
	if (!m_reloadButton)
	{
		m_reloadButton = std::make_unique<sen::Button>("Reload");
		sf::Vector2f tempPos(Application::getInitialWindowSize().x / 2.f,
			Application::getInitialWindowSize().y);

		tempPos.y -= 100.f;

		m_reloadButton->setPosition(tempPos);
		m_reloadButton->setOnClickCallback([this] {
			resetGame();
		});
	}
}

void Game::getWords()
{
	std::ifstream f("words.txt");

	std::string temp;
	while (std::getline(f, temp))
	{
		if (temp.find('#') == std::string::npos && withinBounds(temp.length()))
			m_words.push_back(temp);
	}
}

void Game::loadRandomWord()
{
	auto index = sen::Random::get<int>(0, m_words.size());

	m_guessWord.reset(m_words[index]);
}

void Game::resetGame()
{
	loadRandomWord();
	m_letters.clear();
	m_shouldPopReloadButton = true;
	for (auto&x : m_buttons)
	{
		x.second.setActive(true);
	}
	m_game = true;
	m_lives = 11;
	m_livesText->setString("Lives:\n  "+std::to_string(m_lives));
	m_animation->reset();
	m_sprite.setTextureRect(m_animation->getTextureRect());
	auto bounds = m_sprite.getLocalBounds();
	m_sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	m_sprite.setPosition(Application::getInitialWindowSize().x / 2.f, Application::getInitialWindowSize().y - 200.f);

}

void Game::checkLetter(char z)
{
	if (m_guessWord.checkInput(z))
	{
		auto button = m_buttons.find(z);
		if (button != m_buttons.end())
		{
			button->second.setOutlineColor(sf::Color::Green);
			button->second.setActive(false);
			m_letters.push_back(z);
		}
	}
	else
	{
		auto button = m_buttons.find(z);
		if (button != m_buttons.end())
		{
			button->second.setOutlineColor(sf::Color::Red);
			button->second.getTextObject().setFillColor(sf::Color::Red);
			button->second.setActive(false);
			m_letters.push_back(z);
		}
		m_lives--;
		m_animation->nextFrame();
		m_sprite.setTextureRect(m_animation->getTextureRect());

		auto bounds = m_sprite.getLocalBounds();
		m_sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
		m_sprite.setPosition(Application::getInitialWindowSize().x / 2.f, Application::getInitialWindowSize().y / 2.f - 200.f);
		
		m_livesText->setString("Lives:\n  " + std::to_string(m_lives));
	}
}

void Game::placeButtons(char begin, char end, float yCoord)
{
	if (m_buttons.empty() || end <= begin)	return;

	begin = toupper(begin);
	end = toupper(end);

	auto startingPos =
		sf::Vector2f{ Application::getInitialWindowSize().x / 2.f, yCoord };


	// tells how many buttons are above the center position
	// aswell as specifies the middle index of buttons vector
	int temp = (end-begin) / 2;

	// how much to move from the center y coord to the point where should be
	// center of the first button
	float offset = 0.f;

	//sf::Vector2f biggestSize = getBiggestSizeOfButton();
	float buttonSize = 45.f;

	float gap = 30.f;
	
	if ((end-begin) % 2 != 0)
		offset = (temp+1 - 0.5f) * (buttonSize + gap);
	else
		offset = temp * (buttonSize + gap);


	startingPos.x -= offset;

	/*auto endIt = m_buttons.find(end);
	if (end == 'Z')
		endIt = m_buttons.end();*/
	for (char z = begin; z <= end; ++z)
	{
		auto it = m_buttons.find(z);
		it->second.setPosition(startingPos);
		startingPos.x += buttonSize + gap;
	}

}

bool Game::withinBounds(int len)
{
	return (len >= m_bounds.first && len <= m_bounds.second);
}

