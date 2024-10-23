#include <Game.h>

Game::Game() : m_Settings(std::make_shared<sf::ContextSettings>()), m_Window(std::make_shared<sf::RenderWindow>())
	, m_Font(std::make_shared<sf::Font>()), m_Texts(std::make_shared<std::map<std::string, std::shared_ptr<sf::Text>>>())
	, m_Event(std::make_shared<sf::Event>()), m_Entities(std::make_shared<std::map<std::string, std::shared_ptr<Entity>>>()){
	init(); 
}

void Game::init() {
	m_Settings->antialiasingLevel = 4;
	m_Window->create(sf::VideoMode(1280, 720), "Pong", sf::Style::Default, *m_Settings);

	//FONT
	m_Font->loadFromFile("Fonts/DS-DIGIT.TTF");

	//TEXT
	m_Texts->insert(std::pair<std::string, std::shared_ptr<sf::Text>>("GameVariables", std::make_shared<sf::Text>()));
	m_Texts->insert(std::pair<std::string, std::shared_ptr<sf::Text>>("DebugString", std::make_shared<sf::Text>()));
	for(auto& [key, text] : *m_Texts) {
		if(key == "GameVariables") {
			text->setFont(*m_Font);
			text->setCharacterSize(32);
			text->setFillColor(sf::Color::White);
			text->setPosition(5, 10);
		}
		if(key == "DebugString") {
			text->setFont(*m_Font);
			text->setCharacterSize(20);
			text->setFillColor(sf::Color::White);
			text->setPosition(5, m_Window->getSize().y - text->getCharacterSize() - 10);
			text->setString("DEBUG VERSION");
		}
	}

	// Game Variables
	m_Lives = 3;
	m_Score = 0;
	pause = false;

	// Player and Ball
	m_Entities->insert(std::pair<std::string, std::shared_ptr<Entity>>("Player", std::make_shared<Entity>()));
	m_Entities->insert(std::pair<std::string, std::shared_ptr<Entity>>("Ball", std::make_shared<Entity>()));
	for(auto& [key, entity] : *m_Entities) {
		if(key == "Player") {
			entity->cTransform = std::make_shared<CTransform>(sf::Vector2f(m_Window->getSize().x / 2.f, m_Window->getSize().y - 20.f), sf::Vector2f(300.f, 300.f));
			entity->cRecShape = std::make_shared<CRecShape>(sf::Vector2f(100.f, 5.f));
			entity->cInput = std::make_shared<CInput>();
			entity->cRecShape->rectangle.setPosition(entity->cTransform->position.x, entity->cTransform->position.y);
			m_Player = entity;
		}
		if(key == "Ball") {
			entity->cTransform = std::make_shared<CTransform>(sf::Vector2f(m_Window->getSize().x / 2.f, 20.f), sf::Vector2f(300.f, 300.f));
			entity->cCirShape = std::make_shared<CCirShape>(8.f, 10);
			entity->cCirShape->circle.setPosition(entity->cTransform->position.x, entity->cTransform->position.y);
			m_Ball = entity;
		}
	}

	// Time
	m_Clock = std::make_shared<sf::Clock>();
}

void Game::run() {
	while(m_Window->isOpen()) {
		SInput();
		if (!pause) {
			SText();
			SMovement();
		}
		SRender();
	}
}

void Game::SRender() {
	m_Window->clear();

	// Entity render
	for(auto& [key, entity] : *m_Entities) {
		if(key == "Player") {
			entity->cRecShape->rectangle.setPosition(entity->cTransform->position);
			m_Window->draw(entity->cRecShape->rectangle);
		}
		if(key == "Ball") {
			entity->cCirShape->circle.setPosition(entity->cTransform->position);
			m_Window->draw(entity->cCirShape->circle);
		}
	}
	
	// Text render
	for(auto& [key, text] : *m_Texts) {
		m_Window->draw(*text);
	}

	m_Window->display();
}

void Game::SInput() {
	while(m_Window->pollEvent(*m_Event)) {
		if(m_Event->type == sf::Event::Closed)
			m_Window->close();

		if(m_Event->type == sf::Event::KeyPressed) {
			switch(m_Event->key.code) {
				case sf::Keyboard::Right:
					m_Player->cInput->right = true;
					break;
				case sf::Keyboard::Left:
					m_Player->cInput->left = true;
					break;
				case sf::Keyboard::Escape:
					pause = !pause;
					break;
				default:
					break;
			}
		}

		if(m_Event->type == sf::Event::KeyReleased) {
			switch(m_Event->key.code) {
				case sf::Keyboard::Right:
					m_Player->cInput->right = false;
					break;
				case sf::Keyboard::Left:
					m_Player->cInput->left = false;
					break;
				default:
					break;
			}
		}
		
	}
}

void Game::SText() {
	std::ostringstream ss;
	ss << "Lives: " << m_Lives << "\nScore: " << m_Score;
	m_Texts->find("GameVariables")->second->setString(ss.str());
}

void Game::SMovement() {
	m_Time = std::make_shared<sf::Time>(m_Clock->restart());
	if(m_Player->cInput->right)
		m_Player->cTransform->position.x += m_Player->cTransform->velocity.x * m_Time->asSeconds();
	if(m_Player->cInput->left)
		m_Player->cTransform->position.x -= m_Player->cTransform->velocity.x * m_Time->asSeconds();
}
