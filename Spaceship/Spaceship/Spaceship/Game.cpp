// author AoifePowders

#include "Game.h"
#include <iostream>

Game::Game() :
	m_window{ sf::VideoMode{ 800, 600, 32 }, "SFML Game" },
	m_exitGame{false} //when true game will exit
{
	setUp();
}


Game::~Game()
{
}


void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible#
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}

/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if ( sf::Event::Closed == event.type) // window message
		{
			m_window.close();
		}
		if (sf::Event::KeyPressed == event.type) //user key press
		{
			if (sf::Keyboard::Escape == event.key.code)
			{
				m_exitGame = true;
			}
		}
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		m_velocity = m_headingVector;
	}
	else
	{
		m_velocity = sf::Vector2f{ 0, 0 };
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		angle += 0.5;
		m_spaceship.setRotation(angle);
		sf::Vector2f tempVector = {sin(angle * DEG_TO_RAD), cos(angle * DEG_TO_RAD) };

		if (angle < 180)
		{
			m_velocity.x += tempVector.x;
		}

		if (angle > 180)
		{
			m_velocity.y += tempVector.y;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		angle -= 0.5;
		m_spaceship.setRotation(angle);
		sf::Vector2f tempVector = { sin(angle * DEG_TO_RAD), cos(angle * DEG_TO_RAD) };
		m_velocity.x += tempVector.x;
	}

	m_position = (m_spaceship.getPosition() + m_velocity * t_deltaTime.asSeconds() + 0.5f * m_acceleration * (t_deltaTime.asSeconds() * t_deltaTime.asSeconds()));
	m_acceleration = sf::Vector2f((gravity * m_mass, gravity * m_mass) + m_thrust);
	m_velocity = m_velocity + (m_acceleration * t_deltaTime.asSeconds());
	m_spaceship.setPosition(m_position);









	if (m_bulletAlive == false && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		m_bulletAlive = true;
		m_bulletPosition.x = m_position.x;
		m_bulletPosition.y = m_position.y - 25;
		m_bullet.setPosition(m_bulletPosition);
	}

	if (m_bulletAlive == true)
	{
		m_bulletPosition.x += 5;
		m_bullet.setPosition(m_bulletPosition);
	}

	if (m_bullet.getGlobalBounds().intersects(m_target.getGlobalBounds()))
	{
		m_bulletAlive = false;
		m_score += 1;
		m_scoreText.setString("Score: " + std::to_string(m_score));
		m_targetPosition.x = rand() % 700 + 100;
		m_targetPosition.y = rand() % 400 + 100;
		m_target.setPosition(m_targetPosition);
	}

	if (m_bulletPosition.x >= 800)
	{
		m_bulletAlive = false;
		m_bullet.setPosition(m_position);
	}

	if (m_bulletAlive == false)
	{
		m_bullet.setPosition(m_position);
	}
	
	if (m_spaceship.getGlobalBounds().intersects(m_plane.getGlobalBounds()))
	{
		m_spaceship.setPosition(100, 100);
		m_lives -= 1;
		m_livesText.setString("Lives: " + std::to_string(m_lives));
	}

	if (m_spaceship.getGlobalBounds().intersects(m_target.getGlobalBounds()))
	{
		srand(time(nullptr));
		m_spaceship.setPosition(100, 100);
		m_lives -= 1;
		m_livesText.setString("Lives: " + std::to_string(m_lives));
		m_targetPosition.x = rand() % 700 + 100;
		m_targetPosition.y = rand() % 500 + 100;
		m_target.setPosition(m_targetPosition);
	}

	if (m_lives == 0)
	{
		m_gameOver = true;
	}

	if (m_gameOver == true && sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		m_gameOver = false;
		m_score = 0;
		m_lives = 3;
		m_velocity = { 10, 100 };
		m_targetPosition = { 500, 100 };
		m_position = { 100,100 };
	}
}

/// <summary>
/// draw the frame and then switch bufers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
	m_window.draw(m_scoreText);
	m_window.draw(m_livesText);
	m_window.draw(m_plane);
	m_window.draw(m_spaceship);
	m_window.draw(m_target);
	if (m_bulletAlive == true)
	{
		m_window.draw(m_bullet);
	}
	if (m_gameOver == true)
	{
		m_window.clear(sf::Color::Black);
	}
	m_window.display();
}

void Game::setUp()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}

	m_spaceship.setFillColor(sf::Color::Black);
	m_spaceship.setPosition(m_position);
	m_spaceship.setSize(sf::Vector2f{ 25,50 });
	m_spaceship.setOrigin(m_spaceship.getGlobalBounds().width * 0.5, m_spaceship.getGlobalBounds().height * 0.5);

	m_plane.setFillColor(sf::Color::Green);
	m_plane.setPosition(0, 500);
	m_plane.setSize(sf::Vector2f{ 800,100 });

	m_target.setFillColor(sf::Color::Red);
	m_target.setPosition(m_targetPosition);
	m_target.setSize(sf::Vector2f{ 50,50 });

	m_bullet.setFillColor(sf::Color::Blue);
	m_bullet.setPosition(m_bulletPosition);
	m_bullet.setRadius(10);

	m_livesText.setCharacterSize(20);
	m_livesText.setFillColor(sf::Color::Black);
	m_livesText.setFont(m_ArialBlackfont);
	m_livesText.setPosition(100, 50);
	m_livesText.setString("Lives: " + std::to_string(m_lives));

	m_scoreText.setCharacterSize(20);
	m_scoreText.setFillColor(sf::Color::Black);
	m_scoreText.setFont(m_ArialBlackfont);
	m_scoreText.setPosition(500, 50);
	m_scoreText.setString("Score: " + std::to_string(m_score));

}
