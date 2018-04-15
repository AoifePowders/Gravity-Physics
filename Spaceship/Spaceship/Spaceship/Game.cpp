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
void Game::applyGravity(const float t_mass, sf::Vector2f &t_currentAcceleration, sf::Vector2f t_externalForce)
{
	t_currentAcceleration = sf::Vector2f(gravity.x * t_mass, gravity.y * t_mass) + t_externalForce;
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		m_thrust = m_headingVector;
	}
	else
	{
		m_thrust = sf::Vector2f(0, 0);
	}

	//if (m_position.y > 500)
	//{
	//	m_thrust = sf::Vector2f(0, 0);
	//	m_velocity.y = 0;
	//}

	m_position = (m_spaceship.getPosition() + m_velocity * t_deltaTime.asSeconds() + 0.5f * m_acceleration * (t_deltaTime.asSeconds() * t_deltaTime.asSeconds()));
	applyGravity(m_mass, m_acceleration, m_thrust);
	m_velocity = m_velocity + (m_acceleration * t_deltaTime.asSeconds());
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
	m_window.draw(m_target);
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

	m_target.setFillColor(sf::Color::Red);
	m_target.setPosition(m_targetPosition);
	m_target.setSize(sf::Vector2f{ 50,50 });
}
