//author AoifePowders
#ifndef GAME
#define GAME

#include <SFML/Graphics.hpp>
#include <time.h>

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
	sf::Vector2f m_position{ 100,100 };

	int m_lives = 3;
	int m_score = 0;
	bool m_gameOver = false;
	sf::Text m_livesText;
	sf::Text m_scoreText;

	sf::RectangleShape m_target;
	sf::Vector2f m_targetPosition{ 500,100 };

	sf::CircleShape m_bullet;
	sf::Vector2f m_bulletPosition{ 0,0 };
	bool m_bulletAlive = false;

	sf::Vector2f m_velocity{ 10,100 };
	const sf::Vector2f gravity{ 0,9.8 * 20 };
	float m_mass = 0.1;
	sf::Vector2f m_acceleration{ 0,0 };
	sf::Vector2f m_thrust{ 0,0 };
	sf::Vector2f m_headingVector{ 0,-50 };

	float angle = 0;

	float DEG_TO_RAD = 3.14 / 180;
};

#endif // !GAME

