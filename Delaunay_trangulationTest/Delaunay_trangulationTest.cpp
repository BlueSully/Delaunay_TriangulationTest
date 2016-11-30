// Delaunay_trangulationTest.cpp : Defines the entry point for the console application.
//
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
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 

#include <iostream>
#include "Delaunay_Triangle.h"

int main()
{
	srand(time(NULL));
	// Create the main window 
	sf::RenderWindow window(sf::VideoMode(800, 600, 32), "SFML First Program");
	std::vector<sf::Vector2f> m_pointList;

	for (size_t i = 0; i < 6; i++)
	{
		sf::Vector2f tempPoint(rand() % window.getSize().x, rand() % window.getSize().y);
		m_pointList.push_back(tempPoint);
	}
	Delaunay_Triangle graph(m_pointList);
	// Start game loop 
	while (window.isOpen())
	{
		// Process events 
		sf::Event Event;
		while (window.pollEvent(Event))
		{
			// Close window : exit 
			if (Event.type == sf::Event::Closed)
				window.close();

			// Escape key : exit 
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
				window.close();
		}
		window.clear();
		graph.draw(window);
		window.display();
	} 

	return EXIT_SUCCESS;
}