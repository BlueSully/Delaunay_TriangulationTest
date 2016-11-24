#pragma once
#include "SFML/Graphics.hpp" 
#include "Node.h"
class NodeEdge
{
private:
	Node pointA;
	Node pointB;

public:
	NodeEdge();//Default Constructor
	NodeEdge(Node point1, Node point2);//Overloaded Constructor

	void draw(sf::RenderWindow & window);
};