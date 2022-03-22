
#include "Canvas.h"
#include <thread>

using namespace std;

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "Brounov Movement", sf::Style::Titlebar | sf::Style::Close);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(144);

	Canvas mainCanvas = Canvas();
	mainCanvas.CreateParticle(200, 300, sf::Vector2f(1.0f, 0.5f));
	mainCanvas.CreateParticle(200, 200, sf::Vector2f(1.0f, 0.7f));

	sf::VertexArray line(sf::Lines, 2);
	line[0].color = sf::Color::White;
	line[1].color = sf::Color::Red;


	bool firstClick = true;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Button::Left)
			{
				if (firstClick)
				{
					firstClick = !firstClick;
					mainCanvas.CreateParticle((float)event.mouseButton.x, (float)event.mouseButton.y, { 0.0f, 0.0f });
					float x = (float)event.mouseButton.x;
					float y = (float)event.mouseButton.y;
					line[0].position = sf::Vector2f(x, y);
				}
			}
			if (event.type == sf::Event::MouseMoved)
			{
				if (!firstClick)
				{
					float x = (float)event.mouseMove.x;
					float y = (float)event.mouseMove.y;
					line[1].position = sf::Vector2f(x, y);
				}
			}
			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Button::Left)
			{
				firstClick = !firstClick;
				float vx = event.mouseButton.x - mainCanvas.Particles.back().Cir.getPosition().x;
				float vy = event.mouseButton.y - mainCanvas.Particles.back().Cir.getPosition().y;
				mainCanvas.Particles.back().Vel = { vx / 60, vy / 60 };
				line[0].position = sf::Vector2f(0, 0);
				line[1].position = sf::Vector2f(0, 0);
			}
		}
		window.clear(sf::Color::Black);

		mainCanvas.Update(&window);
		if (line[0].position != sf::Vector2f(0, 0) && line[1].position != sf::Vector2f(0, 0))
		{
			window.draw(line);
		}
		mainCanvas.Draw(&window);

		window.display();
	}


	return 0;
}
