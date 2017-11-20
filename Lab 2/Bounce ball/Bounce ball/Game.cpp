// author Aoife Powders


#include "Game.h"
#include <iostream>



Game::Game() :
	m_window{ sf::VideoMode{ 800, 800, 32 }, "SFML Game" },
	m_exitGame{false} //when true game will exit
{
	setupFontAndText(); // load font 
	setUpPlane();
	setUpCircle();
	Ux = U * std::cos(angle);
	Uy = U * std::sin(angle);
	velocity = { Ux, Uy };
	gravity *= pixelsToMetres;
	ogVelocity = velocity;
	position = ogPosition;
	velocity = ogVelocity;
	angleDegrees = angle * (180 / 3.14);
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
			bounce = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			position = ogPosition;
			velocity = ogVelocity;
			velocity = { Ux, Uy };
			velocityText.setString("Velocity:" + std::to_string(U));
			angleText.setString("Angle:" + std::to_string(angleDegrees)+ "Degrees");
			move = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
		{
			U++;
			Ux = U * cos(angle);
			Uy = U * sin(angle);
			velocityText.setString("Velocity:" + std::to_string(U));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
		{
			U--;
			Ux = U * cos(angle);
			Uy = U * sin(angle);
			velocityText.setString("Velocity:" + std::to_string(U));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))
		{
			angle-=0.1;
			angleDegrees = angle * (180 / 3.14);
			Ux = U * cos(angle);
			Uy = U * sin(angle);
			angleText.setString("Angle:" + std::to_string(angleDegrees) + "Degrees");
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
		{
			angle+=0.1;
			angleDegrees = angle * (180 / 3.14);
			Ux = U * cos(angle);
			Uy = U * sin(angle);
			angleText.setString("Angle:" + std::to_string(angleDegrees) + "Degrees");
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
	m_window.draw(velocityText);
	m_window.draw(angleText);
	m_window.draw(distanceX);
	m_window.display();
}

void Game::setupFontAndText()
{
	if (!m_font.loadFromFile("ASSETS//FONTS//Halloween.ttf"))
	{
		std::cout << "Font not loaded" << std::endl;
	}

	text.setFont(m_font);
	text.setString("Height: " + std::to_string(heighest) + " Meters");
	text.setCharacterSize(20);
	text.setPosition(100, 100);
	text.setFillColor(sf::Color::White);

	timeTaken.setFont(m_font);
	timeTaken.setString("Time: " + std::to_string(actualTimer) + " Seconds");
	timeTaken.setCharacterSize(20);
	timeTaken.setPosition(100, 150);
	timeTaken.setFillColor(sf::Color::White);

	distanceX.setFont(m_font);
	distanceX.setString("Distance X:" + std::to_string(Furthest) + " Meters");
	distanceX.setCharacterSize(20);
	distanceX.setPosition(100, 200);
	distanceX.setFillColor(sf::Color::White);

	velocityText.setFont(m_font); 
	velocityText.setString("Velocity:" + std::to_string(U));
	velocityText.setCharacterSize(20);
	velocityText.setPosition(400, 100);
	velocityText.setFillColor(sf::Color::White);  

	angleText.setFont(m_font);
	angleText.setString("Angle:" + std::to_string(angle) + " Degrees");
	angleText.setCharacterSize(20);
	angleText.setPosition(400, 200);
	angleText.setFillColor(sf::Color::White);

}

void Game::gravityfunc()
{
	if (move == true)
	{
		
		position.x = position.x + velocity.x * timeChange + (0.5 * gravity.x * (timeChange * timeChange));
		position.y = position.y + velocity.y * timeChange + (0.5 * gravity.y * (timeChange * timeChange));

		velocity.y = velocity.y + gravity.y * timeChange;
		velocity.x = velocity.x + gravity.x * timeChange;

		// out put the time it takes to get off the ground and back on it
		timer++;
		if (timer == 60)
		{
			timer = 0;
			actualTimer++;
		}

		timeTaken.setString("Time: " + std::to_string(actualTimer) + "." + std::to_string(timer));
		text.setString("HEIGHT: " + std::to_string(heighest) + " Meters");
		distanceX.setString("Distance X:" + std::to_string(Furthest) + " Meters");
	}
	//stops the pixel when it hits the plane
	if (position.y > planePos.y)
	{
		move = false;

		velocity.y = -.9 * velocity.y;
		
		
		if (bounce)
		{
			position.y -= 1;
			bounce = false;
			move = true;
		}
		else
		{
			bounce = false;
		}
	}

	//gets what the highest position is.
	if (planePos.y - position.y > heighest)
	{
		heighest = planePos.y - position.y;
	}

	if (position.x  - planePos.x  > Furthest)
	{
		Furthest = planePos.x - position.x;
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
	shape.setRadius(5);
}


