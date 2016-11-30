#pragma once
#include "SFML/Graphics.hpp" 
#include "NodeEdge.h"
#include "Node.h"

class Delaunay_Triangle {
private:
	std::vector<Node> m_nodeList;
	std::vector<NodeEdge> m_nodeEdgeList;
public:
	Delaunay_Triangle();
	Delaunay_Triangle(std::vector<sf::Vector2f> & pointslist);
	bool LineSegementsIntersect(NodeEdge l1, NodeEdge l2);
	void draw(sf::RenderWindow & window);
};