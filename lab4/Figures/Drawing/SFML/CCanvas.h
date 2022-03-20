#pragma once

#include "../ICanvas.h"
#include <SFML/Graphics.hpp>

class CCanvas : public ICanvas
{
public:
	explicit CCanvas(sf::RenderTarget& target);

	void DrawLine(CPoint from, CPoint to, uint32_t lineColor) override;
	void DrawPolygon(const std::vector<CPoint>& points, uint32_t outlineColor, uint32_t fillColor) override;
	void DrawCircle(CPoint center, double radius, uint32_t outlineColor, uint32_t fillColor) override;

private:
	static sf::Color BuildColor(uint32_t color);

	sf::RenderTarget& m_target;
};
