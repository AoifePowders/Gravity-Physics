// author Peter Lowe
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

	sf::Vector2f m_velocity{ 0, -44.25 };
	sf::Vector2f m_moveVelocity{ 5,0 };
	float m_acceleration = 9.8f;
	float m_timeChange;
	sf::Vector2f m_position{ 50,450 };

};

#endif // !GAME

