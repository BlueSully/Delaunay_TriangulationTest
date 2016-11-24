#pragma once

#include "SFML/Graphics.hpp" 

class Node
{
private:
	sf::CircleShape body;

public:
	Node();
	Node(float xPosition, float yPosition);
	Node(sf::Vector2f position);
	~Node();

	void setColour(sf::Color);
	sf::Vector2f getNodeCentre() const;
	void draw(sf::RenderWindow & window);
};

