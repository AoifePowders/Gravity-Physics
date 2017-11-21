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
	/// main method for game
	void run();

private:

	void processEvents();
	void update(sf::Time t_deltaTime);
	void render();

	void gravityfunc();
	void setUpPlane();
	void setUpCircle();
	void setupFontAndText();
	void airResistance();

	sf::CircleShape shape{ 0.5f };
	sf::CircleShape target{ 1.0f };
	sf::RectangleShape m_plane;

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_font; // font used by message
	sf::Text velocityText;
	sf::Text angleText;

	bool m_exitGame; // control exiting game
	bool move = false;

	float angle = -0.785398;
	float angleDegrees;
	float Ux{ 0 };
	float Uy{ 0 };
	float U = 100;

	sf::Vector2f size{ 800, 100 };
	sf::Vector2f ogVelocity{ 90, -190.27 };
	sf::Vector2f velocity;
	sf::Vector2f ogPosition{ 100, 698 };
	sf::Vector2f position{ 100, 698 };
	sf::Vector2f planePos{ 1, 700 };
	sf::Vector2f gravity{ 0.0f, 9.8f };

	float mass = 0.1;
	sf::Vector2f accel;
	float grav = 9.8;
	float Ca = 0.001;
	float incTime;
	float ma = 0;

	float heighest = 0;
	int timer = 0;
	int actualTimer = 0;
	float timeChange;
	float pixelsToMetres = 10;

};

#endif // !GAME

