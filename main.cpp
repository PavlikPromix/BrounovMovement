
#include "Canvas.h"
#include <thread>
#include <ctime>

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
	line[1].color = sf::Color::Blue;

	srand(time(0));

	bool firstClick = true;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Button::Left)
				{
					if (firstClick)
					{
						firstClick = !firstClick;
						float x = (float)event.mouseButton.x;
						float y = (float)event.mouseButton.y;
						mainCanvas.CreateParticle(x, y, { 0.0f, 0.0f });
						line[0].position = sf::Vector2f(x, y);
					}
				}
				else if (event.mouseButton.button == sf::Mouse::Button::Right)
				{
					mainCanvas.CreateParticle((float)event.mouseButton.x, (float)event.mouseButton.y, { (float)rand() / RAND_MAX, (float)rand() / RAND_MAX });
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
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
			{
				mainCanvas.Particles.clear();
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
