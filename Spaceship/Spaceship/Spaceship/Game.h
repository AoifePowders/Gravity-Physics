// author AoifePowders
#ifndef GAME
#define GAME

#include <SFML/Graphics.hpp>

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void update(sf::Time t_deltaTime);
	void render();
	void setUp();

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	bool m_exitGame; // control exiting game

	sf::RectangleShape m_spaceship;
	sf::RectangleShape m_plane;
	sf::Vector2f m_position{ 50, 500 };

	sf::Vector2f m_velocity{ 10,100 };
	float m_pixelToMeter = 20.0;
	sf::Vector2f m_gravity{ 0,9.8 * m_pixelToMeter };
	sf::Vector2f m_acceleration{ 0,9.8 * m_pixelToMeter };
	float m_timeChange;
	
};

#endif // !GAME

