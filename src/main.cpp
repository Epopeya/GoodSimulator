#include <SFML/Graphics.hpp>
#include <cstdio>

#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "render.h"
#include "robot_code.h" // bad, but we need original code

bool paused = false;

void eventHandler()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed) window->close();
		if (event.type == sf::Event::KeyPressed)
		{
			switch (event.key.code)
			{
			case (sf::Keyboard::Key::P): {
			}
				paused = !paused;
			}
		}
	}
}

int main()
{
	window = new sf::RenderWindow(sf::VideoMode(600, 600), "Simulation");

	sf::View mapView(sf::FloatRect(0, -3000, 3000, 3000));
	mapView.zoom(1.3);
	window->setView(mapView);

	// robot_code.h setup
	setup();

	while (window->isOpen())
	{
		eventHandler();

		if (paused) { continue; }
		window->clear(sf::Color::Black);

		// logic
		loop();
		robot.update();

		// rendering
		robot.render();

		window->display();
		window->setFramerateLimit(60); // TODO: remove timers from robot_code, make millis and micros fixed
	}
	return 0;
}
