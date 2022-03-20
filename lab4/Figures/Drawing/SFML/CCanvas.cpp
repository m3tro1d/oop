#include "CCanvas.h"

CCanvas::CCanvas(sf::RenderTarget& target)
	: m_target(target)
{
}

void CCanvas::DrawLine(CPoint from, CPoint to, uint32_t lineColor)
{
	sf::Vertex line[] = {
		sf::Vertex(sf::Vector2f(from.GetX(), from.GetY())),
		sf::Vertex(sf::Vector2f(to.GetX(), to.GetY())),
	};

	line[0].color = BuildColor(lineColor);
	line[1].color = BuildColor(lineColor);

	m_target.draw(line, 2, sf::Lines);
}

void CCanvas::DrawPolygon(const std::vector<CPoint>& points, uint32_t outlineColor, uint32_t fillColor)
{
	sf::ConvexShape shape;

	shape.setOutlineColor(BuildColor(outlineColor));
	shape.setFillColor(BuildColor(fillColor));

	shape.setPointCount(points.size());
	for (size_t i = 0; i < points.size(); ++i)
	{
		auto const& point = points[i];
		shape.setPoint(i, sf::Vector2f(point.GetX(), point.GetY()));
	}

	m_target.draw(shape);
}

void CCanvas::DrawCircle(CPoint center, double radius, uint32_t outlineColor, uint32_t fillColor)
{
	sf::CircleShape shape;

	shape.setOutlineColor(BuildColor(outlineColor));
	shape.setFillColor(BuildColor(fillColor));

	shape.setPosition(center.GetX() + radius, center.GetY() + radius);
	shape.setRadius(radius);

	m_target.draw(shape);
}

sf::Color CCanvas::BuildColor(uint32_t color)
{
	uint32_t red = color / 256 / 256 % 256;
	uint32_t green = color / 256 % 256;
	uint32_t blue = color % 256;

	return sf::Color(red, green, blue);
}
