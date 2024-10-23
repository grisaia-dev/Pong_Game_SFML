#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/ContextSettings.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <Entity.h>
#include <sstream>
#include <map>
#include <memory>

class Game {
	std::shared_ptr<sf::RenderWindow> m_Window;
	std::shared_ptr<sf::ContextSettings> m_Settings;
	std::shared_ptr<sf::Font> m_Font;
	std::shared_ptr<std::map<std::string, std::shared_ptr<sf::Text>>> m_Texts;
	std::shared_ptr<std::map<std::string, std::shared_ptr<Entity>>> m_Entities;
	std::shared_ptr<sf::Event> m_Event;
	std::shared_ptr<sf::Clock> m_Clock;
	std::shared_ptr<sf::Time> m_Time;

	// PTR Player and Ball
	std::shared_ptr<Entity> m_Player;
	std::shared_ptr<Entity> m_Ball;

	// Game variables
	int m_Lives;
	int m_Score;
	bool pause;

	// Systems
	void SRender();
	void SInput();
	void SText();
	void SMovement();

public:
	Game();
	void init();
	void run();

};