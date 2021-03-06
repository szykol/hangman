#include "GuessWord.h"

#include <cstring>

GuessWord::GuessWord()
{

}

void GuessWord::render(sf::RenderTarget & target)
{
	if(m_displayWord)
		m_displayWord->render(target);
}

bool GuessWord::checkInput(char input)
{
	if (!m_displayWord) return false;

	input = tolower(input);
	auto word = m_displayWord->getString().toAnsiString();
	bool result = false;
	for (int i = 0; i < m_word.size(); ++i)
	{
		if (tolower(m_word[i]) == input)
		{
			word[i] = m_word[i];
			//m_guessed[i] = input;
			result = true;
		}

	}
	m_displayWord->setString(word);
	return result;
}

bool GuessWord::correct() const
{
	if (!m_displayWord) return false;
	else return !m_revealed && m_displayWord->getString() == m_word;
}

void GuessWord::reset(const std::string & newWord)
{
	m_word = newWord;
	m_revealed = false;

	std::string temp = "";
	for (char z : m_word)
	{
		temp += '_';
	}

	if (!m_displayWord)
	{
		m_displayWord = std::make_unique<sen::Text>(temp);
		m_displayWord->setUpdateOnlyXAxis(true);
	}
	else
		m_displayWord->setString(temp);

	m_displayWord->setCharacterSize(66U);
	m_displayWord->setLetterSpacing(2.5f);
	m_displayWord->setPosition(Application::getInitialWindowSize().x / 2.f,
							Application::getInitialWindowSize().y / 2.f - 30.f);
}

void GuessWord::reveal()
{
	m_revealed = true;
	m_displayWord->setString(m_word);
}
