#pragma once

#include "States/State.h"

#include "GUI/Text.h"
#include "GuessWord.h"
#include "Util/Animation.h"

class Game : public sen::State
{
	GuessWord m_guessWord;
	
	std::shared_ptr<sf::Texture> m_background;
	std::shared_ptr<sf::Texture> m_texture;
	std::unique_ptr<sen::Text> m_resultText;
	std::unique_ptr<sen::Text> m_livesText;
	std::unique_ptr<sen::Button> m_reloadButton;
	std::unique_ptr<sen::Animation> m_animation;
	std::vector<std::string> m_words;
	std::vector<char> m_letters;
	std::unordered_map<char, sen::Button> m_buttons;
	
	bool m_shouldPopReloadButton = false;
	bool m_game = true;
	unsigned int m_lives = 11;

	sf::Sprite m_sprite;
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