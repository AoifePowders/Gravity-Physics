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
void Game::applyGravity(const float t_mass, Vector3D &t_currentAcceleration, Vector3D t_externalForce)
{
	t_currentAcceleration = Vector3D(gravity.x * t_mass, gravity.y * t_mass, 0) + t_externalForce;
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
		m_thrust = m_headingVector;
	}
	else
	{
		m_thrust = Vector3D(0, 0, 0);
	}

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	//{
	//	m_headingVector -= m_adjustment;
	//	m_velocity -= m_adjustment;
	//	thor::setLength(m_headingVector, 70.f);
	//	checkRotate();
	//}
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	//{
	//	m_headingVector += m_adjustment;
	//	m_velocity += m_adjustment;
	//	thor::setLength(m_headingVector, 70.f);
	//	checkRotate();
	//}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		angle += 5;
		m_spaceship.setRotation(angle);
		m_rotationThing = Matrix3D::rotationX(angle);
		m_velocity = m_rotationThing.operator*(m_velocity);
		//m_headingVector = m_rotationThing.operator*(m_headingVector);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		angle -= 5;
		m_spaceship.setRotation(angle);
		m_rotationThing = Matrix3D::rotationX(angle);
		m_velocity = m_rotationThing.operator*(m_velocity);
		//m_headingVector = m_rotationThing.operator*(m_headingVector);
	}

	m_position.x = (m_spaceship.getPosition().x + m_velocity.X() * t_deltaTime.asSeconds() + 0.5f * m_acceleration.X() * (t_deltaTime.asSeconds() * t_deltaTime.asSeconds()));
	m_position.y = (m_spaceship.getPosition().y + m_velocity.Y() * t_deltaTime.asSeconds() + 0.5f * m_acceleration.Y() * (t_deltaTime.asSeconds() * t_deltaTime.asSeconds()));
	applyGravity(m_mass, m_acceleration, m_thrust);
	m_velocity = m_velocity + (m_acceleration * t_deltaTime.asSeconds());
	m_spaceship.setPosition(m_position);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
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
	}
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
	if (m_bulletAlive == true)
	{
		m_window.draw(m_bullet);
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

}

void Game::checkRotate()
{
	float angle;
	if (m_headingVector.X() < 0)
	{
		angle = 360 + atan(m_headingVector.Y() / m_headingVector.X());
	}

	if (m_headingVector.Y() > 0)
	{
		angle = atan(m_headingVector.Y() / m_headingVector.X());
	}

	if (m_headingVector.Y() == 0)
	{

		if (m_headingVector.X() < m_originalHeading.X())
		{
			angle = 180;
		}
		else if (m_headingVector.X() > m_originalHeading.X())
		{
			angle = 0;
		}
	}

	angle += 90;
	m_spaceship.setRotation(angle);
	//m_adjustment = thor::rotatedVector(m_headingVector, 90.0f);
	//thor::setLength(m_adjustment, m_adjustmentMax);
}
