#include "GuessWord.h"

GuessWord::GuessWord()
{
	m_letters.reserve(m_word.size());

	sf::Vector2f pos(200.f, 300.f);
	for (auto znak : m_word)
	{
		auto temp = std::string{};
		//temp += znak;
		temp += "_";
		auto letter = sen::Text{ temp, 66U };
		letter.setPosition(pos);
		m_letters.push_back(std::move(letter));
		pos.x += 60.f;
	}
}

void GuessWord::render(sf::RenderTarget & target)
{
	for (auto& letter : m_letters)
	{
		letter.render(target);
	}
}

void GuessWord::checkInput(char input)
{
	for (int i = 0; i < m_word.size(); ++i)
	{
		if (m_word[i] == input)
		{
			m_letters[i].setString(input);
		}

	}
}
