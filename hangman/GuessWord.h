#pragma once

#include <vector>

#include "GUI/Button.h"

class GuessWord
{
	//std::vector<sen::Text> m_letters;
	std::unique_ptr<sen::Text> m_displayWord;
	std::string m_word;
public:
	GuessWord();
	void render(sf::RenderTarget& target);
	bool checkInput(char input);
	bool correct() const;
	void reset(const std::string& newWord);

};