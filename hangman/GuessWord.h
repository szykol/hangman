#pragma once

#include <vector>

#include "GUI/Button.h"

class GuessWord
{
	std::vector<sen::Text> m_letters;
	std::string m_word = "SLOWO";
public:
	GuessWord();
	void render(sf::RenderTarget& target);
	void checkInput(char input);
};