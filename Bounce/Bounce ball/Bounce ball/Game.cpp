// author Peter Lowe

#include "Game.h"
#include <iostream>



Game::Game() :
	m_window{ sf::VideoMode{ 800, 800, 32 }, "SFML Game" },
	m_exitGame{false} //when true game will exit
{
	setupFontAndText(); // load font 
	setUpPlane();
	setUpCircle();
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
			timeChange = timeSinceLastUpdate.asSeconds();
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}

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
			move = true;
		}
	}
}

void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	gravityfunc();
	shape.setPosition(position);
}

void Game::render()
{
	m_window.clear(sf::Color::Black);
	m_window.draw(m_plane);
	m_window.draw(shape);
	m_window.draw(text);
	m_window.draw(timeTaken);
	m_window.draw(estHeight);
	m_window.draw(estTime);
	m_window.display();
}

void Game::setupFontAndText()
{
	if (!m_font.loadFromFile("ASSETS//FONTS//Halloween.ttf"))
	{
		std::cout << "Font not loaded" << std::endl;
	}

	text.setFont(m_font);
	text.setString("HEIGHT: " + std::to_string(heighest));
	text.setCharacterSize(20);
	text.setPosition(100, 100);
	text.setFillColor(sf::Color::White);

	timeTaken.setFont(m_font);
	timeTaken.setString("Time: " + std::to_string(actualTimer));
	timeTaken.setCharacterSize(20);
	timeTaken.setPosition(100, 150);
	timeTaken.setFillColor(sf::Color::White);

	estTime.setFont(m_font);
	estTime.setString("Estimated Time: 9  seconds");
	estTime.setCharacterSize(20);
	estTime.setPosition(500, 150);
	estTime.setFillColor(sf::Color::White);

	estHeight.setFont(m_font);
	estHeight.setString("Estimated Height: 100 pixels");
	estHeight.setCharacterSize(20);
	estHeight.setPosition(500, 100);
	estHeight.setFillColor(sf::Color::White);

}

void Game::gravityfunc()
{
	if (move == true)
	{
		(position.x, position.y) = (position.x, position.y) + (velocity.x, velocity.y) * timeChange + 0.5 * acceleration * (timeChange * timeChange);
		velocity = velocity + sf::Vector2f(0, acceleration) * timeChange;

		// out put the time it takes to get off the ground and back on it
		timer++;
		if (timer == 60)
		{
			timer = 0;
			actualTimer++;
		}

		timeTaken.setString("Time: " + std::to_string(actualTimer) + "." + std::to_string(timer));
		text.setString("HEIGHT: " + std::to_string(heighest));
		std::cout << actualTimer << std::endl;

	}
	//stops the pixel when it hits the plane
	if (position.y > (planePos.y - 1))
	{
		move = false;
	}

	//gets what the highest position is.
	if (planePos.y - position.y > heighest)
	{
		heighest = planePos.y - position.y;
	}
}

void Game::setUpPlane()
{
	m_plane.setFillColor(sf::Color::Green);
	m_plane.setPosition(planePos);
	m_plane.setSize(size);
}

void Game::setUpCircle()
{
	shape.setFillColor(sf::Color::White);
	shape.setPosition(position);
}


