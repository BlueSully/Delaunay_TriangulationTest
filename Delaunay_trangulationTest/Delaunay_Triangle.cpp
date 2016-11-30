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

			if (sqrt(((pointslist[j].x - pointslist[i].x) * (pointslist[j].x - pointslist[i].x)) +
				((pointslist[j].y - pointslist[i].y) * (pointslist[j].y - pointslist[i].y))) < 6)
			{
				
			}
			else 
			{
				NodeEdge tempEdge = NodeEdge(pointslist[i], pointslist[j]);
				m_nodeEdgeList.push_back(tempEdge);
			}
		}
	}
}

bool Delaunay_Triangle::LineSegementsIntersect(NodeEdge l1, NodeEdge l2)
{
	sf::Vector2f intersection;

	sf::Vector2f p = sf::Vector2f(l1.getPoints()[0].getNodeCentre().x, l1.getPoints()[0].getNodeCentre().y);
	sf::Vector2f p2 = sf::Vector2f(l1.getPoints()[1].getNodeCentre().x, l1.getPoints()[1].getNodeCentre().y);

	sf::Vector2f q = sf::Vector2f(l2.getPoints()[0].getNodeCentre().x, l2.getPoints()[0].getNodeCentre().y);
	sf::Vector2f q2 = sf::Vector2f(l2.getPoints()[1].getNodeCentre().x, l2.getPoints()[1].getNodeCentre().y);

	sf::Vector2f e1 = p2 - p;
	sf::Vector2f e2 = q2 - q;
	//sf::Vector2f U x V = Ux*Vy - Uy*Vx // cross product
	float e1_Cross_e2 = ((e1.x * e2.y) - (e1.y * e2.x));

	sf::Vector2f pq = q - p;
	float pq_Cross_e1 = ((pq.x * e1.y) - (pq.y * e1.x));

	if (e1_Cross_e2 == 0 && pq_Cross_e1 == 0) //if true then the two lines are collinear. meaning they belong along the same line
	{
		/*if (0 <= (pq.x * e1.x))
		{

		}*/
		//if ((0 <= (q - p)*r && (q - p)*r <= r*r) || (0 <= (p - q)*s && (p - q)*s <= s*s))
			// return true;
		//else
			// return false;
	}
	else if (e1_Cross_e2 == 0 && pq_Cross_e1 != 0) //if true then the two lines are parralel.
	{
		return false;
	}

	return false;
}

//public static bool LineSegementsIntersect(Vector p, Vector p2, Vector q, Vector q2,
//	out Vector intersection, bool considerCollinearOverlapAsIntersect = false)
//{
//	intersection = new Vector();
//
//	var r = p2 - p;
//	var s = q2 - q;
//	var rxs = r.Cross(s);
//	var qpxr = (q - p).Cross(r);
//
//	// If r x s = 0 and (q - p) x r = 0, then the two lines are collinear.
//	if (rxs.IsZero() && qpxr.IsZero())
//	{
//		// 1. If either  0 <= (q - p) * r <= r * r or 0 <= (p - q) * s <= * s
//		// then the two lines are overlapping,
//		if (considerCollinearOverlapAsIntersect)
//			if ((0 <= (q - p)*r && (q - p)*r <= r*r) || (0 <= (p - q)*s && (p - q)*s <= s*s))
//				return true;
//
//		// 2. If neither 0 <= (q - p) * r = r * r nor 0 <= (p - q) * s <= s * s
//		// then the two lines are collinear but disjoint.
//		// No need to implement this expression, as it follows from the expression above.
//		return false;
//	}
//
//	// 3. If r x s = 0 and (q - p) x r != 0, then the two lines are parallel and non-intersecting.
//	if (rxs.IsZero() && !qpxr.IsZero())
//		return false;
//
//	// t = (q - p) x s / (r x s)
//	var t = (q - p).Cross(s) / rxs;
//
//	// u = (q - p) x r / (r x s)
//
//	var u = (q - p).Cross(r) / rxs;
//
//	// 4. If r x s != 0 and 0 <= t <= 1 and 0 <= u <= 1
//	// the two line segments meet at the point p + t r = q + u s.
//	if (!rxs.IsZero() && (0 <= t && t <= 1) && (0 <= u && u <= 1))
//	{
//		// We can calculate the intersection point using either t or u.
//		intersection = p + t*r;
//
//		// An intersection was found.
//		return true;
//	}
//
//	// 5. Otherwise, the two line segments are not parallel but do not intersect.
//	return false;
//}

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
