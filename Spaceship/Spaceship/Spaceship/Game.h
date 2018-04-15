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
	void applyGravity(const float t_mass, sf::Vector2f &t_currentAcceleration, sf::Vector2f t_externalForce);

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
	sf::Vector2f m_position{ 50, 400 };

	sf::RectangleShape m_target;
	sf::Vector2f m_targetPosition{ 500,100 };

	sf::Vector2f m_velocity{ 10,100 };
	const sf::Vector2f gravity{ 0,0.5 };
	float m_mass = 0;
	sf::Vector2f m_acceleration{ 0,0 };
	sf::Vector2f m_thrust{ 0,0 };
	sf::Vector2f m_originalHeading{ 0,-50 };
	sf::Vector2f m_headingVector{ m_originalHeading };	
};

#endif // !GAME

