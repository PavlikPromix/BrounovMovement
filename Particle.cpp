#include "Particle.h"



Particle::Particle(float x, float y) {
	Radius = 5.0f;
	Cir = sf::CircleShape(Radius);
	Cir.setOrigin({ Radius, Radius });
	Cir.setPosition(x, y);
	Cir.setFillColor(sf::Color::White);
	Vel = {1.0f, 1.0f};
}

Particle::Particle(float x, float y, sf::Vector2f vel) {
	Radius = 5.0f;
	Cir = sf::CircleShape(Radius);
	Cir.setOrigin({ Radius, Radius });
	Cir.setPosition(x, y);
	Cir.setFillColor(sf::Color::White);
	Vel = vel;
}

void Particle::Draw(sf::RenderWindow* win) {
	win->draw(Particle::Cir);
}

void Particle::Update()
{
	Cir.move(Vel);
	//Vel *= 0.9999f;
}

bool Particle::operator==(const Particle& p1) const {
	if (p1.Vel == Vel && p1.Cir.getPosition().x == Cir.getPosition().x && p1.Cir.getPosition().y == Cir.getPosition().y)
		return true;
	return false;
}
