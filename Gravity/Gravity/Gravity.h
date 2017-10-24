#pragma once
#include <SFML/Graphics.hpp>
#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#include <iostream>

//shapes
sf::CircleShape shape(0.5f);
sf::RectangleShape plane;
//functions
void setUpPlane();
void setUpCircle();
void setUpText();
//vectors
sf::Vector2f size(800, 100);
sf::Vector2f velocity(0, -44.27);
sf::Vector2f position(400, 699);
sf::Vector2f planePos(1, 700);
sf::Vector2f gravity(0.0f, 9.8f);
float acceleration = 9.8f;
bool move = false;
float heighest = 0;
//font and texts
sf::Font font;
sf::Text text;
sf::Text timeTaken;
sf::Text estTime;
sf::Text estHeight;
int timer = 0;
int actualTimer = 0;

