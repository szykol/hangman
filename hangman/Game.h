#pragma once

#include "States/State.h"

#include "GUI/Text.h"
#include "GuessWord.h"

class Game : public sen::State
{
	std::unique_ptr<sen::Text> m_welcome;
	std::shared_ptr<sf::Texture> m_background;
	GuessWord m_guessWord;
	std::vector<sen::Button> m_buttons;
public:
	virtual void update(float deltaTime, sf::RenderWindow& window) override;
	virtual void render(sf::RenderTarget& target) override;
	virtual void input(sf::RenderWindow& window) override;
	Game();
	~Game();
	/*Game(Game&&) = default;
	Game& operator=(Game&&) = default;*/
};