// author Apoi
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
	void jump();
	
	void setup();

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen
	bool m_exitGame; // control exiting game

	sf::RectangleShape m_player;
	sf::RectangleShape m_plane;

	bool m_jump;
	bool m_moveLeft;
	bool m_moveRight;

	sf::Vector2f m_velocity{ 10, -44.25 };
	float m_pixelToMeter = 20.0;
	float m_acceleration = 9.8f * 20.0;
	float m_coeffFriction = 0.8;
	float m_mass = 10;
	sf::Vector2f m_unitVelocity;
	sf::Vector2f m_frictionAcceleration;
	float m_timeChange;
	sf::Vector2f m_position{ 50,450 };

};

#endif // !GAME

