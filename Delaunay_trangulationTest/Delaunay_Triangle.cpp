#include "Delaunay_Triangle.h"

Delaunay_Triangle::Delaunay_Triangle()
{

}

Delaunay_Triangle::Delaunay_Triangle(std::vector<sf::Vector2f> & pointslist)
{
	//Setup Nodes
	for (size_t i = 0; i < pointslist.size(); i++)
	{
		Node tempNode = Node(pointslist[i]);
		tempNode.setColour(sf::Color::White);
		m_nodeList.push_back(tempNode);
	}

	//Setup Edges
	for (size_t i = 0; i < pointslist.size(); i++)
	{
		for (size_t j = i + 1; j < pointslist.size(); j++)
		{
			NodeEdge tempEdge = NodeEdge(pointslist[i], pointslist[j]);
			m_nodeEdgeList.push_back(tempEdge);
		}
	}
}

void Delaunay_Triangle::draw(sf::RenderWindow & window)
{
	for (size_t i = 0; i < m_nodeList.size(); i++)
	{
		m_nodeList[i].draw(window);
	}

	for (size_t i = 0; i < m_nodeEdgeList.size(); i++)
	{
		m_nodeEdgeList[i].draw(window);
	}
}
