// author AoifePowders
#ifndef GAME
#define GAME

#include <SFML/Graphics.hpp>
#include "Vector3D.h"
#include "Matrix3D.h"

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();
	void applyGravity(const float t_mass, Vector3D &t_currentAcceleration, Vector3D t_externalForce);

private:

	void processEvents();
	void update(sf::Time t_deltaTime);
	void render();
	void setUp();
	void checkRotate();

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	bool m_exitGame; // control exiting game

	sf::RectangleShape m_spaceship;
	sf::RectangleShape m_plane;
	sf::Vector2f m_position{ 50, 400 };
	int m_lives = 0;
	int m_score = 0;

	sf::RectangleShape m_target;
	sf::Vector2f m_targetPosition{ 500,100 };

	sf::CircleShape m_bullet;
	sf::Vector2f m_bulletPosition{ 0,0 };
	bool m_bulletAlive = false;

	Vector3D m_velocity{ 10,100, 0};
	const sf::Vector2f gravity{ 0,9.8 * 20 };
	float m_mass = 0.1;
	Vector3D m_acceleration{ 0,0, 0 };
	Vector3D m_thrust{ 0,0,0 };
	Vector3D m_originalHeading{ 0,-50, 0 };
	Vector3D m_headingVector{ m_originalHeading };

	Vector3D m_adjustment{ 1.f, 0, 0 };
	float angle = 0;
	Matrix3D m_rotationThing;
};

#endif // !GAME

