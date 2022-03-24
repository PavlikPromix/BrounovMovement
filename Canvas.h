#pragma once
#include "Particle.h"
#include <vector>
#include <cmath>



class Canvas
{
public:
	std::vector<Particle> Particles;
	Canvas();
	void CreateParticle(float x, float y, sf::Vector2f vel);
	void Draw(sf::RenderWindow* win);
	void Update(sf::RenderWindow* win);
	void OnCollideCheck(sf::RenderWindow* win);
};