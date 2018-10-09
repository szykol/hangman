#pragma once

#include "States/State.h"
#include "GUI/Button.h"

class Menu : public sen::State
{
	//std::unique_ptr<sen::Text> m_welcome;
	std::unique_ptr<sen::Button> m_into;
public:
	Menu();
	virtual void update(float deltaTime, sf::RenderWindow& window) override;
	virtual void render(sf::RenderTarget& target) override;
	virtual void input(sf::RenderWindow& window) override;
};