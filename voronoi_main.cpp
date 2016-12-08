/*
* The author of this software is Shane O'Sullivan.  
* Permission to use, copy, modify, and distribute this software for any
* purpose without fee is hereby granted, provided that this entire notice
* is included in all copies of any software which is or includes a copy
* or modification of this software and in all copies of the supporting
* documentation for such software.
* THIS SOFTWARE IS BEING PROVIDED "AS IS", WITHOUT ANY EXPRESS OR IMPLIED
* WARRANTY.  IN PARTICULAR, NEITHER THE AUTHORS NOR AT&T MAKE ANY
* REPRESENTATION OR WARRANTY OF ANY KIND CONCERNING THE MERCHANTABILITY
* OF THIS SOFTWARE OR ITS FITNESS FOR ANY PARTICULAR PURPOSE.
*/


/* 
* Modified by Dr. Oisin Cawley Institute of Technology Carlow - 2015
* Integrated the Veronoi algorithm in a graphic implementation using SFML.
* User can click on the screnn to add a new node to the space.
* Algorithm then called to recalulate the Veronoi diagram.
* Also retrieves and displays the corresponding Delaunay Triangulations. 
*/

//////////////////////////////////////////////////////////// 
// Headers 
//////////////////////////////////////////////////////////// 
#include <iostream>
#include "stdafx.h" 
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

#include <stdio.h>
#include <search.h>
#include <malloc.h>
#include "VoronoiDiagramGenerator.h"

using namespace std;


int main(int argc, char **argv)
{
	// Window creation
	sf::RenderWindow app(sf::VideoMode(1000, 768, 32), "Veronoi");
	sf::Event event;
	bool m_mouseClick = false;
	//Array to hold the Veronoi edges
	sf::Vertex line[] =
	{
		sf::Vertex(sf::Vector2f(25, 10), sf::Color(100, 250, 50)),
		sf::Vertex(sf::Vector2f(400, 100), sf::Color(100, 250, 50))
	};
	int lastx = 0, lasty = 0; // Need to remember the last mouse position clicked due to SFML glitch

	// Clearing screen
	/*app.clear(sf::Color(0, 0, 0, 0));*/

	const long count = 400; // Our array will have max 400 nodes.
							// There will be a Lousy overflow error if you click more than that!
	int currentCount = 4;	// Lets get things started with just two nodes

	/*for (size_t i = 0; i < currentCount; i++)
	{
		xValues[i] = (rand() % 970) + 20;
	}*/
	float xValues[count] = { 220, 170, 500, 220, 100, 900, 111, 123, 231, 432, 500, 500 };
	float yValues[count] = { 90, 301, 131, 500, 100, 900, 100, 200, 300, 400, 500, 400 };
	//	float xValues[count] = { 400, 600 };
	//	float yValues[count] = { 400, 500 };

	sf::CircleShape circle;	// I use the cirlce class to draw the nodes.
	circle.setRadius(2);
	circle.setOutlineColor(sf::Color::Red);
	circle.setOutlineThickness(1);
	for (int i = 0; i < currentCount; i++)
	{
		circle.setPosition(xValues[i], yValues[i]);
		app.draw(circle);
	}

	VoronoiDiagramGenerator vdg;
	vdg.setGenerateDelaunay(true);
	vdg.generateVoronoi(xValues, yValues, currentCount, 0, 1000, 0, 1000, 3); // X-cords, ycoords, number of coords, mixX, maxX, minY, maxY, minDistance between points
	vdg.resetIterator();

	float x1, y1, x2, y2;

	while (true)
	{
		while (app.pollEvent(event))
		{
			// Window closed
			if (event.type == sf::Event::Closed)
			{
				return EXIT_SUCCESS;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
			{
				if (vdg.isRenderingDelaunayTri()) 
				{
					vdg.setGenerateDelaunay(false);
				}
				else if (!vdg.isRenderingDelaunayTri())
				{
					vdg.setGenerateDelaunay(true);
				}
			}
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !m_mouseClick)//Check to See if mouse was clicked
			{
				m_mouseClick = true;//set mouse to be clicked
				int xpos = sf::Mouse::getPosition(app).x;
				int ypos = sf::Mouse::getPosition(app).y;

				if (xpos > 0 && xpos < app.getDefaultView().getSize().x &&
					ypos > 0 && ypos < app.getDefaultView().getSize().y)//Check to See if mouse click is within the screen
				{
					// Clearing screen				
					currentCount++;
					xValues[currentCount - 1] = xpos;
					yValues[currentCount - 1] = ypos;
					lastx = xpos;
					lasty = ypos;

					//reGenerate new voronoi with new data
					vdg.generateVoronoi(xValues, yValues, currentCount, 0, 1000, 0, 1000, 3, true);							
				}
			}
			else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_mouseClick)//if mouse was released and mouseclick was pressed
			{
				m_mouseClick = false;
			}
		}

		app.clear(sf::Color(0, 50, 100));
		vdg.resetIterator();
		//printf("\n-------------------------------\n");

		// Also getds and displays the Delaunay Triangulations
		vdg.resetDelaunayEdgesIterator();
		for (int i = 0; i < currentCount; i++)//Draw the nodes
		{
			circle.setPosition(xValues[i], yValues[i]);
			app.draw(circle);
		}

		while (vdg.getNext(x1, y1, x2, y2))// Generate voronoi Lines
		{
			//printf("GOT Line (%f,%f)->(%f,%f)\n",x1,y1,x2, y2);
			line[0] = sf::Vertex(sf::Vector2f(x1, y1), sf::Color(100, 250, 50));
			line[1] = sf::Vertex(sf::Vector2f(x2, y2), sf::Color(100, 250, 50));
			app.draw(line, 2, sf::Lines);
		}

		while (vdg.getNextDelaunay(x1, y1, x2, y2))
		{
			//					printf("GOT Line (%f,%f)->(%f,%f)\n", x1, y1, x2, y2);
			line[0] = sf::Vertex(sf::Vector2f(x1, y1));
			line[1] = sf::Vertex(sf::Vector2f(x2, y2));
			app.draw(line, 2, sf::Lines);
		}
		app.display();
	}
}
