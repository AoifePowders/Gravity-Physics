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
	void collision();

	sf::CircleShape shape{ 0.5f };
	sf::CircleShape target{ 1.0f };
	sf::RectangleShape m_plane;

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_font; // font used by message
	sf::Text velocityText;
	sf::Text angleText;
	sf::Text airResText;
	sf::Text attemptText;

	bool m_exitGame; // control exiting game
	bool move = false;


	float angle = -.785398;
	float angleDegrees;
	float Ux{ 0 };
	float Uy{ 0 };
	float U = 100;

	sf::Vector2f size{ 800, 100 };
	sf::Vector2f ogVelocity{};
	sf::Vector2f velocity;
	sf::Vector2f ogPosition{ 100, 698 };
	sf::Vector2f position{ 100, 698 };
	sf::Vector2f planePos{ 1, 700 };
	sf::Vector2f gravity{ 0.0f, 9.8f };

	float mass = 100;
	sf::Vector2f accel;
	float grav = 9.8;
	float Ca = 1.29;
	float ma = 0;

	float heighest = 0;
	int timer = 0;
	int actualTimer = 0;
	float timeChange;
	float pixelsToMetres = 5;
	float weight{ 1000 };

	int attempt = 0;

};

#endif // !GAME

