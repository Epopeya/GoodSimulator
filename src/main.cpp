
#include <SFML/Graphics.hpp>
#include <cstdio>
#include <set>
#include <vector>
#include <chrono>

#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/Mouse.hpp"
#include "map.h"
#include "robot_code.h" // bad, but we need original code


sf::Vector2i windowSize = sf::Vector2i(1200, 600);

int main()
{
	sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "My window");
	sf::View mapView(sf::FloatRect(0, -3000, 3000, 3000));
	mapView.setViewport(sf::FloatRect(0, 0, 0.5f, 1));

	sf::View debugView(sf::FloatRect(0, 0, 3000, 3000));
	debugView.setViewport(sf::FloatRect(0.5f, 0, 0.5f, 1));
	mapView.zoom(1.3);

	setup();
	// SFML stuff
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case (sf::Keyboard::Key::P): {
				}
				}
			}
		}
		window.clear(sf::Color::Black);
		// main loop

		window.setView(mapView);
		renderMap(&window);
		loop();
		robot.updateMovement();
		robot.render(&window);

		window.setView(debugView);

		// end loop
		window.display();
		window.setFramerateLimit(60);
	}

	return 0;
}
