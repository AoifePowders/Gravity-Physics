// author Peter Lowe

#include "Game.h"
#include <iostream>



Game::Game() :
	m_window{ sf::VideoMode{ 800, 600, 32 }, "SFML Game" },
	m_exitGame{false} //when true game will exit
{
	setup(); 

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
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			m_timeChange = timeSinceLastUpdate.asSeconds();
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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			m_jump = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			m_moveLeft = true;
		}
		else
		{
			m_moveLeft = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			m_moveRight = true;
		}
		else
		{
			m_moveRight = false;
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
	jump();
}

/// <summary>
/// draw the frame and then switch bufers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
	m_window.draw(m_player);
	m_window.draw(m_plane);
	m_window.display();
}

void Game::jump()
{
	if (m_jump == true)
	{
		(m_position.x, m_position.y) = (m_position.x, m_position.y) + (m_velocity.x, m_velocity.y) * m_timeChange + 0.5 * m_acceleration * (m_timeChange * m_timeChange);
		m_velocity = m_velocity + sf::Vector2f(0, m_acceleration) * m_timeChange;
		m_player.setPosition(m_position);
	}

	if (m_moveLeft == true)
	{
		m_position = m_position - m_moveVelocity;
		m_player.setPosition(m_position);
	}

	if (m_moveRight == true)
	{
		m_position = m_position + m_moveVelocity;
		m_player.setPosition(m_position);
	}

	if (m_position.y > (m_plane.getPosition().y - 50))
	{
		m_jump = false;
	}
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setup()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}

	m_player.setFillColor(sf::Color::Black);
	m_player.setPosition(m_position);
	m_player.setSize(sf::Vector2f{ 25,50 });


	m_plane.setFillColor(sf::Color::Green);
	m_plane.setPosition(1, 500);
	m_plane.setSize(sf::Vector2f{ 800,100 });
}

