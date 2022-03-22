#include "Canvas.h"

sf::Vector2f Normalize(const sf::Vector2f& vec) {
	float l = sqrt((vec.x * vec.x) + (vec.y * vec.y));
	if (l != 0)
		return { vec.x / l, vec.y / l };
	return vec;
}
float Dot(const sf::Vector2f& vec1, const sf::Vector2f& vec2) {
	return vec1.x * vec2.x + vec1.y * vec2.y;
}

Canvas::Canvas()
{
	Particles = {};
}

void Canvas::CreateParticle(float x, float y, sf::Vector2f vel)
{
	Particles.push_back(Particle(x, y, vel));
}

void Canvas::Draw(sf::RenderWindow* win)
{
	for (auto p : Particles) {
		p.Draw(win);
	}
}

void Canvas::Update(sf::RenderWindow* win)
{
	for (auto& p : Particles) {
		p.Update();
	}
	OnCollideCheck(win);
}

void Canvas::OnCollideCheck(sf::RenderWindow* win)
{
	for (auto &p1 : Particles)
	{
		if (p1.Cir.getPosition().x < p1.Radius)
		{
			p1.Cir.setPosition({ p1.Radius, p1.Cir.getPosition().y });
			p1.Vel.x = -p1.Vel.x;
		}
		if (p1.Cir.getPosition().x > win->getSize().x - p1.Radius)
		{
			p1.Cir.setPosition({ win->getSize().x - p1.Radius, p1.Cir.getPosition().y });
			p1.Vel.x = -p1.Vel.x;
		}
		if (p1.Cir.getPosition().y < p1.Radius)
		{
			p1.Cir.setPosition({ p1.Cir.getPosition().x, p1.Radius });
			p1.Vel.y = -p1.Vel.y;
		}
		if (p1.Cir.getPosition().y > win->getSize().y - p1.Radius)
		{
			p1.Cir.setPosition({ p1.Cir.getPosition().x, win->getSize().y - p1.Radius });
			p1.Vel.y = -p1.Vel.y;
		}
		for (auto &p2 : Particles)
		{
			if (p1 == p2)
			{
				continue;
			}
			float dx = p2.Cir.getPosition().x - p1.Cir.getPosition().x;
			float dy = p2.Cir.getPosition().y - p1.Cir.getPosition().y;
			float dist = sqrt((dx * dx) + (dy * dy));
			if (dist < p1.Radius + p2.Radius)
			{
				sf::Vector2f normal{ (p2.Cir.getPosition().x - p1.Cir.getPosition().x) / dist, (p2.Cir.getPosition().y - p1.Cir.getPosition().y) / dist };
				sf::Vector2f tangent{ -normal.y, normal.x };
				
				float dpT1 = Dot(p1.Vel, Normalize(tangent));
				float dpT2 = Dot(p2.Vel, Normalize(tangent));

				float dpN1 = Dot(Normalize(p1.Vel), Normalize(tangent));
				float dpN2 = Dot(Normalize(p2.Vel), Normalize(tangent));

				float m1 = (dpN1 * (p1.Radius - p2.Radius) + 2.0f * p2.Radius * dpN2) / (p1.Radius + p2.Radius);
				float m2 = (dpN2 * (p2.Radius - p1.Radius) + 2.0f * p1.Radius * dpN1) / (p1.Radius + p2.Radius);
				
				sf::Vector2f newVel1 = { tangent.x * dpT1 + normal.x * m1, tangent.y * dpT1 + normal.y * m1 };
				sf::Vector2f newVel2 = { tangent.x * dpT2 - normal.x * m2, tangent.y * dpT2 - normal.y * m2 };

				p1.Vel = newVel1;
				p2.Vel = newVel2;
			}

		}
	}
}
