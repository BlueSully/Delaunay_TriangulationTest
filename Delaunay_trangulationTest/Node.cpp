#include "Node.h"

Node::Node()
{
}

Node::Node(float xPosition, float yPosition)
{
	body.setPosition(xPosition, yPosition);
	body.setRadius(5);
}

Node::Node(sf::Vector2f position)
{
	body.setPosition(position.x, position.y);
	body.setRadius(5);
}

Node::~Node()
{

}

sf::Vector2f Node::getNodeCentre() const
{
	return sf::Vector2f((body.getPosition().x + body.getRadius()), (body.getPosition().y + body.getRadius()));
}

void Node::setColour(sf::Color colourVal)
{
	body.setFillColor(colourVal);
}

void Node::draw(sf::RenderWindow & window)
{
	window.draw(body);
}
