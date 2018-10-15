#pragma once

#include "States/State.h"

#include "GUI/Text.h"
#include "GuessWord.h"

class Game : public sen::State
{
	std::unique_ptr<sen::Text> m_resultText;
	std::shared_ptr<sf::Texture> m_background;
	GuessWord m_guessWord;
	//std::vector<sen::Button> m_buttons;
	std::vector<std::string> m_words;
	std::vector<char> m_letters;
	std::unordered_map<char, sen::Button> m_buttons;
	std::unique_ptr<sen::Button> m_reloadButton;
	bool m_shouldPopReloadButton = false;
	unsigned int m_lives = 11;
	std::unique_ptr<sen::Text> m_livesText;
	bool m_game = true;
public:
	virtual void update(float deltaTime, sf::RenderWindow& window) override;
	virtual void render(sf::RenderTarget& target) override;
	//virtual void input(sf::RenderWindow& window) override;
	virtual void handleEvents(sf::Event& evnt) override;
	
	Game();
	~Game();
	
	void checkResult();
	void spawnReloadButton();
	void getWords();
	void loadRandomWord();
	void resetGame();
	void checkLetter(char letter);
	void placeButtons(char begin, char end, float yCoord);
	/*Game(Game&&) = default;
	Game& operator=(Game&&) = default;*/
};