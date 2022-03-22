#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Particle
{
public:
	sf::CircleShape Cir;
	sf::Vector2f Vel;
	float Radius;
	Particle(float x, float y);
	Particle(float x, float y, sf::Vector2f vel);
	void Draw(sf::RenderWindow *win);
	void Update();
	bool operator==(const Particle& p1) const;

};