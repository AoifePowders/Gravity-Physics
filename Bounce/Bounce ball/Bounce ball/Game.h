// author Peter Lowe
#ifndef GAME
#define GAME

#include <SFML/Graphics.hpp>
#include <cmath>

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

	void gravityfunc();
	void setUpPlane();
	void setUpCircle();
	void setupFontAndText();

	sf::CircleShape shape{ 0.5f };
	sf::RectangleShape m_plane;

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_font; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen
	sf::Text text;
	sf::Text timeTaken;
	sf::Text estTime;
	sf::Text estHeight;

	bool m_exitGame; // control exiting game
	bool move = false;

	float angle = 45;
	float angleDegrees = angle * 3.14 / 180;
	float Ux;
	float Uy;
	float U = 50;

	sf::Vector2f size{ 800, 100 };
	sf::Vector2f ogVelocity{ 90, -190.27 };
	sf::Vector2f velocity;
	sf::Vector2f ogPosition{ 100, 699 };
	sf::Vector2f position{ 0, 0 };
	sf::Vector2f planePos{ 1, 700 };
	sf::Vector2f gravity{ 0.0f, 9.8f };

	float heighest = 0;
	int timer = 0;
	int actualTimer = 0;
	float timeChange;
	bool bounce = false;
	float pixelsToMetres = 10;

};

#endif // !GAME

