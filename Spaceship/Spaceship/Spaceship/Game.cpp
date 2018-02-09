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
		m_timeChange = timeSinceLastUpdate.asSeconds();
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_position.y == 500)
	{
		m_velocity.y -= 200;
		m_position.y -= 1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (m_velocity.x > -100)
		{
			m_velocity.x -= 10.0;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (m_velocity.x < 100)
		{
			m_velocity.x += 10.0;
		}
	}

	if (m_position.y < m_plane.getPosition().y)
	{
		m_acceleration = m_gravity;
	}

	else
	{
		m_position.y = m_plane.getPosition().y;
		m_velocity.y = 0;

		float veloLen = sqrt(m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y);
		if (veloLen != 0)
		{
			float unitX = m_velocity.x / veloLen;
			sf::Vector2f unitVelo(unitX, 0.0);
			m_acceleration.x = -1.0f * m_gravity.y * unitVelo.x * 0.8;
			m_acceleration.y = 0;
		}
		else
		{
			m_acceleration = sf::Vector2f(0, 0);
		}
	}
	
	m_position = m_position + m_velocity * m_timeChange + 0.5f * m_acceleration * (m_timeChange * m_timeChange);
	m_velocity = m_velocity + m_acceleration * m_timeChange;
	m_spaceship.setPosition(m_position);
}

/// <summary>
/// draw the frame and then switch bufers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
	m_window.draw(m_plane);
	m_window.draw(m_spaceship);
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
	m_spaceship.setOrigin(0, m_spaceship.getGlobalBounds().height);


	m_plane.setFillColor(sf::Color::Green);
	m_plane.setPosition(0, 500);
	m_plane.setSize(sf::Vector2f{ 800,100 });
}
