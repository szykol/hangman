#pragma once

#include "States/State.h"
#include "GUI/Button.h"
#include "Managers/ButtonController.h"

enum Level {EASY = 0, MEDIUM = 1, HARD = 2};

class Menu : public sen::State
{
	sen::Text m_text;
	sen::Text m_difficulty;
	sen::ButtonController m_bc;
public:
	Menu();
	virtual void update(float deltaTime, sf::RenderWindow& window) override;
	virtual void render(sf::RenderTarget& target) override;
	virtual void input(sf::RenderWindow& window) override;
};