#include"Gravity.h"
#include <cmath>


int main()

{
	sf::RenderWindow window(sf::VideoMode(800, 800), "Go Physics!!");
	if (!font.loadFromFile("Fonts//Halloween.ttf"))
		{
			std::cout << "Font not loaded" << std::endl;
		}
	
	setUpText();
	setUpCircle();
	setUpPlane();
	setUpText();
	sf::Clock clock;
	const float FPS = 60.0f;
	const sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	clock.restart();
	while (window.isOpen())
	{
		//read keyboard inout
		sf::Event event;
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			move = true;
		}
		//function sets up the time and height text
		
	
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		//get the time since last update and restart the clock
		timeSinceLastUpdate += clock.restart();
		
		//update every 60th of a second
		if (timeSinceLastUpdate > timePerFrame)
		{
			window.clear();
			// update position and velocity here using equations in lab sheet using timeChange as timeSinceLastUpdate.asSeconds().
			float timeChange = timeSinceLastUpdate.asSeconds();
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
			

			//update shape on screen
			shape.setPosition(position);
			window.draw(plane);
			window.draw(shape);
			window.draw(text);
			window.draw(timeTaken);
			window.draw(estHeight);
			window.draw(estTime);
			window.display();
			timeSinceLastUpdate = sf::Time::Zero;
		}
	}
	return 0;
}

//function to set up the plane
void setUpPlane()
{
	plane.setFillColor(sf::Color::Green);
	plane.setPosition(planePos);
	plane.setSize(size);
}

//function to set up the pixel
void setUpCircle()
{
	shape.setFillColor(sf::Color::White);
	shape.setPosition(position);
}

//function to set up the text
void setUpText()
{

	text.setFont(font);
	text.setString("HEIGHT: " + std::to_string(heighest));
	text.setCharacterSize(20);
	text.setPosition(100, 100);
	text.setColor(sf::Color::White);

	timeTaken.setFont(font);
	timeTaken.setString("Time: " + std::to_string(actualTimer));
	timeTaken.setCharacterSize(20);
	timeTaken.setPosition(100, 150);
	timeTaken.setColor(sf::Color::White);

	estTime.setFont(font);
	estTime.setString("Estimated Time: 9  seconds");
	estTime.setCharacterSize(20);
	estTime.setPosition(500, 150);
	estTime.setColor(sf::Color::White);

	estHeight.setFont(font);
	estHeight.setString("Estimated Height: 100 pixels");
	estHeight.setCharacterSize(20);
	estHeight.setPosition(500, 100);
	estHeight.setColor(sf::Color::White);
}

