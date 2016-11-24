#include "NodeEdge.h"

NodeEdge::NodeEdge()
{

}

NodeEdge::NodeEdge(Node point1, Node point2)
{
	pointA = point1;
	pointB = point2;
}

void NodeEdge::draw(sf::RenderWindow & window)
{
	sf::VertexArray lines(sf::Lines, 2);
	lines[0].position = pointA.getNodeCentre();
	lines[1].position = pointB.getNodeCentre();

	window.draw(lines);

}