#pragma once

#include "States/State.h"
#include "GUI/Button.h"
#include "Managers/ButtonController.h"

enum Language{ ENGLISH = 0, POLISH};

class Languages: public sen::State
{
	sen::Text m_text;
	sen::ButtonController m_bc;
public:
	Languages();
	virtual void update(float deltaTime, sf::RenderWindow& window) override;
	virtual void render(sf::RenderTarget& target) override;
	virtual void input(sf::RenderWindow& window) override;
};